/**
 * @file BufferTVM.h
 * @author Eugenio Stabile
 * @brief Interface for the basic data transfer object
 * @version 2.0.0
 * @date 2024-07-08
 * 
 */

#pragma once

#ifndef _BUFFERTVM_H
#define _BUFFERTVM_H

#include <dlpack/dlpack.h>
#include "IBuffer.h"

class BufferTVM : public IBuffer {

public:

    /// @brief Construct a new BufferTVM object 
    BufferTVM() = default;

    /**
     * @brief Construct a new BufferTVM object specifying the dimensions of the image
     * 
     * 
     * @param height 
     * @param width 
     */
    BufferTVM(int64_t height, int64_t width);
    
    virtual ~BufferTVM() = default;


    /**
     * @brief Get the Data object
     * 
     * @return DLTensor*& 
     */
    DLTensor*& getData() noexcept;


    /**
     * @brief Set the Data object
     * 
     * @param input 
     * @param dimensions 
     */
    void setData(DLTensor*& input, std::vector<int64_t>& dimensions);


    /**
     * @brief Get the Dims object
     * 
     * @return const std::vector<int64_t>& 
     */
    const std::vector<int64_t>& getDims() noexcept;
    

private:

    DLTensor* data_;
    std::vector<int64_t> dims_;

};

#endif 