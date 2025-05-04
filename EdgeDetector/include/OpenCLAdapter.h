/**
 * @file OpenCLAdapter.h
 * @author Eugenio Stabile (eugenio.stabile@photonicsens.com)
 * @brief Adapter to OpenCL library
 * @version 2.0.0
 * @date 2024-08-27
 * 
 * Copyright (c) 2024, Photonicsens. All rights reserved.
 * 
 */

#pragma once

#ifndef _OPENCLADAPTER_H
#define _OPENCLADAPTER_H

#include <tvm/runtime/module.h>
#include <tvm/runtime/registry.h>
#include <tvm/runtime/packed_func.h>
#include <tvm/runtime/c_runtime_api.h>
#include <CL/cl.hpp>
#include <fstream>

#include "Buffer.h"
#include "Utils.h"

class OpenCLAdapter {

public:

	enum DeviceType {
		TYPE_GPU = CL_DEVICE_TYPE_GPU,
		TYPE_CPU = CL_DEVICE_TYPE_CPU,
		TYPE_ANY = CL_DEVICE_TYPE_ALL,
	};

    struct OpenCLParams {
        std::vector<cl::Platform> platforms;
        std::vector<cl::Device> devices;
        cl::Context context;
        cl::CommandQueue queue;
        cl_int ret = 0;
    };

    OpenCLAdapter() = default;
    ~OpenCLAdapter() = default;

    void getOpenCLParams(OpenCLParams& openclParams);
    void finishOpenCLParams(OpenCLParams& openclParams);

    template<typename... Args>
    void computeOpenCL(const std::string& algorithmName, OpenCLParams openclParams, Args ...args) {
        
        size_t index = 0;
        size_t numOfArguments = sizeof...(args);
        
        std::vector<cl::Buffer> openclBuffers;

        std::string libraryName = algorithmName + "_OCL_GPU" + ".cl";
        std::ifstream sourceFile(libraryName.c_str(), std::ios::binary);

        if (!sourceFile.is_open()) {
            throw std::runtime_error("No se pudo abrir el archivo: " + libraryName);
        }

        std::string sourceCode((std::istreambuf_iterator<char>(sourceFile)), std::istreambuf_iterator<char>());
        sourceFile.close();

        cl::Program::Sources sources(1, std::make_pair(sourceCode.c_str(), sourceCode.length()));

        cl::Program program(openclParams.context, sources, &openclParams.ret);
        openclParams.ret = program.build(openclParams.devices);

        if (openclParams.ret != CL_SUCCESS) {
            std::string buildLog;
            program.getBuildInfo(openclParams.devices[0], CL_PROGRAM_BUILD_LOG, &buildLog);
            std::cerr << "Build log:\n" << buildLog << std::endl;
        }

        auto processArg = [&](auto&& arg) {
            
            auto sizeBuf = getSize(arg);
            
            if (index < numOfArguments - 1) {

                openclBuffers.push_back(cl::Buffer(openclParams.context, CL_MEM_READ_ONLY, sizeBuf));
                openclParams.ret = openclParams.queue.enqueueWriteBuffer(openclBuffers[index], CL_TRUE, 0, sizeBuf, getData(arg));

            } else {

                openclBuffers.push_back(cl::Buffer(openclParams.context, CL_MEM_WRITE_ONLY, sizeBuf));

            }

            if (openclParams.ret != CL_SUCCESS) {
                std::cerr << "Error en enqueueWriteBuffer: " << openclParams.ret << std::endl;
            }
            ++index;
        };

        (processArg(args), ...);

        std::string kernelName = algorithmName + "_kernel";
        cl::Kernel kernel(program, kernelName.c_str(), &openclParams.ret);

        if (openclParams.ret != CL_SUCCESS) {
            std::cerr << "Error al crear el kernel: " <<openclParams.ret << std::endl;
        }
        
        int numThreads = 32;
        size_t i = 0;

        // Establecer los parametros del kernel
        for (; i < openclBuffers.size(); ++i) {
            cl::Buffer& clBuffer = openclBuffers[i];
            openclParams.ret = kernel.setArg(i, clBuffer);
            if (openclParams.ret != CL_SUCCESS) {
                std::cerr << "Error en setArg para el buffer: " << openclParams.ret << std::endl;
            }
        }
        

        std::shared_ptr<Buffer> lastBuffer = getLastBufferCPU(args...);
        int height = lastBuffer->getDims()[0];
        int width = lastBuffer->getDims()[1];
        size_t lastBufferSize = height * width * sizeof(float32_t);
        
        kernel.setArg(i++, height);
        if (openclParams.ret != CL_SUCCESS) {
            std::cerr << "Error en setArg para el buffer: " << openclParams.ret << std::endl;
        }
        
        kernel.setArg(i++, width);
        if (openclParams.ret != CL_SUCCESS) {
            std::cerr << "Error en setArg para el buffer: " << openclParams.ret << std::endl;
        }
        
        if (algorithmName != "upsamplingMatrix" && algorithmName != "transpose") {

            size_t globalHeight = (height + numThreads - 1) / numThreads * numThreads;
            size_t globalWidth = (width + numThreads - 1) / numThreads * numThreads;

            cl::NDRange global(globalHeight, globalWidth);
            cl::NDRange local(numThreads, numThreads);
            openclParams.ret = openclParams.queue.enqueueNDRangeKernel(kernel, cl::NullRange, global, local);

        } else {

            cl::NDRange global(static_cast<size_t>(height), static_cast<size_t>(width));
            openclParams.ret = openclParams.queue.enqueueNDRangeKernel(kernel, cl::NullRange, global);

        }

        // Ejecutar el kernel 
        if (openclParams.ret != CL_SUCCESS) {
            std::cerr << "Error en enqueueNDRangeKernel: " << openclParams.ret << std::endl;
        }
        
        cl::Buffer& outputGPU = openclBuffers.back();


        openclParams.ret = openclParams.queue.enqueueReadBuffer(outputGPU, CL_TRUE, 0, lastBufferSize, static_cast<void*>(lastBuffer->getData().data()));
        if (openclParams.ret != CL_SUCCESS) {
            std::cerr << "Error en enqueueReadBuffer: " << openclParams.ret << std::endl;
        }

    }

    size_t getSize(std::vector<float32_t>& filterCPU) {

        return filterCPU.size() * sizeof(float32_t);

    }


    size_t getSize(std::shared_ptr<Buffer> bufferCPU) {

        return bufferCPU->getDims()[0] * bufferCPU->getDims()[1] * sizeof(float32_t);

    }


    void* getData(std::vector<float32_t>& filterCPU) {

        return static_cast<void*>(filterCPU.data());

    }


    void* getData(std::shared_ptr<Buffer> bufferCPU) {

        return static_cast<void*>(bufferCPU->getData().data());

    }


private:
    
    std::vector<int64_t> dims_;

    template<typename T, typename... Args>
    std::shared_ptr<Buffer> getLastBufferCPU(T first, Args... args) {
        return getLastBufferCPU(args...);
    }

    template<typename T>
    std::shared_ptr<Buffer> getLastBufferCPU(T last) {
        return last;
    }

    template<typename T, typename... Args>
    T getFirstBufferCPU(T first, Args... args) {
        return first;
    }
    
};

#endif


