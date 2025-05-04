/**
 * @file SyntheticMatrix.h
 * @author Eugenio Stabile (eugenio.stabile@photonicsens.com)
 * @brief Generate synthetic image with an edge.
 * @version 2.0.0
 * @date 2024-04-24
 * 
 * Copyright (c) 2024, Photonicsens. All rights reserved.
 * 
 */

#pragma once
#ifndef _SYNTHETIC_KERNEL_H
#define _SYNTHETIC_KERNEL_H

#include <vector>
#include <memory>

#include "Buffer.h"


class SyntheticMatrix {

public:
    SyntheticMatrix(int64_t minHeight = 1000, int64_t minWidth = 1000, float32_t slope = 1.f, float32_t zc_init = 0.f);
	SyntheticMatrix(int64_t numOfImages, int64_t minHeight, int64_t minWidth, int64_t growthFactor, float32_t slope = 1.f, float32_t zc_init = 0.f);
	SyntheticMatrix(int64_t minHeight, int64_t minWidth, int64_t maxHeight, int64_t maxWidth, int64_t growthFactor, float32_t slope = 1.f, float32_t zc_init = 0.f);
	
    ~SyntheticMatrix() = default;

    std::shared_ptr<Buffer>& getSyntheticMatrix();
    std::vector<std::shared_ptr<Buffer>>& getSyntheticMultipleMatrix();
    
private:
	
    enum DimsSize {
        MIN = 0,
        MAX = 1 
    };

    struct SyntheticDims {
        int64_t numOfImages;
		std::vector<int64_t> height;
		std::vector<int64_t> width;
        int64_t growthFactor;
        float32_t slope;
        float32_t zc_init;
	};

    SyntheticDims syntheticDims_;
    std::vector<std::shared_ptr<Buffer>> input_;
    std::shared_ptr<Buffer> inputBuffer_;
    
    void generateMultipleSyntheticMatrix(std::vector<std::shared_ptr<Buffer>>& input, SyntheticDims& syntheticDims);
    void generateSyntheticMatrix(std::shared_ptr<Buffer> in, const float32_t slope, const float32_t zc_init);


};

#endif
