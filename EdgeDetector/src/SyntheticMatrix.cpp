#include <cmath>
#include <algorithm>
#include "SyntheticMatrix.h"

#define HEIGHT  Buffer::DimsIndex::HEIGHT
#define WIDTH   Buffer::DimsIndex::WIDTH


SyntheticMatrix::SyntheticMatrix(int64_t minHeight, int64_t minWidth, float32_t slope, float32_t zc_init) {

    syntheticDims_.numOfImages = 1;
    syntheticDims_.height.insert(syntheticDims_.height.begin() + DimsSize::MIN, minHeight);
    syntheticDims_.width.insert(syntheticDims_.width.begin() + DimsSize::MIN, minWidth);
    syntheticDims_.growthFactor = 0;
    syntheticDims_.slope = slope;
    syntheticDims_.zc_init = zc_init;

    inputBuffer_ = std::make_shared<Buffer>(minHeight, minWidth);
    generateSyntheticMatrix(inputBuffer_, slope, zc_init);

}


SyntheticMatrix::SyntheticMatrix(int64_t numOfImages, int64_t minHeight,
                                 int64_t minWidth, int64_t growthFactor,
                                 float32_t slope, float32_t zc_init) {

    syntheticDims_.numOfImages = numOfImages;
    syntheticDims_.height.insert(syntheticDims_.height.begin() + DimsSize::MIN, minHeight);
    syntheticDims_.width.insert(syntheticDims_.width.begin() + DimsSize::MIN, minWidth);
    syntheticDims_.growthFactor = growthFactor;
    syntheticDims_.slope = slope;
    syntheticDims_.zc_init = zc_init;

    syntheticDims_.height.insert(syntheticDims_.height.begin() + DimsSize::MAX, (numOfImages - 1) * growthFactor + minHeight);
    syntheticDims_.width.insert(syntheticDims_.width.begin() + DimsSize::MAX, (numOfImages - 1) * growthFactor + minWidth);

    generateMultipleSyntheticMatrix(input_, syntheticDims_);

}


SyntheticMatrix::SyntheticMatrix(int64_t minHeight, int64_t minWidth, int64_t maxHeight, int64_t maxWidth,
                                 int64_t growthFactor, float32_t slope, float32_t zc_init) {

    syntheticDims_.height.insert(syntheticDims_.height.begin() + DimsSize::MIN, minHeight);
    syntheticDims_.width.insert(syntheticDims_.width.begin() + DimsSize::MIN, minWidth);
    syntheticDims_.height.insert(syntheticDims_.height.begin() + DimsSize::MAX, maxHeight);
    syntheticDims_.width.insert(syntheticDims_.width.begin() + DimsSize::MAX, maxWidth);
    syntheticDims_.growthFactor = growthFactor;
    syntheticDims_.slope = slope;
    syntheticDims_.zc_init = zc_init;

    syntheticDims_.numOfImages = static_cast<int64_t>(std::min(floor((maxHeight - minHeight) / growthFactor) + 1, floor((maxWidth - minWidth) / growthFactor) + 1));
    
    generateMultipleSyntheticMatrix(input_, syntheticDims_);    

}


void SyntheticMatrix::generateSyntheticMatrix(const std::shared_ptr<Buffer>& in, const float32_t slope, const float32_t zc_init) {

    std::vector<float32_t>& inData = in->getData();
    int height = in->getDims()[HEIGHT];
    int width = in->getDims()[WIDTH];

    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            float32_t border = static_cast<float32_t>(width - 1) / 2.f + slope * (static_cast<float32_t>(height - 1) / 2.f - j) + zc_init; 
            if (i == static_cast<int>(border)) {
                inData[i * width + j] = (1.f - static_cast<float32_t>(border - static_cast<int>(border)));
            }
            if (i > static_cast<int>(border)) {
                inData[i * width + j] = 1.f;
            } 
        }
    }

}


void SyntheticMatrix::generateMultipleSyntheticMatrix(std::vector<std::shared_ptr<Buffer>>& input, const SyntheticDims& syntheticDims) {

    int64_t height = syntheticDims.height[DimsSize::MIN];
    int64_t width = syntheticDims.width[DimsSize::MIN];

    for (size_t i = 0; i < syntheticDims.numOfImages; ++i) {
        
        if ( height > syntheticDims.height[DimsSize::MAX] || width > syntheticDims.width[DimsSize::MAX]) {
            break;
        }
        std::shared_ptr<Buffer> newBuffer = std::make_shared<Buffer>(height, width);
        input.insert(input.begin() + i, newBuffer);
        generateSyntheticMatrix(input[i], syntheticDims.slope, syntheticDims.zc_init);
        height += syntheticDims.growthFactor;
        width += syntheticDims.growthFactor;

    }

}


std::shared_ptr<Buffer>& SyntheticMatrix::getSyntheticMatrix() {

    return inputBuffer_;

}


std::vector<std::shared_ptr<Buffer>>& SyntheticMatrix::getSyntheticMultipleMatrix() {

    return input_;

}