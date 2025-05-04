#include "EdgeDetectorException.h"
#include "ZeroCrossingTest.h"
#include "ZeroCrossingCPU.h"
#include "ZeroCrossingOpenCL.h"

constexpr Buffer::DimsIndex WIDTH = Buffer::DimsIndex::WIDTH;
constexpr Buffer::DimsIndex HEIGHT = Buffer::DimsIndex::HEIGHT;
constexpr AlgorithmFactory::AlgorithmType ZERO_CROSSING_CPU = AlgorithmFactory::AlgorithmType::ZERO_CROSSING_CPU;
constexpr AlgorithmFactory::AlgorithmType ZERO_CROSSING_OPENCL = AlgorithmFactory::AlgorithmType::ZERO_CROSSING_OPENCL;

using VALID_TYPE = Buffer;
using ZeroCrossingOpenCLTest = ZeroCrossingTest<ZeroCrossingOpenCL, VALID_TYPE>;

INSTANTIATE_TEST_SUITE_P(ZeroCrossingTest, ZeroCrossingOpenCLTest, ::testing::Values(std::make_tuple(ZERO_CROSSING_OPENCL, "OpenCL")));


TEST_P(ZeroCrossingOpenCLTest, zeroCrossingOpenCL_compute_syntheticMatrix_success) {

    syntheticMatrix = std::make_shared<SyntheticMatrix>(height, width, slope, zeroCrossingExpected);
    
    std::shared_ptr<Buffer> inBuffer = syntheticMatrix->getSyntheticMatrix();
    std::shared_ptr<OpenCLAdapter> openCLAdapter = std::make_shared<OpenCLAdapter>();

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


TEST_P(ZeroCrossingOpenCLTest, zeroCrossingOpenCL_compute_realImage_success) {

    bool throwException = false;

    try {
            
        std::shared_ptr<Buffer> inBuffer = adapter->obtainImage(path_);
        std::shared_ptr<OpenCLAdapter> openCLAdapter = std::make_shared<OpenCLAdapter>();

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


TEST_P(ZeroCrossingOpenCLTest, compute_invalidInputSize_exceptionExpected) {

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


TEST_P(ZeroCrossingOpenCLTest, compute_inputNotSameAsOutput_exceptionExpected) {

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


TEST_P(ZeroCrossingOpenCLTest, compute_invalidCheckParams_exceptionExpected) {

    syntheticMatrix = std::make_shared<SyntheticMatrix>(height, width, slope, zeroCrossingExpected);
    
    std::shared_ptr<Buffer> inBuffer = syntheticMatrix->getSyntheticMatrix();
    std::shared_ptr<OpenCLAdapter> openCLAdapter = std::make_shared<OpenCLAdapter>();

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


TEST_P(ZeroCrossingOpenCLTest, zeroCrossingOpenCL_validate_SyntheticMatrix_Horizontal_success) {

    slope = 0.f;
    syntheticMatrix = std::make_shared<SyntheticMatrix>(height, width, slope, zeroCrossingExpected);
    
    std::shared_ptr<Buffer> inBuffer = syntheticMatrix->getSyntheticMatrix();

    std::shared_ptr<VALID_TYPE> outBuffer = std::make_shared<VALID_TYPE>(height, width);
    bool throwException = false;

    try {

        zeroCrossing->settingArguments(inBuffer, outBuffer, configParams);
        zeroCrossing->compute(inBuffer, outBuffer);
        std::shared_ptr<VALID_TYPE> horizontal = zeroCrossing->getZeroCrossingH();
        verifySynteticMatrixOutput(horizontal, zeroCrossingExpected);
    
    } catch(EdgeDetectorException& e) {

        GTEST_LOG_(ERROR) << e.what() << std::endl;
        throwException = true;    

    }

    EXPECT_FALSE(throwException);

}


TEST_P(ZeroCrossingOpenCLTest, zeroCrossingOpenCL_validate_SyntheticMatrix_Vertical_success) {

    slope = 0.f;
    syntheticMatrix = std::make_shared<SyntheticMatrix>(height, width, slope, zeroCrossingExpected);
    
    std::shared_ptr<Buffer> inBuffer = syntheticMatrix->getSyntheticMatrix();

    std::shared_ptr<VALID_TYPE> outBuffer = std::make_shared<VALID_TYPE>(height, width);
    bool throwException = false;

    try {

        zeroCrossing->settingArguments(inBuffer, outBuffer, configParams);
        zeroCrossing->compute(inBuffer, outBuffer);
        std::shared_ptr<VALID_TYPE> vertical = zeroCrossing->getZeroCrossingH();
        verifySynteticMatrixOutput(vertical, zeroCrossingExpected);
    
    } catch(EdgeDetectorException& e) {

        GTEST_LOG_(ERROR) << e.what() << std::endl;
        throwException = true;    

    }

    EXPECT_FALSE(throwException);

}


TEST_P(ZeroCrossingOpenCLTest, zeroCrossingOpenCL_compute_sameOutputAsCPU) {


    std::shared_ptr<Buffer> inBuffer = adapter->obtainImage(path_);
    std::shared_ptr<OpenCLAdapter> openCLAdapter = std::make_shared<OpenCLAdapter>();

    height = inBuffer->getDims()[HEIGHT];
    width = inBuffer->getDims()[WIDTH];
    bool throwException = false;

    std::shared_ptr<VALID_TYPE> outBufferOpenCL = std::make_shared<VALID_TYPE>(height, width);
    std::shared_ptr<Buffer> outBufferCpu = std::make_shared<Buffer>(height, width);
    
    try {

        zeroCrossing->settingArguments(inBuffer, outBufferOpenCL, configParams);
        zeroCrossing->compute(inBuffer, outBufferOpenCL);

        std::shared_ptr<VALID_TYPE> zeroCrossingOpenCLH = zeroCrossing->getZeroCrossingH();
        std::shared_ptr<VALID_TYPE> zeroCrossingOpenCLV = zeroCrossing->getZeroCrossingV();
        
        std::shared_ptr<IZeroCrossing<Buffer>> zeroCrossingCPU = algorithmFactory->getAlgorithm<IZeroCrossing<Buffer>>(ZERO_CROSSING_CPU);
        IZeroCrossing<Buffer>::ConfigParams configParamsCPU;
        zeroCrossingCPU->settingArguments(inBuffer, outBufferCpu, configParamsCPU);
        zeroCrossingCPU->compute(inBuffer, outBufferCpu);
        
        std::shared_ptr<Buffer> zeroCrossingCPUH = zeroCrossingCPU->getZeroCrossingH();
        std::shared_ptr<Buffer> zeroCrossingCPUV = zeroCrossingCPU->getZeroCrossingV();

        // printMatrix(zeroCrossingCPUH, "CPUHorizontal");
        // printMatrix(zeroCrossingOpenCLH, "OpenCLHorizontal");

        verifyOutput(zeroCrossingCPUH, zeroCrossingOpenCLH);
        verifyOutput(zeroCrossingCPUV, zeroCrossingOpenCLV);
        verifyOutput(outBufferCpu, outBufferOpenCL);
    
    } catch(EdgeDetectorException &e) {

        GTEST_LOG_(ERROR) << e.what() << std::endl;
        throwException = true;    

    }

    EXPECT_FALSE(throwException);

}