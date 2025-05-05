/**
 * @file Utils.h
 * @author Eugenio Stabile
 * @brief Utilities for zero crossing algorithm
 * @version 2.0.0
 * @date 2024-04-02
 * 
 */

#pragma once

#ifndef _UTILS_H
#define _UTILS_H

#include <memory>
#include <string>

#include "Buffer.h"

constexpr float32_t tolerance_{0.016f};

/**
 * @brief This function transposes a vector row-wise to column-wise
 * 
 * @param in 
 * @return std::shared_ptr<Buffer> 
 */
std::shared_ptr<Buffer> transpose(const std::shared_ptr<Buffer>& in);

/**
 * @brief This function transposes a vector row-wise to column-wise. This is the vectorized and parallelized version of transpose function
 * 
 * @param in 
 * @return std::shared_ptr<Buffer> 
 */
std::shared_ptr<Buffer> transposeOptimized(const std::shared_ptr<Buffer>& in);

/**
 * @brief This function stores a Buffer object into a text plain format
 * 
 * @param in 
 * @param path 
 */
void printMatrix(const std::shared_ptr<Buffer>& in, const std::string& path);

/**
 * @brief This function takes 2 Buffer objects and compares element by element if the distance of both values are greater than a threshold
 * 
 * @param in 
 * @param out 
 */
void verifyOutput(const std::shared_ptr<Buffer>& in, const std::shared_ptr<Buffer>& out);

/**
 * @brief This function takes a synthetic matrix and compares the correctness of each value
 * 
 * @param in 
 * @param zeroCrossingExpected 
 */
void verifySynteticMatrixOutput(const std::shared_ptr<Buffer>& in, float32_t zeroCrossingExpected);

/**
 * @brief This function stores a Buffer object into a binary file and returns it into a string.
 * 
 * @param out 
 * @return std::string 
 */
std::string saveToBin(const std::shared_ptr<Buffer>& out);

/**
 * @brief This function compares 2 strings that contains the binaries of images.
 * 
 * @param outputBin 
 * @param outputCorrectBin 
 */
void compareBinFiles(const std::string& outputBin, const std::string& outputCorrectBin);

#endif 