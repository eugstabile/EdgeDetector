/**
 * @file ZeroCrossingTVM.h
 * @author Eugenio Stabile (eugenio.stabile@photonicsens.com)
 * @brief Calculate edges using the zero crossing algorithm. Apache TVM version.
 * @version 2.0.0
 * @date 2024-06-04
 * 
 * Copyright (c) 2024, Photonicsens. All rights reserved.
 * 
 */

#ifndef _ZERO_CROSSING_TVM_H
#define _ZERO_CROSSING_TVM_H

#include "TVMAdapter.h"
#include "IZeroCrossing.h"
#include "BufferTVM.h"

class ZeroCrossingTVM : public IZeroCrossing<BufferTVM> {

public:

    /// @brief Construct a new ZeroCrossingCPU object
    ZeroCrossingTVM();
    ~ZeroCrossingTVM() = default;

    /**
     * @brief Setting dimensions and data of variables that compose zero crossings algorithm
     * 
     * @param in 
     * @param out 
     * @param configParams 
     */
    void settingArguments(std::shared_ptr<BufferTVM> in, std::shared_ptr<BufferTVM> out, const ConfigParams& configParams) override;
    
    /**
     * @brief Computing the sequential version of zero crossing
     * 
     * @param in 
     * @param out 
     */
    void compute(std::shared_ptr<BufferTVM> in, std::shared_ptr<BufferTVM> out) override;
    
    /**
     * @brief Get the Config Params object
     * 
     * @return const IZeroCrossing::ConfigParams 
     */
    const IZeroCrossing<BufferTVM>::ConfigParams getConfigParams() override;
    
    /**
     * @brief Set the Config Params object
     * 
     * @param ConfigParams 
     */
    void setConfigParams(const ConfigParams& ConfigParams) override;

    /**
     * @brief Get the Zero Crossing rows values
     * 
     * @return DLTensor* 
     */
    virtual std::shared_ptr<BufferTVM> getZeroCrossingH() override;

    /**
     * @brief Get the Zero Crossing columns values
     * 
     * @return DLTensor* 
     */
    virtual std::shared_ptr<BufferTVM> getZeroCrossingV() override;

private:

    /**
     * @brief It creates a tuple of Buffer objects to compute the zero crossing algorithm in every dimension
     */
    using BufferSet = 
    struct{
        std::shared_ptr<BufferTVM> h;
        std::shared_ptr<BufferTVM> v;
    };

    IZeroCrossing::ConfigParams configParams_;

    BufferSet derivativeImage_;
    BufferSet confidences_;
    BufferSet upSampledImage_;
    BufferSet zeroCrossings_;
    BufferSet inPadded_;

    std::shared_ptr<TVMAdapter> tvmAdapter_;
    std::vector<int64_t> dims_;

    DLTensor* derivativeFilter_;
    DLTensor* upsamplingFilter_;

    std::shared_ptr<BufferTVM> inTranspose_;
    std::shared_ptr<BufferTVM> zeroCrossingsMapVTranspose_;

    /**
     * @brief This function verifies the correctness of the image data and its dimensions.
     * 
     * @param in 
     * @param out 
     * @param configParams 
     */
    void checkParams(std::shared_ptr<BufferTVM> in, std::shared_ptr<BufferTVM> out, const ConfigParams& configParams);
    
    
    /**
     * @brief This function reserves memory space in the intermediate vectors necessary for the computation of the algorithm according to the dimensions of the input data.
     * 
     * @param bufferset 
     * @param dimsH 
     * @param dimsV 
     */
    void prepareBuffers(BufferSet& bufferset, std::vector<int64_t>& dimsH, std::vector<int64_t>& dimsV);

};

#endif