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
    template Benchmark<T>::Benchmark(int iterations, const std::vector<T>& imagesInput, std::string& funcline);\
    template void Benchmark<T>::setIterations(int iterations);                                                 \
    template void Benchmark<T>::setImages(const std::vector<T>& images);                                       \
    template void Benchmark<T>::setProcType(const AlgorithmFactory::AlgorithmType procType);                   \
    template void Benchmark<T>::setMatrixSize(size_t height, size_t width, size_t channels);                   \
    template void Benchmark<T>::setFuncline(std::string& funcline);                                            \
    template void Benchmark<T>::setComment(std::string& comment);                                              \
    template std::vector<T>& Benchmark<T>::getImagesInput();                                                   \
    template std::string& Benchmark<T>::getComment();                                                          \
    template BENCH_TYPE Benchmark<T>::benchmarkLambda(std::function<void()>& lambda);                          \
    template void Benchmark<T>::compute(std::function<void(T)>& lambdaContext, std::function<void()>& lambda); \
    template void Benchmark<T>::calculateTime(BENCH_TYPE sum, std::vector<uint64_t>& results);                 \
    template void Benchmark<T>::saveResult();                                                                  \
    template void Benchmark<T>::substractNames(std::string& pathMethod);

TEMPLATE_INIT(std::string)
TEMPLATE_INIT(std::shared_ptr<Buffer>)
TEMPLATE_INIT(std::shared_ptr<BufferTVM>)

enum MatrixDims { 
    HEIGHT = 0, 
    WIDTH = 1, 
    CHANNELS = 2 
};


template <class T>
Benchmark<T>::Benchmark(int iterations, const std::vector<T>& imagesInput,
                        std::string& funcline) {

    setIterations(iterations);
    setImages(imagesInput);
    setFuncline(funcline);

}


template <class T> 
void Benchmark<T>::setIterations(int iterations) {
  
    iterations_ = iterations;

}


template <class T> 
void Benchmark<T>::setImages(const std::vector<T>& images) {

    imagesInput_ = images;

}


template <class T>
void Benchmark<T>::setProcType(const AlgorithmFactory::AlgorithmType procTypeId) {

    procTypeId_ = procTypeId;

}


template <class T>
void Benchmark<T>::setMatrixSize(size_t height, size_t width, size_t channels) {

    std::get<MatrixDims::HEIGHT>(matrixSize_) = height;
    std::get<MatrixDims::WIDTH>(matrixSize_) = width;
    std::get<MatrixDims::CHANNELS>(matrixSize_) = channels;

    results_[matrixSize_];

}


template <class T> 
void Benchmark<T>::setFuncline(std::string& funcline) {

    funcline_ = funcline;

}


template <class T> 
void Benchmark<T>::setComment(std::string& comment) {

    comment_ = std::string(", " + comment);

}


template <class T> 
std::vector<T>& Benchmark<T>::getImagesInput() {

    return imagesInput_;

}


template <class T> 
std::string& Benchmark<T>::getComment() { 
  
    return comment_; 
  
}


template <class T>
BENCH_TYPE Benchmark<T>::benchmarkLambda(std::function<void()>& lambda) {

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    lambda();
    std::chrono::high_resolution_clock::time_point stop = std::chrono::high_resolution_clock::now();
    
    long long duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();

    return static_cast<BENCH_TYPE>(duration);

}


template <class T>
void Benchmark<T>::compute(std::function<void(T)>& lambdaContext, std::function<void()>& lambda) {

    BENCH_TYPE sum;
    std::vector<uint64_t> results;

    for (auto&& image : imagesInput_) {
        sum = 0ULL;
        results = std::vector<uint64_t>{};
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


template <class T>
void Benchmark<T>::calculateTime(BENCH_TYPE sum, std::vector<uint64_t>& results) {

    BENCH_TYPE mean = static_cast<BENCH_TYPE>(sum / iterations_);
    float32_t std = 0.0f;
    BENCH_TYPE desv = 0.0;
    const float32_t zScore = 1.96f;

    for (int i = 0; i < results.size(); i++) {
        desv += pow(results[i] - mean, 2);
    }

    BENCH_TYPE variance = desv / iterations_;

    std = static_cast<float>(std::sqrt(variance));

    float32_t errorMargin = zScore * (std / std::sqrt(static_cast<float32_t>(iterations_)));

    std::sort(results.begin(), results.end());
    size_t resultSize = results.size();
    size_t resultCenter = results.size() / 2;
    
    BENCH_TYPE median = resultSize % 2 == 0 ? static_cast<BENCH_TYPE>(results[(resultSize - 1) / 2] + results[resultCenter]) / 2 : results[resultCenter];

    if (results_.find(matrixSize_) != results_.end()) {
        results_[matrixSize_].resultMean += mean;
        results_[matrixSize_].resultMedian += median;
        results_[matrixSize_].resultErrorMargin += errorMargin;
        results_[matrixSize_].resultStd += std;
        results_[matrixSize_].numImages += 1;
    } else {
        MathResult valueMap{};
        valueMap.resultMean = mean;
        valueMap.resultMedian = median;
        valueMap.resultErrorMargin = errorMargin;
        valueMap.resultStd = std;
        valueMap.numImages = 1;
        results_.insert(std::make_pair(matrixSize_, valueMap));
    }
  
}


template <class T> 
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

#define SEPARATOR << "|" <<
#define LINEND SEPARATOR std::endl
#define PUTCELL(VALUE) SEPARATOR VALUE

#define HEADER                                                                      \
  SEPARATOR "	Algorithm			" SEPARATOR                                     \
            "	Configuration		" SEPARATOR                                     \
            "	Num Images			" SEPARATOR                                     \
            "	Matrix size	(MxN)	" SEPARATOR                                     \
            "	Num Iterations		" SEPARATOR                                     \
            "	Median duration (us)" SEPARATOR                                     \
            "	Avg duration (us)	" SEPARATOR                                     \
            "	Margin error +- (us)" SEPARATOR                                     \
            "	Std Deviation (us)	" LINEND

#define SUBHEADER                                                                   \
    SEPARATOR                                                                       \
    "-----------------------" SEPARATOR "-----------------------" SEPARATOR         \
    "-----------------------" SEPARATOR "-----------------------" SEPARATOR         \
    "-----------------------" SEPARATOR "-----------------------" SEPARATOR         \
    "-----------------------" SEPARATOR "-----------------------" SEPARATOR         \
    "-----------------------" LINEND

    std::fstream file = std::fstream();
    std::stringstream md = std::stringstream();
    std::string fileName = std::string("Benchmarking") + std::string(".md");

    file.open(fileName.c_str(), std::ios::in | std::ios::out | std::ios::app);

    file.seekg(0, std::ios::end);
    if (file.tellg() == 0) {
        md HEADER SUBHEADER;
        file << md.str();
    }

    for (const auto& image : results_) {
        numImages = image.second.numImages;
        height = std::get<MatrixDims::HEIGHT>(image.first);
        width = std::get<MatrixDims::WIDTH>(image.first);
        channels = std::get<MatrixDims::CHANNELS>(image.first);
        stringChannels = (channels == 1) ? "" : std::string(" x ") + std::to_string(channels);

        configuration = procType + comment_;

        file 
            PUTCELL(funcline_) 
            PUTCELL(configuration)
            PUTCELL("Images processed: " << numImages) 
            PUTCELL(height << " x " << width << stringChannels) 
            PUTCELL(iterations_)
            PUTCELL(floor(image.second.resultMedian / numImages))
            PUTCELL(floor(image.second.resultMean / numImages))
            PUTCELL(floor(image.second.resultErrorMargin / numImages))
            PUTCELL(floor(image.second.resultStd / numImages))
            LINEND;
    }

    file.close();

#undef SUBHEADER
#undef HEADER
#undef PUTCELL
#undef LINEND
#undef SEPARATOR
}


template<class T>
void Benchmark<T>::substractNames(std::string& pathMethod) {

	std::string result;
	std::size_t startPos = pathMethod.find("benchmark_");
    int offsetPos = 10;

	if (startPos != std::string::npos) {
		std::size_t endPos = pathMethod.find("_Test", startPos + offsetPos);
		if (endPos != std::string::npos) {
			result = pathMethod.substr(startPos + offsetPos, endPos - (startPos + offsetPos));
		}
	}

	pathMethod = result;
}