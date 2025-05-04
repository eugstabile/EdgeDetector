#include <gtest/gtest.h>

#include "Buffer.h"

#define TEST_SUITE_NAME BufferTest

namespace TEST_SUITE_NAME
{
    constexpr Buffer::DimsIndex WIDTH_DIM = Buffer::DimsIndex::WIDTH;
    constexpr Buffer::DimsIndex HEIGHT_DIM = Buffer::DimsIndex::HEIGHT;

    int64_t height;
    int64_t width;
    std::vector<float32_t> inputData_;
    std::vector<int64_t> inputDims;
    std::shared_ptr<Buffer> buffer_;

    void initialize() {
        
        height = 400;
        width = 600;
        inputDims = {height, width};
        inputData_.resize(inputDims.size());
        buffer_ = std::make_shared<Buffer>();

    }

} // namespace TEST_SUITE_NAME

using namespace TEST_SUITE_NAME;

TEST(TEST_SUITE_NAME, Buffer_getDims_Sucess) {

    initialize();
    std::shared_ptr<Buffer> buffer = buffer_;
    buffer->setData(inputData_, inputDims);
    std::vector<int64_t> dimsBuffer = buffer->getDims();

    EXPECT_TRUE(dimsBuffer.size() != 0);
    EXPECT_EQ(dimsBuffer[HEIGHT_DIM], height);
    EXPECT_EQ(dimsBuffer[WIDTH_DIM], width);

}

#undef TEST_SUITE_NAME