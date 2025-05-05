#include <gtest/gtest.h>

#include "EdgeDetectorException.h"
#include "OpenCVAdapter.h"


class OpenCVAdapterTest: public ::testing::Test {

protected:

    const std::string path_ = "ajedrez";
    const std::string savingPath_ = "ajedrezCV";

    int64_t width;
    int64_t height;
    std::vector<int64_t> inputDims;
    std::shared_ptr<OpenCVAdapter> adapter;


    void SetUp() override {

        adapter = std::make_shared<OpenCVAdapter>(); 

    }

};


TEST_F(OpenCVAdapterTest, OpenCVAdapter_obtainImage_Sucess) {

    std::shared_ptr<Buffer> buffer;
    bool throwException = false;

    try {

        buffer = adapter->obtainImage(path_);    
    
    } catch(EdgeDetectorException& e) {
    
        GTEST_LOG_(ERROR) << e.what() << std::endl;
        throwException = true;
    
    }

    EXPECT_FALSE(throwException);

}


TEST_F(OpenCVAdapterTest, OpenCVAdapter_saveImage_Sucess) {
  
    std::shared_ptr<Buffer> buffer = adapter->obtainImage(path_);
    bool throwException = false;
    
    try {
        
        adapter->saveImage(buffer, savingPath_);
    
    } catch(EdgeDetectorException& e) {
    
        GTEST_LOG_(ERROR) << e.what() << std::endl;
        throwException = true;
    
    }
    
    EXPECT_FALSE(throwException);

}


TEST_F(OpenCVAdapterTest, OpenCVAdapter_obtainImage_invalidPath) {
  
    bool throwException = false;

    try {
        
        const std::string imageWithInvalidPath = "invalid";
        std::shared_ptr<Buffer> buffer = adapter->obtainImage(imageWithInvalidPath);
    
    } catch(EdgeDetectorException&) {
    
        throwException = true;
    
    }
    
    EXPECT_TRUE(throwException);

}


TEST_F(OpenCVAdapterTest, OpenCVAdapter_saveImage_invalidSize) {
    
    std::shared_ptr<Buffer> buffer = std::make_shared<Buffer>();
    bool throwException = false;

    buffer->getData().resize(1);

    try {
        
        adapter->saveImage(buffer, savingPath_);
    
    } catch(EdgeDetectorException&) {
    
        throwException = true;
    
    }
    
    EXPECT_TRUE(throwException);

}