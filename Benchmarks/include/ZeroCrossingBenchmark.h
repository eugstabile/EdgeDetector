/**
 * @file ZeroCrossingBenchmark.h
 * @author Eugenio Stabile 
 * @brief A Fixture Google Test for ZeroCrossingBenchmark.
 * @version 2.0.0
 * @date 2024-04-30
 * 
 */

#pragma once
#ifndef _ZEROCROSSINGBENCHMARK_H
#define _ZEROCROSSINGBENCHMARK_H

#include <gtest/gtest.h>

#include "EdgeDetectorException.h"
#include "AlgorithmFactory.h"
#include "Benchmark.h"
#include "IZeroCrossing.h"
#include "OpenCVAdapter.h"
#include "Kernel.h"
#include "SyntheticMatrix.h"


template <typename T, typename B>
class ZeroCrossingBenchmark : public ::testing::TestWithParam<AlgorithmFactory::AlgorithmType> {

public:

    AlgorithmFactory::AlgorithmType algorithmType = GetParam();

protected:
    
    int64_t width;
    int64_t height;
    int64_t numOfImages;
    int64_t minHeight;
    int64_t minWidth;
    int64_t growthFactor;
    float32_t slope;
    float32_t zeroCrossingExpected;

    typename IZeroCrossing<B>::ConfigParams configParams;
    std::vector<int64_t> inputDims;
    std::shared_ptr<OpenCVAdapter> adapter;
    std::shared_ptr<AlgorithmFactory> algorithmFactory;
    std::shared_ptr<IZeroCrossing<B>> zeroCrossing;
    std::shared_ptr<Benchmark<std::string>> benchmark;
    std::shared_ptr<Benchmark<std::shared_ptr<B>>> benchmarkSynthetic; 
    std::shared_ptr<B> bufferIn;
    std::shared_ptr<B> bufferOut;
    std::shared_ptr<Kernel> kernel;
    std::shared_ptr<SyntheticMatrix> syntheticMatrix;
    std::vector<std::shared_ptr<Buffer>> imagesSyntheticInput; 

    void SetUp() override {

        kernel = std::make_shared<Kernel>();
        adapter = std::make_shared<OpenCVAdapter>();
        algorithmFactory = AlgorithmFactory::getInstance();
        zeroCrossing = algorithmFactory->getAlgorithm<IZeroCrossing<B>>(algorithmType);

        numOfImages = 1;
        minHeight = 2015;
        minWidth = 3060;
        growthFactor = 0;
        slope = 1.f;
        zeroCrossingExpected = 0.15f;
        configParams.threshold = 0.015f;

    }

};
#endif