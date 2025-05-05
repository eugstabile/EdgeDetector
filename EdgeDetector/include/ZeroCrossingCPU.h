/**
 * @file ZeroCrossingCPU.h
 * @author Eugenio Stabile
 * @brief Calculate edges using the zero crossing algorithm
 * @version 2.0.0
 * @date 2024-03-22
 * 
 */

#pragma once

#ifndef _ZERO_CROSSING_CPU_H
#define _ZERO_CROSSING_CPU_H

#include "IZeroCrossing.h"

class ZeroCrossingCPU : public IZeroCrossing<Buffer> {

public:

    /// @brief Construct a new ZeroCrossingCPU object
    ZeroCrossingCPU();
    ~ZeroCrossingCPU() = default;

    /**
     * @brief Setting dimensions and data of variables that compose zero crossings algorithm
s     * 
     * @param in 
     * @param out 
     * @param configParams 
     */
    void settingArguments(const std::shared_ptr<Buffer>& in, std::shared_ptr<Buffer>& out, const ConfigParams& configParams);
    
    /**
     * @brief Computing the sequential version of zero crossing
     * 
     * @param in 
     * @param out 
     */
    void compute(const std::shared_ptr<Buffer>& in, std::shared_ptr<Buffer>& out) override;
    
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
    virtual std::shared_ptr<Buffer> getZeroCrossingH() override;

    /**
     * @brief Get the Zero Crossing columns values
     * 
     * @return std::shared_ptr<Buffer> 
     */
    virtual std::shared_ptr<Buffer> getZeroCrossingV() override;


    /**
     * @brief It creates a tuple of Buffer objects to compute the zero crossing algorithm in every dimension
     */
    using BufferSet = 
    struct{
        std::shared_ptr<Buffer> h;
        std::shared_ptr<Buffer> v;
    };

    IZeroCrossing<Buffer>::ConfigParams configParams_;

    BufferSet derivativeImage_;
    BufferSet confidences_;
    BufferSet upSampledImage_;
    BufferSet zeroCrossings_;
    BufferSet inPadded_;

    std::vector<float32_t> derivativeFilter_;
    std::vector<float32_t> upsamplingFilter_;

    /**
     * @brief This function gets the distance between 2 values and stores the distance difference. 
     * 
     * @param in 
     * @param confidencesFilter 
     */
    void calculateConfidences(const std::shared_ptr<Buffer>& in, std::shared_ptr<Buffer>& confidencesFilter);
    
    /**
     * @brief This function verifies the correctness of the image data and its dimensions.
     * 
     * @param in 
     * @param out 
     * @param configParams 
     */
    void checkParams(const std::shared_ptr<Buffer>& in, std::shared_ptr<Buffer>& out, const ConfigParams& configParams);
    
    /**
     * @brief This function applies the upsampling filter to the input vector.
     * 
     * @param in 
     * @param upsampledImage 
     * @param inPadded 
     */
    void calculateUpsampling(const std::shared_ptr<Buffer>& in, std::shared_ptr<Buffer>& upsampledImage, std::shared_ptr<Buffer>& inPadded);
    
    /**
     * @brief This function calculates borders of the input image. Applying zero crossing algorithm two times, first by rows and secondly by columns.
     * 
     * @param in 
     * @param inUpsampled 
     * @param confidences 
     * @param zeroCrossingsMap 
     */
    void calculateEdges(const std::shared_ptr<Buffer>& inUpsampled, const std::shared_ptr<Buffer>& confidences, std::shared_ptr<Buffer>& zeroCrossingsMap);
    
    /**
     * @brief This function verifies a zero crossing in horizontal and vertical component. In case of zero crossing stores 1, otherwise 0.
     * 
     * @param zeroCrossingsMapH 
     * @param zeroCrossingsMapV 
     * @param out 
     */
    void combineEdges(const std::shared_ptr<Buffer>& zeroCrossingsMapH, const std::shared_ptr<Buffer>& zeroCrossingsMapV, std::shared_ptr<Buffer>& out);
    
    /**
     * @brief This function applies the derivative filter to the input vector.
     * 
     * @param in 
     * @param out 
     * @param kernel 
     */
    void filterDerivative(const std::shared_ptr<Buffer>& in, std::shared_ptr<Buffer>& out, const std::vector<float32_t>& kernel);
    
    /**
     * @brief This function applies the upsampling filter to the input vector.
     * 
     * @param in 
     * @param out 
     * @param kernel 
     */
    void filterUpsampling(const std::shared_ptr<Buffer>& in, std::shared_ptr<Buffer>& out, const std::vector<float32_t>& kernel);
    
    /**
     * @brief This function reserves memory space in the intermediate vectors necessary for the computation of the algorithm according to the dimensions of the input data.
     * 
     * @param bufferset 
     * @param dimsH 
     * @param dimsV 
     */
    void prepareBuffers(BufferSet& bufferset, const std::vector<int64_t>& dimsH, const std::vector<int64_t>& dimsV);
private:

};

#endif