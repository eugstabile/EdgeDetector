/**
 * @file OpenCLAdapter.h
 * @author Eugenio Stabile (eugenio.stabile@photonicsens.com)
 * @brief Adapter to OpenCL library
 * @version 2.0.0
 * @date 2024-08-27
 * 
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
 #include "EdgeDetectorException.h"
 
 class OpenCLAdapter {
 
 public:
 
     enum DeviceType {

        GPU = CL_DEVICE_TYPE_GPU,
        CPU = CL_DEVICE_TYPE_CPU,
        ANY = CL_DEVICE_TYPE_ALL,

     };
 
     struct OpenCLParams {

        std::vector<cl::Platform> platforms;
        std::vector<cl::Device> devices;
        cl::Context context;
        cl::CommandQueue queue;
        cl_int ret = CL_SUCCESS;

     };
 
    OpenCLAdapter() = default;
    ~OpenCLAdapter() = default;
 
    void getOpenCLParams(OpenCLParams& openclParams);
    void finishOpenCLParams(OpenCLParams& openclParams);

    template<typename... Args>
    void computeOpenCL(const std::string& algorithmName, OpenCLParams openclParams, Args ...args) {
        
        constexpr size_t numOfArguments = sizeof...(Args);
        size_t index = 0;
        std::vector<cl::Buffer> openclBuffers;
        openclBuffers.reserve(numOfArguments);
        
        // Read kernel source
        const std::string fileName = "kernels_GPU/" + algorithmName + "_OCL_GPU.cl";
        std::ifstream fileSource{fileName, std::ios::binary};

        if (!fileSource) {

            THROW_EXCEPTION("Cannot open " + fileName);
            
        }

        const std::string src{std::istreambuf_iterator<char>(fileSource), {}};

        // Crear programa
        cl::Program program{openclParams.context, src, true, &openclParams.ret};

        if (openclParams.ret != CL_SUCCESS) {

            std::string buildLog;
            program.getBuildInfo(openclParams.devices[0], CL_PROGRAM_BUILD_LOG, &buildLog);
            
            THROW_EXCEPTION_CODE("Error en el build log: ", openclParams.ret );

        }

        auto makeBuffer = [&](auto&& arg, bool isOutput) {

            const auto size = getSize(arg);
            cl_mem_flags flags = isOutput ? CL_MEM_WRITE_ONLY : CL_MEM_READ_ONLY;
            cl::Buffer buf{openclParams.context, flags, size};

            if (!isOutput) {

                openclParams.ret = openclParams.queue.enqueueWriteBuffer(buf, CL_TRUE, 0, size, getData(arg));
                
                if (openclParams.ret != CL_SUCCESS) {

                    THROW_EXCEPTION_CODE("Error al crear el enqueueWriteBuffer: ", openclParams.ret );

                }
                
            }

            return buf;

        };

        (void) std::initializer_list<int>{(
                openclBuffers.push_back(
                    makeBuffer(std::forward<Args>(args), (index == numOfArguments - 1))),
                ++index, 0)...
        };
 
        std::string kernelName = algorithmName + "_kernel";
        cl::Kernel kernel(program, kernelName.c_str(), &openclParams.ret);

        if (openclParams.ret != CL_SUCCESS) {

            THROW_EXCEPTION_CODE("Error al crear el kernel: ", openclParams.ret );

        }
         
        int numThreads = 32;
         
        for (size_t i = 0; i < openclBuffers.size(); ++i) {
            openclParams.ret  = kernel.setArg(i, openclBuffers[i]);
            
            if (openclParams.ret != CL_SUCCESS) {

                THROW_EXCEPTION_CODE("Error en setArg para los buffers: ", openclParams.ret );

            }

        }
 
        std::shared_ptr<Buffer> lastBuffer = getLastBufferCPU(args...);
        int height = lastBuffer->getDims()[0];
        int width = lastBuffer->getDims()[1];
        size_t lastBufferSize = height * width * sizeof(float32_t);
        
        kernel.setArg(openclBuffers.size(), height);

        if (openclParams.ret != CL_SUCCESS) {
        
            THROW_EXCEPTION_CODE("Error en setArg para en el height: ", openclParams.ret );
        
        }
        
        kernel.setArg(openclBuffers.size() + 1, width);
        
        if (openclParams.ret != CL_SUCCESS) {
        
            THROW_EXCEPTION_CODE("Error en setArg para en el width: ", openclParams.ret );
        
        }
        
        if (algorithmName != "upsamplingMatrix" && algorithmName != "transpose") {

            const size_t globalHeight = ((height + numThreads - 1) / numThreads) * numThreads;
            const size_t globalWidth = ((width + numThreads - 1) / numThreads) * numThreads;

            cl::NDRange global(globalHeight, globalWidth);
            cl::NDRange local(numThreads, numThreads);
        
            openclParams.ret = openclParams.queue.enqueueNDRangeKernel(kernel, cl::NullRange, global, local);

        } else {

            cl::NDRange global(static_cast<size_t>(height), static_cast<size_t>(width));
            openclParams.ret = openclParams.queue.enqueueNDRangeKernel(kernel, cl::NullRange, global);

        }

        // Ejecutar el kernel 
        if (openclParams.ret != CL_SUCCESS) {
        
            THROW_EXCEPTION_CODE("Error en enqueueNDRangeKernel: ", openclParams.ret );
        
        }
        
        cl::Buffer& outputGPU = openclBuffers.back();

        openclParams.ret = openclParams.queue.enqueueReadBuffer(outputGPU, CL_TRUE, 0, lastBufferSize, static_cast<void*>(lastBuffer->getData().data()));

        if (openclParams.ret != CL_SUCCESS) {

            THROW_EXCEPTION_CODE("Error en enqueueReadBuffer: ", openclParams.ret );
        
        }

    }

    template <typename T>

    static size_t getSize(const T& buffer) {

        if constexpr (std::is_same_v<T, std::vector<float>>) {

            return buffer.size() * sizeof(float);

        } else {

            const size_t height = buffer->getDims()[0];
            const size_t width  = buffer->getDims()[1];
            
            return height * width * sizeof(float);

        }

    }
 
    template <typename T>
    static void* getData(T& buffer) {

        if constexpr (std::is_same_v<T, std::vector<float>>) {

            return const_cast<float*>(buffer.data());

        } else {

            return buffer->getData().data();

        }

    }
 
 
 private:
     
    std::vector<int64_t> dims_;

    template <typename... Args>
    static auto getLastBufferCPU(Args&&... args) {

        auto res = std::forward_as_tuple(std::forward<Args>(args)...);

        return std::get<sizeof...(Args) - 1>(res);

     }
     
 };
 
 #endif
 