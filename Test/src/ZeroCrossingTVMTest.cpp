#include "EdgeDetectorException.h"
#include "ZeroCrossingTest.h"
#include "ZeroCrossingCPU.h"
#include "ZeroCrossingTVM.h"

constexpr Buffer::DimsIndex WIDTH = Buffer::DimsIndex::WIDTH;
constexpr Buffer::DimsIndex HEIGHT = Buffer::DimsIndex::HEIGHT;
constexpr AlgorithmFactory::AlgorithmType ZERO_CROSSING_CPU = AlgorithmFactory::AlgorithmType::ZERO_CROSSING_CPU;
constexpr AlgorithmFactory::AlgorithmType ZERO_CROSSING_TVM = AlgorithmFactory::AlgorithmType::ZERO_CROSSING_TVM;

using VALID_TYPE = BufferTVM;
using ZeroCrossingTVMTest = ZeroCrossingTest<ZeroCrossingTVM, VALID_TYPE>;

INSTANTIATE_TEST_SUITE_P(ZeroCrossingTest, ZeroCrossingTVMTest, ::testing::Values(std::make_tuple(ZERO_CROSSING_TVM, "TVM")));


TEST_P(ZeroCrossingTVMTest, zeroCrossingTVM_compute_syntheticMatrix_success) {

    syntheticMatrix = std::make_shared<SyntheticMatrix>(height, width, slope, zeroCrossingExpected);
    
    std::shared_ptr<Buffer> in = syntheticMatrix->getSyntheticMatrix();
    std::shared_ptr<TVMAdapter> tvmAdapter = std::make_shared<TVMAdapter>();

    std::shared_ptr<VALID_TYPE> inBuffer = tvmAdapter->bufferToTVM(in);
    std::shared_ptr<VALID_TYPE> outBuffer = std::make_shared<VALID_TYPE>(height, width);
    bool throwException = false;

    try {

        adapter->saveImage(in, syntheticPath_);
        zeroCrossing->settingArguments(inBuffer, outBuffer, configParams);
        zeroCrossing->compute(inBuffer, outBuffer);

        std::shared_ptr<Buffer> out = tvmAdapter->bufferFromTVM(outBuffer->getData());
        adapter->saveImage(out, syntheticSavingPath_);
    
    } catch(EdgeDetectorException& e) {
    
        GTEST_LOG_(ERROR) << e.what() << std::endl;
        throwException = true;    

    }

    EXPECT_FALSE(throwException);

}


TEST_P(ZeroCrossingTVMTest, zeroCrossingTVM_compute_realImage_success) {

    bool throwException = false;

    try {
            
        std::shared_ptr<Buffer> in = adapter->obtainImage(path_);
        std::shared_ptr<TVMAdapter> tvmAdapter = std::make_shared<TVMAdapter>();

        std::shared_ptr<VALID_TYPE> inBuffer = tvmAdapter->bufferToTVM(in);
        
        height = inBuffer->getDims()[HEIGHT];
        width = inBuffer->getDims()[WIDTH];
        std::shared_ptr<VALID_TYPE> outBuffer = std::make_shared<VALID_TYPE>(height, width);

        zeroCrossing->settingArguments(inBuffer, outBuffer, configParams);
        zeroCrossing->compute(inBuffer, outBuffer);

        std::shared_ptr<Buffer> out = tvmAdapter->bufferFromTVM(outBuffer->getData());
        adapter->saveImage(out, savingPath_);

    } catch(EdgeDetectorException& e) {

        GTEST_LOG_(ERROR) << e.what() << std::endl;
        throwException = true;    

    }

    EXPECT_FALSE(throwException);

}


TEST_P(ZeroCrossingTVMTest, compute_invalidInputSize_exceptionExpected) {

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


TEST_P(ZeroCrossingTVMTest, compute_inputNotSameAsOutput_exceptionExpected) {

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


TEST_P(ZeroCrossingTVMTest, compute_invalidCheckParams_exceptionExpected) {

    syntheticMatrix = std::make_shared<SyntheticMatrix>(height, width, slope, zeroCrossingExpected);
    
    std::shared_ptr<Buffer> in = syntheticMatrix->getSyntheticMatrix();
    std::shared_ptr<TVMAdapter> tvmAdapter = std::make_shared<TVMAdapter>();
    std::shared_ptr<VALID_TYPE> inBuffer = tvmAdapter->bufferToTVM(in);

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


TEST_P(ZeroCrossingTVMTest, zeroCrossingTVM_validate_SyntheticMatrix_Horizontal_success) {

    slope = 0.f;
    syntheticMatrix = std::make_shared<SyntheticMatrix>(height, width, slope, zeroCrossingExpected);
    
    std::shared_ptr<TVMAdapter> tvmAdapter = std::make_shared<TVMAdapter>();
    std::shared_ptr<Buffer> in = syntheticMatrix->getSyntheticMatrix();

    std::shared_ptr<VALID_TYPE> inBuffer = tvmAdapter->bufferToTVM(in);
    std::shared_ptr<VALID_TYPE> outBuffer = std::make_shared<VALID_TYPE>(height, width);
    bool throwException = false;

    try {

        zeroCrossing->settingArguments(inBuffer, outBuffer, configParams);
        zeroCrossing->compute(inBuffer, outBuffer);
        std::shared_ptr<VALID_TYPE> horizontal = zeroCrossing->getZeroCrossingH();
        auto horizontalCPU = tvmAdapter->bufferFromTVM(horizontal->getData());

        verifySynteticMatrixOutput(horizontalCPU, zeroCrossingExpected);

    
    } catch(EdgeDetectorException& e) {

        GTEST_LOG_(ERROR) << e.what() << std::endl;
        throwException = true;    

    }

    EXPECT_FALSE(throwException);

}


TEST_P(ZeroCrossingTVMTest, zeroCrossingTVM_validate_SyntheticMatrix_Vertical_success) {

    slope = 0.f;
    syntheticMatrix = std::make_shared<SyntheticMatrix>(height, width, slope, zeroCrossingExpected);
    
    std::shared_ptr<TVMAdapter> tvmAdapter = std::make_shared<TVMAdapter>();
    std::shared_ptr<Buffer> in = syntheticMatrix->getSyntheticMatrix();

    std::shared_ptr<VALID_TYPE> inBuffer = tvmAdapter->bufferToTVM(in);
    std::shared_ptr<Buffer> inBufferCPU = tvmAdapter->bufferFromTVM(inBuffer->getData());
    std::shared_ptr<Buffer> inBufferTransposeCPU = transpose(inBufferCPU);
    std::shared_ptr<VALID_TYPE> inBufferTranspose = tvmAdapter->bufferToTVM(inBufferTransposeCPU);

    std::shared_ptr<VALID_TYPE> outBuffer = std::make_shared<VALID_TYPE>(width, height);
    bool throwException = false;

    try {

        zeroCrossing->settingArguments(inBufferTranspose, outBuffer, configParams);
        zeroCrossing->compute(inBufferTranspose, outBuffer);

        std::shared_ptr<VALID_TYPE> vertical = zeroCrossing->getZeroCrossingV();
        auto verticalCPU = tvmAdapter->bufferFromTVM(vertical->getData());

        verifySynteticMatrixOutput(verticalCPU, zeroCrossingExpected);
    
    } catch(EdgeDetectorException& e) {

        GTEST_LOG_(ERROR) << e.what() << std::endl;
        throwException = true;    

    }

    EXPECT_FALSE(throwException);

}


TEST_P(ZeroCrossingTVMTest, zeroCrossingTVM_compute_sameOutputAsCPU) {


    std::shared_ptr<Buffer> in = adapter->obtainImage(path_);
    std::shared_ptr<TVMAdapter> tvmAdapter = std::make_shared<TVMAdapter>();
    std::shared_ptr<VALID_TYPE> inBuffer = tvmAdapter->bufferToTVM(in);

    
    height = inBuffer->getDims()[HEIGHT];
    width = inBuffer->getDims()[WIDTH];
    bool throwException = false;

    std::shared_ptr<VALID_TYPE> outBufferTVM = std::make_shared<VALID_TYPE>(height, width);
    std::shared_ptr<Buffer> outBufferCpu = std::make_shared<Buffer>(height, width);
    
    try {

        zeroCrossing->settingArguments(inBuffer, outBufferTVM, configParams);
        zeroCrossing->compute(inBuffer, outBufferTVM);

        std::shared_ptr<VALID_TYPE> zeroCrossingTVMH = zeroCrossing->getZeroCrossingH();
        std::shared_ptr<VALID_TYPE> zeroCrossingTVMV = zeroCrossing->getZeroCrossingV();
        
        std::shared_ptr<TVMAdapter> tvmAdapter = std::make_shared<TVMAdapter>();
        std::shared_ptr<Buffer> zcTVMH = tvmAdapter->bufferFromTVM(zeroCrossingTVMH->getData());
        std::shared_ptr<Buffer> zcTVMV = tvmAdapter->bufferFromTVM(zeroCrossingTVMV->getData());
        std::shared_ptr<Buffer> outTVM = tvmAdapter->bufferFromTVM(outBufferTVM->getData());
        

        std::shared_ptr<IZeroCrossing<Buffer>> zeroCrossingCPU = algorithmFactory->getAlgorithm<IZeroCrossing<Buffer>>(ZERO_CROSSING_CPU);
        IZeroCrossing<Buffer>::ConfigParams configParamsCPU;
        zeroCrossingCPU->settingArguments(in, outBufferCpu, configParamsCPU);
        zeroCrossingCPU->compute(in, outBufferCpu);
        
        std::shared_ptr<Buffer> zeroCrossingCPUH = zeroCrossingCPU->getZeroCrossingH();
        std::shared_ptr<Buffer> zeroCrossingCPUV = zeroCrossingCPU->getZeroCrossingV();

        printMatrix(zeroCrossingCPUH, "CPUHorizontal");
        printMatrix(zcTVMH, "TVMHorizontal");

        verifyOutput(zeroCrossingCPUH, zcTVMH);
        verifyOutput(zeroCrossingCPUV, zcTVMV);
        verifyOutput(outBufferCpu, outTVM);
    
    } catch(EdgeDetectorException &e) {

        GTEST_LOG_(ERROR) << e.what() << std::endl;
        throwException = true;    

    }

    EXPECT_FALSE(throwException);

}