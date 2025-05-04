#include "EdgeDetectorException.h"
#include "ZeroCrossingTest.h"
#include "ZeroCrossingCPU.h"



constexpr Buffer::DimsIndex WIDTH = Buffer::DimsIndex::WIDTH;
constexpr Buffer::DimsIndex HEIGHT = Buffer::DimsIndex::HEIGHT;
constexpr AlgorithmFactory::AlgorithmType ZERO_CROSSING = AlgorithmFactory::AlgorithmType::ZERO_CROSSING_CPU;

using VALID_TYPE = Buffer;
using ZeroCrossingCPUTest = ZeroCrossingTest<ZeroCrossingCPU, VALID_TYPE>;


INSTANTIATE_TEST_SUITE_P(ZeroCrossingTest, ZeroCrossingCPUTest, ::testing::Values(std::make_tuple(ZERO_CROSSING, "CPU")));


TEST_P(ZeroCrossingCPUTest, zeroCrossingCPU_compute_syntheticMatrix_success) {

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


TEST_P(ZeroCrossingCPUTest, zeroCrossingCPU_compute_realImage_success) {

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


TEST_P(ZeroCrossingCPUTest, compute_invalidInputSize_exceptionExpected) {

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


TEST_P(ZeroCrossingCPUTest, compute_inputNotSameAsOutput_exceptionExpected) {

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


TEST_P(ZeroCrossingCPUTest, compute_invalidCheckParams_exceptionExpected) {

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


TEST_P(ZeroCrossingCPUTest, zeroCrossingCPU_validate_SyntheticMatrix_Horizontal_success) {

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


TEST_P(ZeroCrossingCPUTest, zeroCrossingCPU_validate_SyntheticMatrix_Vertical_success) {

    slope = 0.f;
    syntheticMatrix = std::make_shared<SyntheticMatrix>(height, width, slope, zeroCrossingExpected);
    
    std::shared_ptr<VALID_TYPE> inBuffer = syntheticMatrix->getSyntheticMatrix();
    std::shared_ptr<VALID_TYPE> inBufferTranspose = transpose(inBuffer);
    std::shared_ptr<VALID_TYPE> outBuffer = std::make_shared<VALID_TYPE>(width, height);
    bool throwException = false;
    //auto zeroCrossingCPU = std::dynamic_pointer_cast<IZeroCrossing<Buffer>>(zeroCrossing);

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