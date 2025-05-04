/**
 * @file Buffer.h
 * @author Eugenio Stabile (eugenio.stabile@photonicsens.com)
 * @brief Interface for the basic data transfer object
 * @version 2.0.0
 * @date 2024-07-08
 * 
 * 
 */

#pragma once

#ifndef _IBUFFER_H
#define _IBUFFER_H

#include <vector>

using float32_t = float;

class IBuffer {

public:

  /// @brief It selects the dimensions of the input data
  enum DimsIndex {
    HEIGHT = 0, ///< Number of rows
    WIDTH = 1  ///< Number of columns
  };
    
    /**
     * @brief Get the Dims object
     * 
     * @return const std::vector<int64_t>& 
     */
    virtual const std::vector<int64_t>& getDims() noexcept = 0;

};

#endif 