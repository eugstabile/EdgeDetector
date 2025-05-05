/**
 * @file TVMAdapter.h
 * @author Eugenio Stabile
 * @brief Adapter to TVM library
 * @version 2.0.0
 * @date 2024-06-17
 * 
 */

#pragma once

#ifndef _TVMADAPTER_H
#define _TVMADAPTER_H

#include <tvm/runtime/module.h>
#include <tvm/runtime/registry.h>
#include <tvm/runtime/packed_func.h>
#include <tvm/runtime/c_runtime_api.h>

#include "BufferTVM.h"
#include "Utils.h"

class TVMAdapter {

public:

    struct TVMParams {
        int device_type{ kDLCPU };
        int device_id{ 0 };
        uint8_t dtype_code{ kDLFloat };
        uint8_t dtype_bits{ 32 };
        unsigned short dtype_lanes{ 1 };
    }; 

    TVMAdapter() = default;
    TVMAdapter(const std::vector<std::string>& algorithms);

    ~TVMAdapter() = default;

    TVMParams getTVMParams();
    void setTVMParams(int device_id = 0, int device_type = 0, uint8_t dtype_bits = 0, uint8_t dtype_code = 0, unsigned short dtype_lanes = 0);
    

    /**
     * @brief Get the Tensor object. Obtiene los buffers de entrada y salida, identifica el kernel de TVM y lo ejecuta 
     * (En su llamada hay que hacer coincidir las posiciones de los argumentos)
     * @tparam T 
     * @param buffer 
     * @return DLTensor* 
     */
    template<typename T> DLTensor* getTensor(T& buffer) {
        return buffer->getData();
    };

    /**
     * @brief Get the Tensor<D L Tensor*> object. Generalmente son los filtros los que pasan por esta etapa
     * @tparam  
     * @param buffer 
     * @return DLTensor* 
     */
    template<> DLTensor* getTensor<DLTensor*>(DLTensor*& buffer) {
        return buffer;
    };


    template<typename... Args>
    void computeTVM(const std::string& algorithmName, Args ...args) {

        algorithm_ = function_[algorithmName]->GetFunction(algorithmName);
        algorithm_(getTensor(args)...);

    };


    DLTensor* vectorToTVM(const std::vector<float32_t>& inputVector);
    DLTensor* setBufferTVM(int64_t height, int64_t width);
    std::shared_ptr<BufferTVM> bufferToTVM(const std::shared_ptr<Buffer> inputBuffer);
    std::shared_ptr<Buffer> bufferFromTVM(DLTensor*& outputTensor);

    std::vector<int64_t> getDims(DLTensor*& inputTensor);
    int64_t getSize(DLTensor*& inputTensor);
    void loadLibraries(const std::string& algorithmName);
    DLTensor* redimension(DLTensor*& inputTensor);


private:
    
    std::vector<int64_t> dims_;
    std::map<std::string, std::shared_ptr<tvm::runtime::Module>> function_;
        
    tvm::runtime::PackedFunc algorithm_;
    TVMParams tvmParams_;
    
};
#endif


