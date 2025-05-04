/**
 * @file Kernel.h
 * @author Eugenio Stabile (eugenio.stabile@photonicsens.com)
 * @brief Generate kernels filter 
 * @version 2.0.0
 * @date 2024-04-24
 * 
 * Copyright (c) 2024, Photonicsens. All rights reserved.
 * 
 */

#pragma once
#ifndef _KERNELS_H
#define _KERNELS_H

#include "Buffer.h"

class Kernel {

public:

	Kernel()= default;
	~Kernel() = default;
	
	const std::vector<float32_t>& getDerivativeFilter();
	const std::vector<float32_t>& getUpsamplingFilter();
	const std::vector<float32_t>& getGaussianFilter();
	const int getUpsamplingFactor();

private:

	const std::vector<float32_t> derivativeFilter_ { 0.01001210f,  0.04924748f,  0.09538970f,  0.09471289f, 0.00063781f,    \
                                        			-0.14303523f, -0.21392953f, -0.14303523f, 0.00063781f, 0.09471289f,     \
                                         			 0.09538970f,  0.04924748f,  0.01001210f};
    
	const std::vector<float32_t> upsamplingFilter_{
													0.04852817f,  0.03762380f,  0.00271539f,  -0.03692344f, -0.05745509f,	\
													-0.04450036f, -0.00271831f, 0.04517346f,  0.07032854f,  0.05459582f,	\
													0.00272070f,  -0.05780706f, -0.09053116f, -0.07088177f, -0.00272255f,	\
													0.07960586f,  0.12685790f,  0.10161263f,  0.00272388f,  -0.12628092f,	\
													-0.21155686f, -0.18145701f, -0.00272468f, 0.29733567f,  0.63486118f,	\
													0.89978139f,  1.f,          0.89978139f,  0.63486118f,  0.29733567f,	\
													-0.00272468f, -0.18145701f, -0.21155686f, -0.12628092f, 0.00272388f,	\
													0.10161263f,  0.12685790f,  0.07960586f,  -0.00272255f, -0.07088177f,	\
													-0.09053116f, -0.05780706f, 0.00272070f,  0.05459582f,  0.07032854f,	\
													0.04517346f,  -0.00271831f, -0.04450036f, -0.05745509f, -0.03692344f,	\
													0.00271539f,  0.03762380f,  0.04852817f};

	const std::vector<float32_t> gaussianFilter_ { 	0.0703f, 0.1369f, 0.0855f, 0.1369f, 0.0703f};

	const int upsamplingFactor_ = 4;

};

#endif