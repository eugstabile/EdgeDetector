#include "ZeroCrossingBenchmark.h"
#include "ZeroCrossingCPU.h"
#include "ZeroCrossingOpenCL.h"
#include "ZeroCrossingOpenMP.h"
#include "ZeroCrossingTVM.h"

#ifdef _WIN32
    #define FUNC_NAME __FUNCSIG__
#else
    #define FUNC_NAME __PRETTY_FUNCTION__
#endif

constexpr Buffer::DimsIndex WIDTH = Buffer::DimsIndex::WIDTH;
constexpr Buffer::DimsIndex HEIGHT = Buffer::DimsIndex::HEIGHT;
constexpr AlgorithmFactory::AlgorithmType ZERO_CROSSING_CPU = AlgorithmFactory::AlgorithmType::ZERO_CROSSING_CPU;
constexpr AlgorithmFactory::AlgorithmType ZERO_CROSSING_OPEN_MP = AlgorithmFactory::AlgorithmType::ZERO_CROSSING_OPEN_MP;
constexpr AlgorithmFactory::AlgorithmType ZERO_CROSSING_TVM = AlgorithmFactory::AlgorithmType::ZERO_CROSSING_TVM;
constexpr AlgorithmFactory::AlgorithmType ZERO_CROSSING_OPENCL = AlgorithmFactory::AlgorithmType::ZERO_CROSSING_OPENCL;

const std::string relativePath_ = "Resources/images/";

const std::string CHESS =      relativePath_ + "ajedrez";
const std::string PARROT =     relativePath_ + "parrot";
const std::string WORDS =      relativePath_ + "words";
const std::string FIGURE =     relativePath_ + "figure";
const std::string MOON =       relativePath_ + "moon";

const std::vector<std::string> imagesInput = {CHESS, PARROT, WORDS, MOON};
//const std::vector<std::string> imagesInput = {PARROT, FIGURE, MOON};

constexpr int ITERATIONS = 20;

using ZeroCrossingCPUBenchmark = ZeroCrossingBenchmark<ZeroCrossingCPU, Buffer>;


INSTANTIATE_TEST_SUITE_P(ZeroCrossingBenchmark, ZeroCrossingCPUBenchmark, ::testing::Values(ZERO_CROSSING_CPU));

TEST_P(ZeroCrossingCPUBenchmark, benchmark_zeroCrossing_realImage) {

    const std::string& algorithm = FUNC_NAME;
    benchmark = std::make_shared<Benchmark<std::string>>(ITERATIONS, imagesInput, algorithm);

    std::function<void(std::string)> lambdaContext = [&](const std::string& image) {
        
        bufferIn = adapter->obtainImage(image);
        height = bufferIn->getDims()[HEIGHT];
        width = bufferIn->getDims()[WIDTH];
        bufferOut = std::make_shared<Buffer>(height, width);

        benchmark->setMatrixSize(static_cast<size_t>(height), static_cast<size_t>(width));
        benchmark->setProcType(GetParam());
        zeroCrossing->settingArguments(bufferIn, bufferOut, configParams);

    };

    std::function<void()> lambda = [&]() { 
    
        zeroCrossing->compute(bufferIn, bufferOut); 

    };

    try{

        benchmark->compute(lambdaContext, lambda);

    }catch(EdgeDetectorException& e){

        GTEST_LOG_(ERROR) << e.what() << std::endl;
        FAIL();

    }

}


TEST_P(ZeroCrossingCPUBenchmark, benchmark_zeroCrossing_syntheticImage) {

    syntheticMatrix = std::make_shared<SyntheticMatrix>(numOfImages, minHeight, minWidth, growthFactor);
    imagesSyntheticInput = syntheticMatrix->getSyntheticMultipleMatrix();

    const std::string& algorithm = FUNC_NAME;
    benchmarkSynthetic = std::make_shared<Benchmark<std::shared_ptr<Buffer>>>(ITERATIONS, imagesSyntheticInput, algorithm);

    std::function<void(std::shared_ptr<Buffer>)> lambdaContext = [&](const std::shared_ptr<Buffer>& inputImage) {
        
        bufferIn = inputImage;
        height = bufferIn->getDims()[HEIGHT];
        width = bufferIn->getDims()[WIDTH];
        bufferOut = std::make_shared<Buffer>(height, width);

        benchmarkSynthetic->setMatrixSize(static_cast<size_t>(height), static_cast<size_t>(width));
        benchmarkSynthetic->setProcType(GetParam());
 
        zeroCrossing->settingArguments(bufferIn, bufferOut, configParams);

    };

    std::function<void()> lambda = [&]() { 
    
        zeroCrossing->compute(bufferIn, bufferOut); 

    };

    try{

        benchmarkSynthetic->compute(lambdaContext, lambda);

    } catch(EdgeDetectorException& e) {

        GTEST_LOG_(ERROR) << e.what() << std::endl;
        FAIL();

    }

}


using ZeroCrossingOpenMPBenchmark = ZeroCrossingBenchmark<ZeroCrossingOpenMP, Buffer>;


INSTANTIATE_TEST_SUITE_P(ZeroCrossingBenchmark, ZeroCrossingOpenMPBenchmark, ::testing::Values(ZERO_CROSSING_OPEN_MP));


TEST_P(ZeroCrossingOpenMPBenchmark, benchmark_zeroCrossing_realImage) {

    const std::string& algorithm = FUNC_NAME;
    benchmark = std::make_shared<Benchmark<std::string>>(ITERATIONS, imagesInput, algorithm);

    std::function<void(std::string)> lambdaContext = [&](const std::string& image) {
        
        bufferIn = adapter->obtainImage(image);
        height = bufferIn->getDims()[HEIGHT];
        width = bufferIn->getDims()[WIDTH];
        bufferOut = std::make_shared<Buffer>(height, width);

        benchmark->setMatrixSize(static_cast<size_t>(height), static_cast<size_t>(width));
        benchmark->setProcType(GetParam());
        zeroCrossing->settingArguments(bufferIn, bufferOut, configParams);

    };

    std::function<void()> lambda = [&]() { 
    
        zeroCrossing->compute(bufferIn, bufferOut); 

    };

    try{

        benchmark->compute(lambdaContext, lambda);

    } catch(EdgeDetectorException& e) {

        GTEST_LOG_(ERROR) << e.what() << std::endl;
        FAIL();

    }

}


TEST_P(ZeroCrossingOpenMPBenchmark, benchmark_zeroCrossing_syntheticImage) {

    syntheticMatrix = std::make_shared<SyntheticMatrix>(numOfImages, minHeight, minWidth, growthFactor);
    imagesSyntheticInput = syntheticMatrix->getSyntheticMultipleMatrix();

    const std::string& algorithm = FUNC_NAME;
    benchmarkSynthetic = std::make_shared<Benchmark<std::shared_ptr<Buffer>>>(ITERATIONS, imagesSyntheticInput, algorithm);

    std::function<void(std::shared_ptr<Buffer>)> lambdaContext = [&](const std::shared_ptr<Buffer>& inputImage) {
        
        bufferIn = inputImage;
        height = bufferIn->getDims()[HEIGHT];
        width = bufferIn->getDims()[WIDTH];
        bufferOut = std::make_shared<Buffer>(height, width);

        benchmarkSynthetic->setMatrixSize(static_cast<size_t>(height), static_cast<size_t>(width));
        benchmarkSynthetic->setProcType(GetParam());

        zeroCrossing->settingArguments(bufferIn, bufferOut, configParams);

    };

    std::function<void()> lambda = [&]() { 
    
        zeroCrossing->compute(bufferIn, bufferOut); 

    };

    try{

        benchmarkSynthetic->compute(lambdaContext, lambda);

    } catch(EdgeDetectorException& e) {

        GTEST_LOG_(ERROR) << e.what() << std::endl;
        FAIL();

    }

}


using ZeroCrossingTVMBenchmark = ZeroCrossingBenchmark<ZeroCrossingTVM, BufferTVM>;


INSTANTIATE_TEST_SUITE_P(ZeroCrossingBenchmark, ZeroCrossingTVMBenchmark, ::testing::Values(ZERO_CROSSING_TVM));


TEST_P(ZeroCrossingTVMBenchmark, benchmark_zeroCrossing_realImage) {

    const std::string& algorithm = FUNC_NAME;
    benchmark = std::make_shared<Benchmark<std::string>>(ITERATIONS, imagesInput, algorithm);

    std::function<void(std::string)> lambdaContext = [&](const std::string& image) {
        
        std::shared_ptr<Buffer> in = adapter->obtainImage(image);
        std::shared_ptr<TVMAdapter> tvmAdapter = std::make_shared<TVMAdapter>();
        
        bufferIn = tvmAdapter->bufferToTVM(in);
        height = bufferIn->getDims()[HEIGHT];
        width = bufferIn->getDims()[WIDTH];
        bufferOut = std::make_shared<BufferTVM>(height, width);

        benchmark->setMatrixSize(static_cast<size_t>(height), static_cast<size_t>(width));
        benchmark->setProcType(GetParam());
        zeroCrossing->settingArguments(bufferIn, bufferOut, configParams);

    };

    std::function<void()> lambda = [&]() { 
    
        zeroCrossing->compute(bufferIn, bufferOut); 

    };

    try{

        benchmark->compute(lambdaContext, lambda);

    } catch(EdgeDetectorException& e) {

        GTEST_LOG_(ERROR) << e.what() << std::endl;
        FAIL();

    }

}


TEST_P(ZeroCrossingTVMBenchmark , benchmark_zeroCrossing_syntheticImage) {

    syntheticMatrix = std::make_shared<SyntheticMatrix>(numOfImages, minHeight, minWidth, growthFactor);
    imagesSyntheticInput = syntheticMatrix->getSyntheticMultipleMatrix();
    std::shared_ptr<TVMAdapter> tvmAdapter = std::make_shared<TVMAdapter>();

    std::vector<std::shared_ptr<BufferTVM>> imagesSyntheticInputTVM;

    for (size_t i = 0; i < imagesSyntheticInput.size(); ++i) {

        imagesSyntheticInputTVM.push_back(tvmAdapter->bufferToTVM(imagesSyntheticInput[i]));

    }

    const std::string& algorithm = FUNC_NAME;

    benchmarkSynthetic = std::make_shared<Benchmark<std::shared_ptr<BufferTVM>>>(ITERATIONS, imagesSyntheticInputTVM, algorithm);

    std::function<void(std::shared_ptr<BufferTVM>)> lambdaContext = [&](const std::shared_ptr<BufferTVM>& inputImage) {
        
        bufferIn = inputImage;
        height = bufferIn->getDims()[HEIGHT];
        width = bufferIn->getDims()[WIDTH];
        bufferOut = std::make_shared<BufferTVM>(height, width);

        benchmarkSynthetic->setMatrixSize(static_cast<size_t>(height), static_cast<size_t>(width));
        benchmarkSynthetic->setProcType(GetParam());

        zeroCrossing->settingArguments(bufferIn, bufferOut, configParams);

    };

    std::function<void()> lambda = [&]() { 
    
        zeroCrossing->compute(bufferIn, bufferOut); 

    };

    try{

        benchmarkSynthetic->compute(lambdaContext, lambda);

    } catch(EdgeDetectorException& e) {

        GTEST_LOG_(ERROR) << e.what() << std::endl;
        FAIL();

    }

}


using ZeroCrossingOpenCLBenchmark = ZeroCrossingBenchmark<ZeroCrossingOpenCL, Buffer>;


INSTANTIATE_TEST_SUITE_P(ZeroCrossingBenchmark, ZeroCrossingOpenCLBenchmark, ::testing::Values(ZERO_CROSSING_OPENCL));

TEST_P(ZeroCrossingOpenCLBenchmark, benchmark_zeroCrossing_realImage) {

    const std::string& algorithm = FUNC_NAME;
    benchmark = std::make_shared<Benchmark<std::string>>(ITERATIONS, imagesInput, algorithm);

    std::function<void(std::string)> lambdaContext = [&](const std::string& image) {
        
        bufferIn = adapter->obtainImage(image);
        height = bufferIn->getDims()[HEIGHT];
        width = bufferIn->getDims()[WIDTH];
        bufferOut = std::make_shared<Buffer>(height, width);

        benchmark->setMatrixSize(static_cast<size_t>(height), static_cast<size_t>(width));
        benchmark->setProcType(GetParam());
        zeroCrossing->settingArguments(bufferIn, bufferOut, configParams);

    };

    std::function<void()> lambda = [&]() { 
    
        zeroCrossing->compute(bufferIn, bufferOut); 

    };

    try{

        benchmark->compute(lambdaContext, lambda);

    } catch(EdgeDetectorException& e) {

        GTEST_LOG_(ERROR) << e.what() << std::endl;
        FAIL();

    }

}


TEST_P(ZeroCrossingOpenCLBenchmark, benchmark_zeroCrossing_syntheticImage) {

    syntheticMatrix = std::make_shared<SyntheticMatrix>(numOfImages, minHeight, minWidth, growthFactor);
    imagesSyntheticInput = syntheticMatrix->getSyntheticMultipleMatrix();

    const std::string& algorithm = FUNC_NAME;
    benchmarkSynthetic = std::make_shared<Benchmark<std::shared_ptr<Buffer>>>(ITERATIONS, imagesSyntheticInput, algorithm);

    std::function<void(std::shared_ptr<Buffer>)> lambdaContext = [&](const std::shared_ptr<Buffer>& inputImage) {
        
        bufferIn = inputImage;
        height = bufferIn->getDims()[HEIGHT];
        width = bufferIn->getDims()[WIDTH];
        bufferOut = std::make_shared<Buffer>(height, width);

        benchmarkSynthetic->setMatrixSize(static_cast<size_t>(height), static_cast<size_t>(width));
        benchmarkSynthetic->setProcType(GetParam());
 
        zeroCrossing->settingArguments(bufferIn, bufferOut, configParams);

    };

    std::function<void()> lambda = [&]() { 
    
        zeroCrossing->compute(bufferIn, bufferOut); 

    };

    try{

        benchmarkSynthetic->compute(lambdaContext, lambda);

    } catch(EdgeDetectorException& e) {

        GTEST_LOG_(ERROR) << e.what() << std::endl;
        FAIL();

    }

}