/**
 * @file Benchmark.h
 * @author Eugenio Stabile (eugenio.stabile@photonicsens.com)
 * @brief Measure times on all algortihms
 * @version 2.0.0
 * @date 2023-11-07
 * 
 * Copyright (c) 2024, Photonicsens. All rights reserved.
 * 
 */

#pragma once

#ifndef _BENCHMARK_H
#define _BENCHMARK_H

#include <map>
#include <functional>

#include "AlgorithmFactory.h"

typedef float32_t BENCH_TYPE;

struct MathResult {
    BENCH_TYPE resultMean;
    BENCH_TYPE resultMedian;
    float resultErrorMargin;
    float resultStd;
    unsigned int numImages;
};

template <class T = std::string> class Benchmark {

protected:

public:

    Benchmark(int iterations, const std::vector<T>& imagesInput,
                std::string& funcline);
    ~Benchmark() = default;

    // Setters
    void setIterations(const int iterations);
    void setImages(const std::vector<T>& images);
    void setProcType(const AlgorithmFactory::AlgorithmType procType);
    void setMatrixSize(size_t height, size_t width, size_t channels = 1);
    void setFuncline(std::string& funcline);
    void setComment(std::string& comment);

    // Getters
    std::vector<T>& getImagesInput();
    std::string& getComment();

    // Generate values
    void compute(std::function<void(T)>& lambdaContext, std::function<void()>& lambda);

private:

    int iterations_;
    std::vector<T> imagesInput_;
    std::string funcline_;
    std::string comment_;
    AlgorithmFactory::AlgorithmType procTypeId_;

    MathResult valueMap_;
    std::tuple<size_t, size_t, size_t> matrixSize_;
    std::map<std::tuple<size_t, size_t, size_t>, MathResult> results_;

    BENCH_TYPE benchmarkLambda(std::function<void()>& lambda);
    void calculateTime(BENCH_TYPE sum, std::vector<uint64_t>& results);
    void saveResult();
    void substractNames(std::string& pathMethod);

};

#endif //BENCHMARK_H