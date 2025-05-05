/**
 * @file Buffer.h
 * @author Eugenio Stabile
 * @brief Interface for the basic data transfer object
 * @version 2.0.0
 * @date 2024-03-18
 * 
 * 
 */

#pragma once

#ifndef _BUFFER_H
#define _BUFFER_H

#include <stdint.h>

#include "IBuffer.h"

class Buffer : public IBuffer {

public:

  /// @brief It selects the dimensions of the input data
  enum DimsIndex {
    HEIGHT = 0, ///< Number of rows
    WIDTH = 1  ///< Number of columns
  };
    
    /// @brief Construct a new Buffer object 
    Buffer() = default;

    /**
     * @brief Construct a new Buffer object specifying the dimensions of the image
     * 
     * 
     * @param height 
     * @param width 
     */
    Buffer(int64_t height, int64_t width);
    
    virtual ~Buffer() = default;

    /**
     * @brief Get the Data object
     * 
     * @return std::vector<float32_t>& 
     */
    std::vector<float32_t>& getData() noexcept;

    /**
     * @brief Set the Data object
     * 
     * @param input 
     * @param dimensions 
     */
    void setData(std::vector<float32_t>& input, std::vector<int64_t>& dimensions);

    /**
     * @brief Get the Dims object
     * 
     * @return const std::vector<int64_t>& 
     */
    const std::vector<int64_t>& getDims() noexcept;


private:

    std::vector<float32_t> data_;
    std::vector<int64_t> dims_;

};

#endif 