/**
 * @file ZeroCrossingTest.h
 * @author Eugenio Stabile (eugenio.stabile@photonicsens.com)
 * @brief A Fixture Google Test for ZeroCrossingTest.
 * @version 2.0.0
 * @date 2024-04-30
 * 
 * @copyright Copyright (c) 2024, Photonicsens. All rights reserved.
 * 
 */

#pragma once
#ifndef _ZEROCROSSINGTEST_H
#define _ZEROCROSSINGTEST_H

#include <memory>
#include <gtest/gtest.h>

#include "AlgorithmFactory.h"
#include "IZeroCrossing.h"
#include "OpenCVAdapter.h"
#include "SyntheticMatrix.h"
#include "Buffer.h"
#include "BufferTVM.h"


template <typename T, typename B>
class ZeroCrossingTest : public ::testing::TestWithParam<std::tuple<AlgorithmFactory::AlgorithmType, std::string>> {

public:

    AlgorithmFactory::AlgorithmType algorithmType = std::get<0>(GetParam());
    std::string processorType = std::get<1>(GetParam());

protected:
    
    const std::string path_ = "parrot";
    std::string savingPath_ = path_ + "ZeroCrossing" + processorType;
    std::string syntheticPath_ = "matrixSynt"+ processorType + "Input";
    std::string syntheticSavingPath_ = "matrixSynt" + processorType + "Output";
    std::string syntheticTPath_ = "matrixTrin"+ processorType + "Input";
    std::string syntheticTSavingPath_ = "matrixTrin" + processorType + "Output";
    std::string compareBinImage_ = "matrixSynt" + processorType + "InputCompare";
    const std::string matrixCVOut_ = "matrixCVOut.bin";

    using INVALID_TYPE = std::vector<double>;
    
    int64_t height;
    int64_t width;
    typename IZeroCrossing<B>::ConfigParams configParams;
    std::vector<int64_t> inputDims;

    std::shared_ptr<OpenCVAdapter> adapter;
    std::shared_ptr<AlgorithmFactory> algorithmFactory;
    std::shared_ptr<IZeroCrossing<B>> zeroCrossing;
    std::shared_ptr<SyntheticMatrix> syntheticMatrix;
    float32_t slope;
    float32_t zeroCrossingExpected;


    void SetUp() override {

        adapter = std::make_shared<OpenCVAdapter>();
        algorithmFactory = AlgorithmFactory::getInstance();
        zeroCrossing = algorithmFactory->getAlgorithm<IZeroCrossing<B>>(algorithmType);
        height =                    1024;
        width =                     1024;
        slope =                     1.2f;
        zeroCrossingExpected =      0.15f;
        configParams.threshold =    0.016f;
    }

};
#endif