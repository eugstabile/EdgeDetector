#include <dlpack/dlpack.h>
#include <cstdint>

#include "EdgeDetectorException.h"
#include "BufferTVM.h"
#include "TVMAdapter.h"


BufferTVM::BufferTVM(int64_t height, int64_t width) {

    std::shared_ptr tvmAdapter = std::make_shared<TVMAdapter>();
    dims_ = {height, width};
    data_ = tvmAdapter->setBufferTVM(height, width);

}


DLTensor*& BufferTVM::getData() noexcept { 
  
    return data_; 
  
}


const std::vector<int64_t>& BufferTVM::getDims() noexcept { 
  
    return dims_; 

}


void BufferTVM::setData(DLTensor*& input, std::vector<int64_t>& dimensions) {

    std::shared_ptr<TVMAdapter> tvmAdapter = std::make_shared<TVMAdapter>();
    int64_t inputSize = tvmAdapter->getSize(input);

    if (inputSize == 0) {
        THROW_EXCEPTION( "Input size on BufferTVM setData is null." );
    }
    
    data_ = input;
    dims_ = dimensions;

}