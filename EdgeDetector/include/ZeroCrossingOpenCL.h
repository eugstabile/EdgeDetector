/**
 * @file ZeroCrossingCPU.h
 * @author Eugenio Stabile
 * @brief Calculate edges using the zero crossing algorithm
 * @version 2.0.0
 * @date 2024-03-22
 * 
 */

#pragma once

#ifndef _ZERO_CROSSING_OPENCL_H
#define _ZERO_CROSSING_OPENCL_H

#include "IZeroCrossing.h"
#include "OpenCLAdapter.h"

class ZeroCrossingOpenCL : public IZeroCrossing<Buffer> {

public:

    /// @brief Construct a new ZeroCrossingOpenCL object
    ZeroCrossingOpenCL();
    ~ZeroCrossingOpenCL() = default;

    /**
     * @brief Setting dimensions and data of variables that compose zero crossings algorithm
     * 
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

private:

    /**
     * @brief It creates a tuple of Buffer objects to compute the zero crossing algorithm in every dimension
     */
    using BufferSet = 
    struct{
        std::shared_ptr<Buffer> h;
        std::shared_ptr<Buffer> v;
    };

    IZeroCrossing<Buffer>::ConfigParams configParams_;
    std::shared_ptr<OpenCLAdapter> openCLAdapter_;

    BufferSet derivativeImage_;
    BufferSet confidences_;
    BufferSet upSampledImage_;
    BufferSet zeroCrossings_;
    BufferSet inPadded_;

    std::vector<float32_t> derivativeFilter_;
    std::vector<float32_t> upsamplingFilter_;

    std::shared_ptr<Buffer> inTranspose_;
    std::shared_ptr<Buffer> zeroCrossingsMapVTranspose_;

    OpenCLAdapter::OpenCLParams openclParams_;


    /**
     * @brief This function verifies the correctness of the image data and its dimensions.
     * 
     * @param in 
     * @param out 
     * @param configParams 
     */
    void checkParams(const std::shared_ptr<Buffer>& in, std::shared_ptr<Buffer>& out, const ConfigParams& configParams);
    
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