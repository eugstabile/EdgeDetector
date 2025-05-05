/**
 * @file ZeroCrossingTest.h
 * @author Eugenio Stabile 
 * @brief A Fixture Google Test for ZeroCrossingTest.
 * @version 2.0.0
 * @date 2024-04-30
 * 
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

    using INVALID_TYPE = std::vector<double>;
    using ConfigParams = IZeroCrossing<B>::ConfigParams;

protected:

    AlgorithmFactory::AlgorithmType algorithmType = std::get<0>(GetParam());
    std::string processorType = std::get<1>(GetParam());

    const std::string path_ = "parrot";
    const std::string savingPath_ = path_ + "ZeroCrossing" + processorType;
    const std::string syntheticPath_ = "matrixSynt"+ processorType + "Input";
    const std::string syntheticSavingPath_ = "matrixSynt" + processorType + "Output";
    const std::string syntheticTPath_ = "matrixTrin"+ processorType + "Input";
    const std::string syntheticTSavingPath_ = "matrixTrin" + processorType + "Output";
    const std::string compareBinImage_ = "matrixSynt" + processorType + "InputCompare";
    const std::string matrixCVOut_ = "matrixCVOut.bin";

    
    int64_t height;
    int64_t width;
    std::vector<int64_t> inputDims;

    std::shared_ptr<OpenCVAdapter> adapter;
    std::shared_ptr<AlgorithmFactory> algorithmFactory;
    std::shared_ptr<IZeroCrossing<B>> zeroCrossing;
    std::shared_ptr<SyntheticMatrix> syntheticMatrix;
    float32_t slope;
    float32_t zeroCrossingExpected;
    ConfigParams configParams;


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