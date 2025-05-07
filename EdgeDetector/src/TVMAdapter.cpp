#include <tvm/runtime/module.h>
#include <tvm/runtime/registry.h>

#include "TVMAdapter.h"
#include "BufferTVM.h"

#define HEIGHT Buffer::DimsIndex::HEIGHT
#define WIDTH Buffer::DimsIndex::WIDTH

const std::string pathDir =  "/home/eusta/TVMEugenio/EdgeDetector/Resources/kernels_CPU_OPT/";


TVMAdapter::TVMAdapter(const std::vector<std::string>& algorithms) {

    for(const auto& name : algorithms){
        loadLibraries(name);
    }

}


std::vector<int64_t> TVMAdapter::getDims(DLTensor*& inputTensor) {
    
    for (int i = 0; i < inputTensor->ndim; ++i) {
        dims_[i] =  inputTensor->shape[i];
    }

    return dims_;

}


int64_t TVMAdapter::getSize(DLTensor*& inputTensor) {
    
    int ndim = inputTensor->ndim;

    int64_t* shape = inputTensor->shape;

    int64_t size = 1;
    for (int i = 0; i < ndim; ++i) {
        size *= shape[i];
    }
    
    return size;

}


DLTensor* TVMAdapter::setBufferTVM(int64_t height, int64_t width) {

    DLTensor* inputTensor;
    std::vector<float32_t> inputData(height * width, 0.f);

    int64_t shape[2] = {height, width};
    TVMArrayAlloc(shape, 2, tvmParams_.dtype_code, tvmParams_.dtype_bits, tvmParams_.dtype_lanes, tvmParams_.device_type, tvmParams_.device_id, &inputTensor);
    TVMArrayCopyFromBytes(inputTensor, inputData.data(), inputData.size() * sizeof(float32_t));
    
    dims_ = {static_cast<int64_t>(height), static_cast<int64_t>(width)};

    return inputTensor;

}


std::shared_ptr<BufferTVM> TVMAdapter::bufferToTVM(const std::shared_ptr<Buffer> inputBuffer) {
    
    DLTensor* inputTensor;
    std::shared_ptr<BufferTVM> resultBuffer = std::make_shared<BufferTVM>();

    std::vector<float32_t>& inputData = inputBuffer->getData();
    std::vector<int64_t> inputDims = inputBuffer->getDims();

    int64_t shape[2] = {inputDims[HEIGHT], inputDims[WIDTH]};

    TVMArrayAlloc(shape, 2, tvmParams_.dtype_code, tvmParams_.dtype_bits, tvmParams_.dtype_lanes, tvmParams_.device_type, tvmParams_.device_id, &inputTensor);
    TVMArrayCopyFromBytes(inputTensor, inputData.data(), inputData.size() * sizeof(float32_t));
    
    dims_ = {inputDims[HEIGHT], inputDims[WIDTH]};

    resultBuffer->setData(inputTensor, dims_);

    return resultBuffer;

}


DLTensor* TVMAdapter::vectorToTVM(const std::vector<float32_t>& inputVector) {
    
    DLTensor* inputTensor;
    int64_t shape[1] = { static_cast<int64_t>(inputVector.size())};

    TVMArrayAlloc(shape, 1, tvmParams_.dtype_code, tvmParams_.dtype_bits, tvmParams_.dtype_lanes, tvmParams_.device_type, tvmParams_.device_id, &inputTensor);
    TVMArrayCopyFromBytes(inputTensor, const_cast<void*>(static_cast<const void*>(inputVector.data())), inputVector.size() * sizeof(float32_t));

    return inputTensor;

}


DLTensor* TVMAdapter::redimension(DLTensor*& inputTensor) {
    
    DLTensor* outputTensor;

    int64_t shape[2] = {inputTensor->shape[HEIGHT], inputTensor->shape[WIDTH]};
    
    TVMArrayAlloc(shape, 2, tvmParams_.dtype_code, tvmParams_.dtype_bits, tvmParams_.dtype_lanes, tvmParams_.device_type, tvmParams_.device_id, &outputTensor);
    TVMArrayCopyFromBytes(outputTensor, inputTensor->data, (inputTensor->shape[HEIGHT] * inputTensor->shape[HEIGHT]) * sizeof(float32_t));

    return outputTensor;
}


std::shared_ptr<Buffer> TVMAdapter::bufferFromTVM(DLTensor*& outputTensor) {
    
    std::shared_ptr<Buffer> outputBuffer = std::make_shared<Buffer>(outputTensor->shape[HEIGHT], outputTensor->shape[WIDTH]);
    std::vector<float32_t>& outputData = outputBuffer->getData();
    TVMArrayCopyToBytes(outputTensor, outputData.data(), outputData.size() * sizeof(float32_t));

    return outputBuffer;

}


TVMAdapter::TVMParams TVMAdapter::getTVMParams()
{

    return tvmParams_;
}

void TVMAdapter::setTVMParams(int device_id, int device_type, uint8_t dtype_bits, uint8_t dtype_code, unsigned short dtype_lanes) {

    tvmParams_.device_id = device_id;
    tvmParams_.device_type = device_type;
    tvmParams_.dtype_bits = dtype_bits;
    tvmParams_.dtype_code = dtype_code;
    tvmParams_.dtype_lanes = dtype_lanes;

}


void TVMAdapter::loadLibraries(const std::string& algorithmName) {
    
    std::string libraryName;

    #ifdef _WIN32
        libraryName = "Resources/kernels_CPU_OPT/" + algorithmName + "Windows_CPU_OPT" + ".dll";
    #else
        libraryName = pathDir + algorithmName + "Linux_CPU_OPT" + ".so";
    #endif

    tvm::runtime::Module mod_dylib = tvm::runtime::Module::LoadFromFile(libraryName);
    std::shared_ptr<tvm::runtime::Module> mod = std::make_shared<tvm::runtime::Module>(mod_dylib);
    function_[algorithmName] = mod;

}