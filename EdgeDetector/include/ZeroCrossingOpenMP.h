/**
 * @file ZeroCrossingOpenMP.h
 * @author Eugenio Stabile (eugenio.stabile@photonicsens.com)
 * @brief Calculate edges using the zero crossing algorithm. Optimized version.
 * @version 2.0.0
 * @date 2024-04-02
 * 
 * Copyright (c) 2024, Photonicsens. All rights reserved.
 * 
 */

#pragma once

#ifndef _ZERO_CROSSING_OPENMP_H
#define _ZERO_CROSSING_OPENMP_H

#include <immintrin.h>

#include "IZeroCrossing.h"

typedef __m128 VECTOR_TYPE;
#define VECTOR_STEP 4

class ZeroCrossingOpenMP : public IZeroCrossing<Buffer> {

public:

    /**
     * @brief Construct a new ZeroCrossingOpenMP object
     * 
     */
    ZeroCrossingOpenMP();
    ~ZeroCrossingOpenMP() = default;

    /**
     * @brief Setting dimensions and data of variables that compose zero crossings algorithm
     * 
     * @param in 
     * @param out 
     * @param configParams 
     */
    void settingArguments(const std::shared_ptr<Buffer> in, const std::shared_ptr<Buffer> out, const ConfigParams& configParams);
    
    /**
     * @brief Computing the optimized version of zero crossing
     * 
     * @param in 
     * @param out 
     */
    void compute(const std::shared_ptr<Buffer> in, std::shared_ptr<Buffer> out) override;
    
    /**
     * @brief Get the Config Params object
     * 
     * @return const IZeroCrossing::ConfigParams 
     */
    const IZeroCrossing<Buffer>::ConfigParams getConfigParams() override;

    /**
     * @brief Set the Config Params object
     * 
     * @param ConfigParams 
     */
    void setConfigParams(const ConfigParams& ConfigParams) override;

    /**
     * @brief Get the Zero Crossing rows values
     * 
     * @return std::shared_ptr<Buffer> 
     */
    virtual std::shared_ptr<Buffer> getZeroCrossingH();

    /**
     * @brief Get the Zero Crossing columns values
     * 
     * @return std::shared_ptr<Buffer> 
     */
    virtual std::shared_ptr<Buffer> getZeroCrossingV();

private:

    /**
     * @brief It creates a tuple of Buffer objects to compute the zero crossing algorithm in every dimension
     */
    using BufferSet = 
    struct{
        std::shared_ptr<Buffer> h;
        std::shared_ptr<Buffer> v;
    };

    IZeroCrossing::ConfigParams configParams_;

    BufferSet derivativeImage_;
    BufferSet zeroCrossings_;

    std::vector<float32_t> derivativeFilter_;
    std::vector<float32_t> upsamplingFilter_;

    /**
     * @brief This function verifies the correctness of the image data and its dimensions.
     * 
     * @param in 
     * @param out 
     * @param configParams 
     */
    void checkParams(const std::shared_ptr<Buffer> in, const std::shared_ptr<Buffer> out, const ConfigParams& configParams);
    
    /**
     * @brief This function calculates borders of the input image. Applying zero crossing algorithm two times, first by rows and secondly by columns.
     * 
     * @param in 
     * @param derivativeImage 
     * @param zeroCrossingsMap 
     */
    void calculateEdges(const std::shared_ptr<Buffer> in, std::shared_ptr<Buffer> derivativeImage, std::shared_ptr<Buffer> zeroCrossingsMap);
    
    /**
     * @brief This function verifies a zero crossing in horizontal and vertical component. In case of zero crossing stores 1, otherwise 0.
     * 
     * @param zeroCrossingsMapH 
     * @param zeroCrossingsMapV 
     * @param out 
     */
    void combineEdges(const std::shared_ptr<Buffer> zeroCrossingsMapH, const std::shared_ptr<Buffer> zeroCrossingsMapV, std::shared_ptr<Buffer> out);
    
    /**
     * @brief This function applies the upsampling filter to the input vector.
     * 
     * @param kernelPos 
     * @param inputData 
     * @param outputData 
     */
    void filterUpsampling(int kernelPos, std::vector<float32_t>::iterator& inputData, std::vector<float32_t>::iterator& outputData);
    
    /**
     * @brief This function reserves memory space in the intermediate vectors necessary for the computation of the algorithm according to the dimensions of the input data.
     * 
     * @param bufferset 
     * @param dimsH 
     * @param dimsV 
     */
    void prepareBuffers(BufferSet& bufferset, const std::vector<int64_t>& dimsH, const std::vector<int64_t>& dimsV);

};

#endif