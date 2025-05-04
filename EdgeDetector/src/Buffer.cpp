#include <cstdint>

#include "EdgeDetectorException.h"
#include "Buffer.h"


Buffer::Buffer(int64_t height, int64_t width) {
  
    size_t totalSize = height * width ;
    data_.clear();
    data_.resize(totalSize, 0.f);
    dims_ = {height, width};

}


std::vector<float32_t>& Buffer::getData() noexcept { 
  
    return data_; 
  
}


const std::vector<int64_t>& Buffer::getDims() noexcept { 
  
    return dims_; 

}


void Buffer::setData(std::vector<float32_t>& input, std::vector<int64_t>& dimensions) {

    if (input.size() == 0) {
        THROW_EXCEPTION( "Input size on Buffer setData is null." );
    }
    
    size_t totalSize = dimensions[DimsIndex::HEIGHT] * dimensions[DimsIndex::WIDTH];
    data_.clear();
    data_.resize(totalSize);
    data_ = input;
    dims_ = dimensions;

}