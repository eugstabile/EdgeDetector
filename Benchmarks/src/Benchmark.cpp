#include <algorithm>
#include <chrono>
#include <fstream>
#include <iosfwd>
#include <sstream>
#include <iostream>
#include <cmath>

#include "EdgeDetectorException.h"
#include "Benchmark.h"

#define TEMPLATE_INIT(T) \
    template Benchmark<T>::Benchmark(int iterations, const std::vector<T>& imagesInput, const std::string& funcline);   \
    template void Benchmark<T>::setIterations(int iterations);                                                          \
    template void Benchmark<T>::setImages(const std::vector<T>& images);                                                \
    template void Benchmark<T>::setProcType(const AlgorithmFactory::AlgorithmType procType);                            \
    template void Benchmark<T>::setMatrixSize(size_t height, size_t width, size_t channels);                            \
    template void Benchmark<T>::setFuncline(const std::string& funcline);                                               \
    template void Benchmark<T>::setComment(const std::string& comment);                                                 \
    template std::vector<T>& Benchmark<T>::getImagesInput();                                                            \
    template std::string& Benchmark<T>::getComment();                                                                   \
    template BENCH_TYPE Benchmark<T>::benchmarkLambda(std::function<void()>& lambda);                                   \
    template void Benchmark<T>::compute(std::function<void(T)>& lambdaContext, std::function<void()>& lambda);          \
    template void Benchmark<T>::calculateTime(BENCH_TYPE sum, std::vector<uint64_t>& results);                          \
    template void Benchmark<T>::saveResult();                                                                           \
    template void Benchmark<T>::substractNames(std::string& pathMethod);

TEMPLATE_INIT(std::string)
TEMPLATE_INIT(std::shared_ptr<Buffer>)
TEMPLATE_INIT(std::shared_ptr<BufferTVM>)

enum MatrixDims { 
    HEIGHT = 0, 
    WIDTH = 1, 
    CHANNELS = 2 
};


template <typename T>
Benchmark<T>::Benchmark(int iterations, const std::vector<T>& imagesInput,
                        const std::string& funcline) {

    setIterations(iterations);
    setImages(imagesInput);
    setFuncline(funcline);

}


template <typename T> 
void Benchmark<T>::setIterations(int iterations) {
  
    iterations_ = iterations;

}


template <typename T> 
void Benchmark<T>::setImages(const std::vector<T>& images) {

    imagesInput_ = images;

}


template <typename T>
void Benchmark<T>::setProcType(const AlgorithmFactory::AlgorithmType procTypeId) {

    procTypeId_ = procTypeId;

}


template <typename T>
void Benchmark<T>::setMatrixSize(size_t height, size_t width, size_t channels) {

    std::get<MatrixDims::HEIGHT>(matrixSize_) = height;
    std::get<MatrixDims::WIDTH>(matrixSize_) = width;
    std::get<MatrixDims::CHANNELS>(matrixSize_) = channels;

    results_[matrixSize_];

}


template <typename T> 
void Benchmark<T>::setFuncline(const std::string& funcline) {

    funcline_ = funcline;

}


template <typename T> 
void Benchmark<T>::setComment(const std::string& comment) {

    comment_ = ", " + std::string(comment);

}


template <typename T> 
std::vector<T>& Benchmark<T>::getImagesInput() {

    return imagesInput_;

}


template <typename T> 
std::string& Benchmark<T>::getComment() { 
  
    return comment_; 
  
}


template <typename T>
BENCH_TYPE Benchmark<T>::benchmarkLambda(std::function<void()>& lambda) {

    auto start = std::chrono::high_resolution_clock::now();
    lambda();
    auto stop = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();

    return static_cast<BENCH_TYPE>(duration);

}


template <typename T>
void Benchmark<T>::compute(std::function<void(T)>& lambdaContext, std::function<void()>& lambda) {

    BENCH_TYPE sum;
    std::vector<uint64_t> results;

    for (auto&& image : imagesInput_) {
        
        sum = 0ULL;
        results.reserve(iterations_);
        
        lambdaContext(image);

        lambda();
        lambda();
        lambda();
        
        for (int i = 0; i < iterations_; ++i) {

            BENCH_TYPE&& res = benchmarkLambda(lambda);
            sum += res;
            results.push_back(static_cast<size_t>(res));

        }

        calculateTime(sum, results);

    }

    saveResult();

}


template <typename T>
void Benchmark<T>::calculateTime(BENCH_TYPE sum, std::vector<uint64_t>& results) {

    static constexpr float32_t zScore{1.96f};
    
    BENCH_TYPE mean = static_cast<BENCH_TYPE>(sum / iterations_);
    float32_t stdDev = 0.0f;
    BENCH_TYPE variance = 0.0;

    for (const auto &result :results) {

        variance += pow(result - mean, 2);

    }

    variance /= iterations_;

    stdDev = static_cast<float>(std::sqrt(variance));

    float32_t errorMargin = zScore * (stdDev / std::sqrt(static_cast<float32_t>(iterations_)));

    std::sort(results.begin(), results.end());
    const size_t resultSize = results.size();
    const size_t resultCenter = results.size() / 2;
    
    BENCH_TYPE median = resultSize % 2 == 0 ?
                        static_cast<BENCH_TYPE>(results[(resultSize - 1) / 2] + results[resultCenter]) / 2 :
                        results[resultCenter];

    auto it = results_.find(matrixSize_);
    
    if (it != results_.end()) {

        it->second.resultMean += mean;
        it->second.resultMedian += median;
        it->second.resultErrorMargin += errorMargin;
        it->second.resultStd += stdDev;
        it->second.numImages += 1;

    } else {

        MathResult valueMap{};
        valueMap.resultMean = mean;
        valueMap.resultMedian = median;
        valueMap.resultErrorMargin = errorMargin;
        valueMap.resultStd = stdDev;
        valueMap.numImages = 1;
        results_.insert(std::make_pair(matrixSize_, valueMap));

    }
  
}


template <typename T> 
void Benchmark<T>::saveResult() {

    substractNames(funcline_);

    int64_t procTypeId = static_cast<int64_t>(procTypeId_);
    std::string procType;
    
    switch (procTypeId) {
        case 0:
            procType = "CPU";
            break;
        case 1:
            procType = "OPEN_MP";
            break;
        case 2:
            procType = "TVM";
            break;
        case 3:
            procType = "OPEN_CL";
            break;            
        default:
            procType = "WRONG_PROCESSOR";
            THROW_EXCEPTION("Wrong processor type selected.");
            break;
    }

    
    unsigned int numImages;
    size_t height;
    size_t width;
    size_t channels;
    std::string stringChannels;
    std::string configuration;

    std::fstream file;
    std::stringstream md;
    std::string fileName = "Benchmarking.md";

    file.open(fileName.c_str(), std::ios::in | std::ios::out | std::ios::app);

    if (!file.is_open()) {
        THROW_EXCEPTION("Error opening benchmarking file.");
    }   

    file.seekg(0, std::ios::end);

    if (file.tellg() == 0) {

        file << "| Algorithm | Configuration | Num Images | Matrix size (MxN) | Num Iterations | "
             << "Median duration (us) | Avg duration (us) | Margin error +- (us) | Std Deviation (us) |\n"
             << "| --------- | ------------- | ---------- | ----------------- | -------------- | "
             << "-------------------- | ----------------- | -------------------- | ------------------ |\n";

    }

    for (const auto& [matrix, result] : results_) {
        
        numImages = result.numImages;
        
        height = std::get<MatrixDims::HEIGHT>(matrix);
        width = std::get<MatrixDims::WIDTH>(matrix);
        channels = std::get<MatrixDims::CHANNELS>(matrix);
        
        stringChannels = (channels == 1) ? "" : " x " + std::to_string(channels);
        configuration = procType + comment_;

        file                << " | " 
        << funcline_        << " | " 
        << configuration    << " | "
        << "Images processed: " 
        << numImages        << " | " 
        << height           << " x " 
        << width 
        << stringChannels   << " | " 
        << iterations_      << " | "
        << static_cast<int>(std::floor(result.resultMedian / numImages))        << " | "
        << static_cast<int>(std::floor(result.resultMean / numImages))          << " | "
        << static_cast<int>(std::floor(result.resultErrorMargin / numImages))   << " | "
        << static_cast<int>(std::floor(result.resultStd / numImages))           << " |\n";

    }

    file.close();

}


template<typename T>
void Benchmark<T>::substractNames(std::string& pathMethod) {

	std::string result;
	constexpr char benchmark_prefix[] = "benchmark_";
    constexpr char test_suffix[] = "_Test";
    constexpr size_t offset = sizeof(benchmark_prefix) - 1;
    
    if (auto startPos = pathMethod.find(benchmark_prefix); startPos != std::string::npos) {
        if (auto endPos = pathMethod.find(test_suffix, startPos + offset); endPos != std::string::npos) {
            result = pathMethod.substr(startPos + offset, endPos - (startPos + offset));
        }
    }
    
    pathMethod = result;
}