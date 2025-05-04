#include <vector>

#include "Kernel.h"

const std::vector<float32_t>& Kernel::getDerivativeFilter() {
    
	return derivativeFilter_;

}


const std::vector<float32_t>& Kernel::getUpsamplingFilter() {

	return upsamplingFilter_;

}

const std::vector<float32_t>& Kernel::getGaussianFilter() {

	return gaussianFilter_;

}

const int Kernel::getUpsamplingFactor(){

	return upsamplingFactor_;

}