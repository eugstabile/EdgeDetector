#include <cmath>

#include "EdgeDetectorException.h"
#include "ZeroCrossingOpenMP.h"

#define HEIGHT Buffer::DimsIndex::HEIGHT
#define WIDTH Buffer::DimsIndex::WIDTH


ZeroCrossingOpenMP::ZeroCrossingOpenMP() {
    
    std::shared_ptr<Kernel> kernel = std::make_shared<Kernel>();
 
    derivativeFilter_ = kernel->getDerivativeFilter();
    upsamplingFilter_ = kernel->getUpsamplingFilter();
    upsamplingFactor_ = kernel->getUpsamplingFactor();

}


void ZeroCrossingOpenMP::compute(const std::shared_ptr<Buffer> in, std::shared_ptr<Buffer> out) {

    // Horizontal edge computation
    calculateEdges(in, derivativeImage_.h, zeroCrossings_.h);

    // Vertical edge computation
    const std::shared_ptr<Buffer> inTranspose = transposeOptimized(in);

    calculateEdges(inTranspose, derivativeImage_.v, zeroCrossings_.v);

    // Combine computation
    combineEdges(zeroCrossings_.h, zeroCrossings_.v, out);
}


void ZeroCrossingOpenMP::filterUpsampling(int kernelPos, std::vector<float32_t>::iterator& inputData, std::vector<float32_t>::iterator& outputData) {
  
    const int marginsInput = static_cast<int>(upsamplingFactor_ / 2);
    const int kernelSize = static_cast<int>(upsamplingFilter_.size());
    const int kernelCenter = static_cast<int>(kernelSize / 2);
    const int originalCenter = static_cast<int>(ceil(kernelCenter / upsamplingFactor_));

    float32_t upsamplingFactorDiv = (1.f / upsamplingFactor_);
    
    std::vector<float32_t> valuesInterpolated(upsamplingFactor_ + 1, 0.f);
    std::vector<float32_t> inputDataUpsampled(kernelSize + upsamplingFactor_, 0.f);

    int k = 0;
    float32_t confidence = abs(inputData[originalCenter - 1] - inputData[originalCenter]);

    if (confidence >= configParams_.threshold) {

        /**
         * 
         * This for loop fills the inputData values with an offset of 4 to construct an upsampled vector representation of the input data.
         * 
         */

        for (int i = marginsInput; i < inputDataUpsampled.size(); i+= upsamplingFactor_) {
            inputDataUpsampled[i] = inputData[k++];
        }

        /**
         * 
         *  The FilterUpsampling function takes two zero crossing values and generates a vector with the following characteristics:
         *    - Size of (upsamplingFactor_ - 1) elements.
         *    - The data it contains will have a structure like this: [A, 0, 0, 0, B] 
         *      where A and B are the values that produce the zero crossings and the elements at 0 will be the values to interpolate.
         * 
         */

        // aqui tengo que poner pos * upsampling - (upsamplingFactor - 3)
        valuesInterpolated[0] = inputData[originalCenter - 1];
        valuesInterpolated[upsamplingFactor_] = inputData[originalCenter];
        
        
        for (int i = 0; i < upsamplingFactor_ - 1; ++i) {
            for (int j = 0; j < upsamplingFilter_.size(); ++j) {

                valuesInterpolated[i] += inputDataUpsampled[i + j] * upsamplingFilter_[j];

            }
        }

        for (int j = 0; j < upsamplingFilter_.size(); ++j) {

            valuesInterpolated[upsamplingFactor_] += inputDataUpsampled[upsamplingFactor_ + j] * upsamplingFilter_[j];

        }

        float32_t value = 0.f;
        float32_t zeroCrossingValue = 0.f;
        int xi = 0;
        float current = 0.f;
        float next = 0.f;

        /**
         * 
         * We find for the precise location of the zero crossing before interpolating the values and calculate the result.
         * 
         */
        
        for (; xi < upsamplingFactor_ - 1; ++xi) {
            
            current = valuesInterpolated[xi];
            next = valuesInterpolated[xi + 1];

            if (!((current >= 0.f) ^ (next < 0.f))) {             
                
                if ((current - next) != 0.f) {  
                    value = (current / (current - next));
                    break;  
                }
            }

        }

        float32_t posValue = static_cast<float32_t>(xi % upsamplingFactor_) * upsamplingFactorDiv;
        zeroCrossingValue = posValue + upsamplingFactorDiv * value;

        outputData[originalCenter] = zeroCrossingValue;
    }
}


void ZeroCrossingOpenMP::calculateEdges(const std::shared_ptr<Buffer> in, std::shared_ptr<Buffer> derivativeImage, std::shared_ptr<Buffer> zeroCrossingsMap){
    
    /** 
     *    
     *   CalculateEdges:
     * 
     *   This method calculates and returns the edges of an image.
     *   The function can be divided into two parts: the derivative part and the upsampling part. In each iteration the following is computed row by row:
     *   
     *      
     *    - Upsampling part: This part looks for a zero crossing between two derived values (current and next).
     *       If this condition is met, the 'filterUpsampling' function is called, which creates an interpolation between these values and applies the upsampling filter. 
     *       Finally, it stores the value in the zeroCrossingMap
     * 
     *   Additionally, we treat all input matrices as not multiples of 4. 
     *   That is why at the end of each row, we calculate the last (width - margins) - 4 elements in a scalar way.
     * 
     */

    const std::vector<float32_t>& inputData = in->getData();
    std::vector<float32_t>& derivativeImageData = derivativeImage->getData();
    std::vector<float32_t>& zeroCrossing = zeroCrossingsMap->getData();

    const int marginsDerivative = static_cast<int>(derivativeFilter_.size() / 2);
    const int marginsUpsampling = static_cast<int>(upsamplingFilter_.size() / 2);

    /**
     * 
     *   To align with the sequential version of the CPU, we have to start at the position that meets the following condition:
     *   - To be a multiple of 4.
     *   - To be greater than half the size of the upsampling filter.
     * 
     */

    const int marginsUpsamplingMultiple =  upsamplingFactor_ * static_cast<int>(ceil(marginsUpsampling / upsamplingFactor_));
    std::vector<VECTOR_TYPE> vectorDerivativeKernel(derivativeFilter_.size());

    const int marginsInterpolation = static_cast<int>(ceil(marginsUpsampling / upsamplingFactor_));

    
    /**
     * 
     *  Before starting the derivative part, we vectorize the derivative filter.
     * 
     *  If the vector is {1.f, 0.4f, 0.2f, 0.5f}
     *  The vectorized version will be {1.f, 1.f, 1.f, 1.f, 0.4f, 0.4f, 0.4f, 0.4f, 0.2f, 0.2f, 0.2f, 0.2f, 0.5f, 0.5f, 0.5f, 0.5f}  
     *  
     */

    //#pragma omp parallel for
    for (int m = -marginsDerivative; m <= marginsDerivative; ++m) {
        vectorDerivativeKernel[m + marginsDerivative] = _mm_set1_ps(derivativeFilter_[m + marginsDerivative]);
    }
    
    const int height = in->getDims()[HEIGHT];
    const int width = in->getDims()[WIDTH];
    float32_t sum = 0.f;
    
    //#pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < height; ++i) {
        
        /** 
        *    
        *    Derivative part: 
        * 
        *    To obtain a derivative image, this part applies a Fused Multiply-and-Add operation
        *    and stores the result in the derivativeImageData vector, which serves as input data for the upsampling part.
        *    If we look at the innermost loop of this part, it starts by reading the first element of the kernel and 
        *    the current position of the input data minus half the size of the derivative filter.
        *    This ensures that the center of the kernel is aligned with the current position.
        *
        */

        int j = marginsDerivative;
        for (; j < width - marginsDerivative - VECTOR_STEP; j+= VECTOR_STEP) {

            VECTOR_TYPE sumVector = _mm_setzero_ps();

            for (int m = -marginsDerivative; m <= marginsDerivative; ++m) {

                VECTOR_TYPE vectorInputData = _mm_loadu_ps(&inputData[(i * width + j) + m]);
                sumVector = _mm_fmadd_ps(vectorInputData, vectorDerivativeKernel[m + marginsDerivative], sumVector);
                _mm_prefetch((char*)&inputData[(i * width + j) + m + VECTOR_STEP], _MM_HINT_T0);
            }
            _mm_storeu_ps(&derivativeImageData[i * width + j], sumVector);

        }

        /** 
        *    
        *    Upsampling part: 
        * 
        *    It gets the derived row and looks for a zero crossing. 
        *    In this part to find an edge, it uses a mask that compares with an XNOR operation 4 elements of the variable current and 4 of the variable next.
        *    Note: The intrinsic function _mm_movemask_ps() returns in case of a zero crossing the value -1.f, otherwise 0.f.
        * 
        *    For example:
        * 
        *     - Current vector is: {1.f, -1.f, -1.f, -1.f}.
        *     - Next vector is: {-1.f, -1.f, -1.f, -1.f}.
        *     - After applying the XNOR operation, the mask becomes: {-0.0f, 0.0f, 0.0f, 0.0f}. (Note: -0.f = 0x80000000, where the most significant bit is set).
        *     - The line 'maskInt = _mm_movemask_ps(mask);' returns from {-0.0f, 0.0f, 0.0f, 0.0f} the integer 1.  
        *     - The subsequent for loop determines the position of the zero crossing within the vector. In this example, it will be 1.
        *       
        * 
        *    Finally, it calls the filterUpsampling function with the following arguments:
        *     - The position within the vector where the zero crossing is found.   
        *     - The current position of the derivative image minus half of the upsampling filter size (to align the current position with the center of the kernel).
        *     - The current position of the zero crossing map.
        *
        */

        int k = marginsUpsamplingMultiple;
        for (; k < (width - marginsUpsamplingMultiple) - VECTOR_STEP; k += VECTOR_STEP) {

            VECTOR_TYPE current = _mm_loadu_ps(&derivativeImageData[i * width + k - 1]);
            VECTOR_TYPE next = _mm_loadu_ps(&derivativeImageData[i * width + k]);

            VECTOR_TYPE currentMask = _mm_cmpge_ps(current, _mm_setzero_ps());
            VECTOR_TYPE nextMask = _mm_cmplt_ps(next, _mm_setzero_ps());

            VECTOR_TYPE mask = _mm_xor_ps(currentMask, nextMask);
            mask = _mm_andnot_ps(mask, _mm_set1_ps(-0.0f));

            int maskInt = _mm_movemask_ps(mask);

            for (int l = 0; l < VECTOR_STEP; ++l) {
                
                if (maskInt & (1 << l)) {

                    int pos = (i * width + k + l);
                
                    std::vector<float32_t>::iterator inputIterator = derivativeImageData.begin() + (pos - marginsInterpolation);
                    std::vector<float32_t>::iterator zeroCrossingIterator = zeroCrossing.begin() + pos;

                    filterUpsampling((k+l), inputIterator, zeroCrossingIterator);

                }
            }
        }

        
        for (; j < width - marginsDerivative; ++j) {        
            for (int m = -marginsDerivative; m <= marginsDerivative; ++m) {
                sum += inputData[(i * width + j) + m] * derivativeFilter_[marginsDerivative + m];
            }

            derivativeImageData[i * width + j] = sum;
            sum = 0.f;
        }
        

        for(; k < (width - marginsUpsamplingMultiple); ++k) {

            float32_t current = derivativeImageData[i* width + k];
            float32_t next = derivativeImageData[i* width + k + 1];
            
            if ( !((current >= 0.f) ^ (next < 0.f)) ) {
                
                int pos = i * width + k;
                std::vector<float32_t>::iterator inputIterator = derivativeImageData.begin() + (pos - marginsInterpolation);
                std::vector<float32_t>::iterator zeroCrossingIterator = zeroCrossing.begin() + pos;

                filterUpsampling(k, inputIterator, zeroCrossingIterator);

            }
        }
    }       
}


void ZeroCrossingOpenMP::combineEdges(const std::shared_ptr<Buffer> zeroCrossingsMapH, const std::shared_ptr<Buffer> zeroCrossingsMapV, std::shared_ptr<Buffer> out) {

    
    const std::vector<float32_t>& zeroCrossingsMapHData = zeroCrossingsMapH->getData();
    const int height = zeroCrossingsMapH->getDims()[HEIGHT];
    const int width = zeroCrossingsMapH->getDims()[WIDTH];

    const std::shared_ptr<Buffer> zeroCrossingsMapVTranspose = transposeOptimized(zeroCrossingsMapV);
    const std::vector<float32_t>& zeroCrossingsMapVData = zeroCrossingsMapVTranspose->getData();
    std::vector<float32_t>& outData = out->getData();
    
    const VECTOR_TYPE one = _mm_set1_ps(1.f);
    const VECTOR_TYPE zeroes = _mm_setzero_ps();

    float32_t hitH = 0.f;
    float32_t hitV = 0.f;

    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < height; ++i) {
        int j = 0;
        for (; j < width - VECTOR_STEP; j +=VECTOR_STEP) {

            VECTOR_TYPE horizontal = _mm_loadu_ps(&zeroCrossingsMapHData[i * width + j]);
            VECTOR_TYPE vertical = _mm_loadu_ps(&zeroCrossingsMapVData[i * width + j]);
        
            VECTOR_TYPE maskHorizontal = _mm_cmpgt_ps(horizontal, zeroes);
            VECTOR_TYPE maskVertical = _mm_cmpgt_ps(vertical, zeroes);

            VECTOR_TYPE mask = _mm_or_ps(maskHorizontal, maskVertical);
            int maskInt = _mm_movemask_ps(mask); 
        
            if (maskInt) {
                /**
                 * 
                 * Intrinsics functions such as _mm_cmpgt_ps return 0xffffffff if true, and 0x0 otherwise.
                 * If mask has {0.f, -1,f, 0.f, -1,f}, the line 'VECTOR_TYPE outVector = _mm_and_ps(mask, one);' will yeild {0.f, 1.f, 0.f, 1.f}.
                 * This corresponds to the bitwise operation (0xff & 0x01).
                 *  
                 */

                VECTOR_TYPE outVector = _mm_and_ps(mask, one);
                _mm_storeu_ps(&outData[i * width + j], outVector);
                
            } 
        }

        for(; j < width; ++j){
            
            hitH = zeroCrossingsMapHData[i * width + j] > 0.f ? 1.f : 0.f;
            hitV = zeroCrossingsMapVData[i * width + j] > 0.f ? 1.f : 0.f;

            if ((hitH > 0.f) || (hitV > 0.f)) {
                outData[i * width + j] = 1.f;
            }
        }
    }

}


void ZeroCrossingOpenMP::settingArguments(const std::shared_ptr<Buffer> in, const std::shared_ptr<Buffer> out, const ConfigParams& configParams) {

    checkParams(in, out, configParams);
    setConfigParams(configParams);

    const int64_t rows = in->getDims()[HEIGHT];
    const int64_t cols = in->getDims()[WIDTH];
    const std::vector<int64_t> inputSizeH = {rows, cols};
    const std::vector<int64_t> inputSizeV = {cols, rows};

    prepareBuffers(derivativeImage_, inputSizeH, inputSizeV);
    prepareBuffers(zeroCrossings_, inputSizeH, inputSizeV);

}


void ZeroCrossingOpenMP::checkParams(const std::shared_ptr<Buffer> in, const std::shared_ptr<Buffer> out, const ConfigParams &configParams) {

    const std::vector<int64_t> inputDims = in->getDims();
    const std::vector<int64_t> outputDims = in->getDims();
    const size_t inputSize = in->getData().size();
    const size_t outputSize = out->getData().size();

    if (inputSize != outputSize) {
	    THROW_EXCEPTION("Input and output sizes don't match");
    }
    
    if (inputDims != outputDims) {
	    THROW_EXCEPTION("Input and output dimensions don't match");
    }
    
    if (inputSize <= 0 || inputDims[HEIGHT] <= 1 || inputDims[WIDTH] <= derivativeFilter_.size()) {
	    THROW_EXCEPTION("Invalid input dimensions");
    }

    if (outputSize <= 0 || outputDims[HEIGHT] <= 1 || outputDims[WIDTH] <= derivativeFilter_.size()) {
	    THROW_EXCEPTION("Invalid output dimensions");
    }

    if (derivativeFilter_.size() == 0) {
	    THROW_EXCEPTION("Invalid derivative filter");
    }

    if (upsamplingFilter_.size() == 0) {
	    THROW_EXCEPTION("Invalid upsampling filter");
    }

    if (configParams.threshold < 0) {
	    THROW_EXCEPTION("Invalid threshold value");
    }

}


void ZeroCrossingOpenMP::setConfigParams(const ConfigParams& configParams) {

    configParams_.threshold = configParams.threshold;    
    
    if (configParams_.threshold < 0.f) {
        THROW_EXCEPTION("Threshold can not be negative");
    } 

}


void ZeroCrossingOpenMP::prepareBuffers(BufferSet& bufferset, const std::vector<int64_t>& dimsH, const std::vector<int64_t>& dimsV) {
  
    bufferset.h = std::make_shared<Buffer>(dimsH[HEIGHT], dimsH[WIDTH]);
    bufferset.v = std::make_shared<Buffer>(dimsV[HEIGHT], dimsV[WIDTH]);

}


const IZeroCrossing<Buffer>::ConfigParams ZeroCrossingOpenMP::getConfigParams() {
    
    return configParams_;

}

std::shared_ptr<Buffer> ZeroCrossingOpenMP::getZeroCrossingH(){

    return zeroCrossings_.h;

}


std::shared_ptr<Buffer> ZeroCrossingOpenMP::getZeroCrossingV(){

    return zeroCrossings_.v;

}
