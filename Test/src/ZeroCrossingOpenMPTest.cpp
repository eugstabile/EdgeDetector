#include "EdgeDetectorException.h"
#include "ZeroCrossingTest.h"
#include "ZeroCrossingOpenMP.h"

constexpr Buffer::DimsIndex WIDTH = Buffer::DimsIndex::WIDTH;
constexpr Buffer::DimsIndex HEIGHT = Buffer::DimsIndex::HEIGHT;
constexpr AlgorithmFactory::AlgorithmType ZERO_CROSSING_CPU = AlgorithmFactory::AlgorithmType::ZERO_CROSSING_CPU;
constexpr AlgorithmFactory::AlgorithmType ZERO_CROSSING_OPEN_MP = AlgorithmFactory::AlgorithmType::ZERO_CROSSING_OPEN_MP;

using VALID_TYPE = Buffer;
using ZeroCrossingOpenMPTest = ZeroCrossingTest<ZeroCrossingOpenMP, VALID_TYPE>;

INSTANTIATE_TEST_SUITE_P(ZeroCrossingTest, ZeroCrossingOpenMPTest, ::testing::Values(std::make_tuple(ZERO_CROSSING_OPEN_MP, "OPEN_MP")));


TEST_P(ZeroCrossingOpenMPTest, zeroCrossingOpenMP_compute_syntheticMatrix_success) {

    syntheticMatrix = std::make_shared<SyntheticMatrix>(height, width, slope, zeroCrossingExpected);
    
    std::shared_ptr<VALID_TYPE> inBuffer = syntheticMatrix->getSyntheticMatrix();
    std::shared_ptr<VALID_TYPE> outBuffer = std::make_shared<VALID_TYPE>(height, width);
    bool throwException = false;

    try {

        adapter->saveImage(inBuffer, syntheticPath_);
        zeroCrossing->settingArguments(inBuffer, outBuffer, configParams);
        zeroCrossing->compute(inBuffer, outBuffer);
        adapter->saveImage(outBuffer, syntheticSavingPath_);
    
    } catch(EdgeDetectorException& e) {
    
        GTEST_LOG_(ERROR) << e.what() << std::endl;
        throwException = true;    

    }

    EXPECT_FALSE(throwException);

}


TEST_P(ZeroCrossingOpenMPTest, zeroCrossingOpenMP_compute_realImage_success) {

    bool throwException = false;

    try {

        std::shared_ptr<Buffer> inBuffer = adapter->obtainImage(path_);
        
        height = inBuffer->getDims()[HEIGHT];
        width = inBuffer->getDims()[WIDTH];
        std::shared_ptr<VALID_TYPE> outBuffer = std::make_shared<VALID_TYPE>(height, width);

        zeroCrossing->settingArguments(inBuffer, outBuffer, configParams);
        zeroCrossing->compute(inBuffer, outBuffer);
        adapter->saveImage(outBuffer, savingPath_);
    
    } catch(EdgeDetectorException& e) {

        GTEST_LOG_(ERROR) << e.what() << std::endl;
        throwException = true;    

    }

    EXPECT_FALSE(throwException);

}


TEST_P(ZeroCrossingOpenMPTest, compute_invalidInputSize_exceptionExpected) {

    syntheticMatrix = std::make_shared<SyntheticMatrix>(height, width, slope, zeroCrossingExpected);
    
    std::shared_ptr<VALID_TYPE> inBuffer = std::make_shared<VALID_TYPE>(0, 0);
    std::shared_ptr<VALID_TYPE> outBuffer = std::make_shared<VALID_TYPE>(height, width);
    bool throwException = false;

    try {

        zeroCrossing->settingArguments(inBuffer, outBuffer, configParams);
        zeroCrossing->compute(inBuffer, outBuffer);
    
    } catch(EdgeDetectorException&) {

        throwException = true;    

    }

    EXPECT_TRUE(throwException);

}


TEST_P(ZeroCrossingOpenMPTest, compute_inputNotSameAsOutput_exceptionExpected) {

    syntheticMatrix = std::make_shared<SyntheticMatrix>(height, width, slope, zeroCrossingExpected);
    
    std::shared_ptr<VALID_TYPE> inBuffer = std::make_shared<VALID_TYPE>(height, width);
    std::shared_ptr<VALID_TYPE> outBuffer = std::make_shared<VALID_TYPE>(height - 1, width - 1);
    bool throwException = false;

    try {

        zeroCrossing->settingArguments(inBuffer, outBuffer, configParams);
        zeroCrossing->compute(inBuffer, outBuffer);
    
    } catch(EdgeDetectorException&) {

        throwException = true;    

    }

    EXPECT_TRUE(throwException);

}


TEST_P(ZeroCrossingOpenMPTest, compute_invalidCheckParams_exceptionExpected) {

    syntheticMatrix = std::make_shared<SyntheticMatrix>(height, width, slope, zeroCrossingExpected);
    
    std::shared_ptr<VALID_TYPE> inBuffer = syntheticMatrix->getSyntheticMatrix();
    std::shared_ptr<VALID_TYPE> outBuffer = std::make_shared<VALID_TYPE>(height, width);
    bool throwException = false;

    const float INVALID_THRESHOLD = -1.0f;
    configParams.threshold = INVALID_THRESHOLD;

    try {

        zeroCrossing->settingArguments(inBuffer, outBuffer, configParams);
        zeroCrossing->compute(inBuffer, outBuffer);
    
    } catch(EdgeDetectorException&) {

        throwException = true;    

    }

    EXPECT_TRUE(throwException);

}


TEST_P(ZeroCrossingOpenMPTest, zeroCrossingOpenMP_validate_SyntheticMatrix_Horizontal_success) {

    slope = 0.f;
    syntheticMatrix = std::make_shared<SyntheticMatrix>(height, width, slope, zeroCrossingExpected);
    
    std::shared_ptr<VALID_TYPE> inBuffer = syntheticMatrix->getSyntheticMatrix();
    std::shared_ptr<VALID_TYPE> outBuffer = std::make_shared<VALID_TYPE>(height, width);
    bool throwException = false;

    try {

        zeroCrossing->settingArguments(inBuffer, outBuffer, configParams);
        zeroCrossing->compute(inBuffer, outBuffer);

        std::shared_ptr<VALID_TYPE> vertical = zeroCrossing->getZeroCrossingV();
        verifySynteticMatrixOutput(vertical, zeroCrossingExpected);
    
    } catch(EdgeDetectorException& e) {

        GTEST_LOG_(ERROR) << e.what() << std::endl;
        throwException = true;    

    }

    EXPECT_FALSE(throwException);

}


TEST_P(ZeroCrossingOpenMPTest, zeroCrossingOpenMP_validate_SyntheticMatrix_Vertical_success) {

    slope = 0.f;
    syntheticMatrix = std::make_shared<SyntheticMatrix>(height, width, slope, zeroCrossingExpected);
    
    std::shared_ptr<VALID_TYPE> inBuffer = syntheticMatrix->getSyntheticMatrix();
    std::shared_ptr<VALID_TYPE> inBufferTranspose = transpose(inBuffer);
    std::shared_ptr<VALID_TYPE> outBuffer = std::make_shared<VALID_TYPE>(width, height);
    bool throwException = false;

    try {

        zeroCrossing->settingArguments(inBufferTranspose, outBuffer, configParams);
        zeroCrossing->compute(inBufferTranspose, outBuffer);

        std::shared_ptr<VALID_TYPE> horizontal = zeroCrossing->getZeroCrossingH();
        verifySynteticMatrixOutput(horizontal, zeroCrossingExpected);
    
    } catch(EdgeDetectorException& e) {

        GTEST_LOG_(ERROR) << e.what() << std::endl;
        throwException = true;    

    }

    EXPECT_FALSE(throwException);

}


TEST_P(ZeroCrossingOpenMPTest, zeroCrossingOpenMP_compute_sameOutputAsCPU) {


    std::shared_ptr<VALID_TYPE> inBuffer = adapter->obtainImage(path_);
    
    height = inBuffer->getDims()[HEIGHT];
    width = inBuffer->getDims()[WIDTH];
    bool throwException = false;

    std::shared_ptr<VALID_TYPE> outBufferOpenMP = std::make_shared<VALID_TYPE>(height, width);
    std::shared_ptr<VALID_TYPE> outBufferCpu = std::make_shared<VALID_TYPE>(height, width);
    
    try {

        zeroCrossing->settingArguments(inBuffer, outBufferOpenMP, configParams);
        zeroCrossing->compute(inBuffer, outBufferOpenMP);

        std::shared_ptr<Buffer> zeroCrossingOpenMPH = zeroCrossing->getZeroCrossingH();
        std::shared_ptr<Buffer> zeroCrossingOpenMPV = zeroCrossing->getZeroCrossingV();

        
        zeroCrossing = algorithmFactory->getAlgorithm<IZeroCrossing<VALID_TYPE>>(ZERO_CROSSING_CPU);
        zeroCrossing->settingArguments(inBuffer, outBufferCpu, configParams);
        zeroCrossing->compute(inBuffer, outBufferCpu);
        
        std::shared_ptr<Buffer> zeroCrossingCPUH = zeroCrossing->getZeroCrossingH();
        std::shared_ptr<Buffer> zeroCrossingCPUV = zeroCrossing->getZeroCrossingV();

        verifyOutput(zeroCrossingCPUH, zeroCrossingOpenMPH);
        verifyOutput(zeroCrossingCPUV, zeroCrossingOpenMPV);
        verifyOutput(outBufferCpu, outBufferOpenMP);
    
    } catch(EdgeDetectorException &e) {

        GTEST_LOG_(ERROR) << e.what() << std::endl;
        throwException = true;    

    }

    EXPECT_FALSE(throwException);

}