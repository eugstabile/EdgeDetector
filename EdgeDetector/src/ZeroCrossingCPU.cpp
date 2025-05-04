#include "EdgeDetectorException.h"
#include "ZeroCrossingCPU.h"
#include "OpenCVAdapter.h"


#define HEIGHT Buffer::DimsIndex::HEIGHT
#define WIDTH Buffer::DimsIndex::WIDTH


ZeroCrossingCPU::ZeroCrossingCPU() {
    
    std::shared_ptr<Kernel> kernel = std::make_shared<Kernel>();
 
    derivativeFilter_= kernel->getDerivativeFilter();
    upsamplingFilter_ = kernel->getUpsamplingFilter();
    upsamplingFactor_ = kernel->getUpsamplingFactor();

}


void ZeroCrossingCPU::compute(std::shared_ptr<Buffer> in, std::shared_ptr<Buffer> out) {

    // Horizontal edge computation
    filterDerivative(in, derivativeImage_.h, derivativeFilter_);
    calculateConfidences(derivativeImage_.h, confidences_.h);
    calculateUpsampling(derivativeImage_.h, upSampledImage_.h, inPadded_.h);
    calculateEdges(upSampledImage_.h, confidences_.h, zeroCrossings_.h);

    // Vertical edge computation
    std::shared_ptr<Buffer> inTranspose = transpose(in);

    filterDerivative(inTranspose, derivativeImage_.v, derivativeFilter_);
    calculateConfidences(derivativeImage_.v, confidences_.v);
    calculateUpsampling(derivativeImage_.v, upSampledImage_.v, inPadded_.v);
    calculateEdges(upSampledImage_.v, confidences_.v, zeroCrossings_.v);

    // Combine computation
    combineEdges(zeroCrossings_.h, zeroCrossings_.v, out);

}


void ZeroCrossingCPU::filterUpsampling(const std::shared_ptr<Buffer> in, std::shared_ptr<Buffer> out, const std::vector<float32_t>& kernel) {
  
    std::vector<float32_t>& inputData = in->getData();
    std::vector<float32_t>& outputData = out->getData();
    int height = in->getDims()[HEIGHT];
    int width = in->getDims()[WIDTH];
    int marginsUpsampling = static_cast<int>(kernel.size() / 2);

    /**
     * 
     * Previous version calculates filter derivative and upsampling in the same way.
     * In this version, filterUpsampling doesn't overwrite zero crossing values.
     * 
     */

    int isMultiple = marginsUpsampling % upsamplingFactor_;
    int margins = isMultiple != 0 ? (marginsUpsampling + isMultiple) : marginsUpsampling;

    for (int i = 0; i < height; ++i) {
        for (int j = margins; j < width - margins; j+=upsamplingFactor_) {

            outputData[i * width + j] = inputData[i * width + j];

            for (int k = 1; k < upsamplingFactor_; ++k) {
                
                float32_t sum = 0.f;
                
                for (int m = -marginsUpsampling; m <= marginsUpsampling; ++m) {

                    sum += inputData[(i * width + j) + k + m] * kernel[marginsUpsampling + m];

                }
                int pos = (i * width + j) + k;

                outputData[pos] = sum;
            }            
        }
    }
}


void ZeroCrossingCPU::filterDerivative(const std::shared_ptr<Buffer> in, std::shared_ptr<Buffer> out, const std::vector<float32_t>& kernel) {
  
    std::vector<float32_t>& inputData = in->getData();
    std::vector<float32_t>& outputData = out->getData();
    int height = in->getDims()[HEIGHT];
    int width = in->getDims()[WIDTH];
    int margins = static_cast<int>(kernel.size() / 2);
    
    for (int i = 0; i < height; ++i) {
        for (int j = margins; j < width - margins; ++j) {

            float sum = 0.f;
            
            for (int m = -margins; m <= margins; ++m) {

                sum += inputData[(i * width + j) + m] * kernel[margins + m];

            }
            outputData[i * width + j] = sum;
        }
    }
    
}


void ZeroCrossingCPU::calculateConfidences(std::shared_ptr<Buffer> in, std::shared_ptr<Buffer> confidencesFilter) {
  
    std::vector<float32_t>& inputData = in->getData();
    std::vector<float32_t>& confidencesData = confidencesFilter->getData();
    int height = in->getDims()[HEIGHT];
    int width = in->getDims()[WIDTH];
    int margins = static_cast<int>(derivativeFilter_.size() / 2);

    for (int i = 0; i < height; ++i) {
        for (int j = margins + 1; j < width - margins; ++j) {
            
            float32_t previous = inputData[i * width + (j - 1)];
            float32_t current = inputData[i * width + j];
            confidencesData[i * width + j] = abs(previous - current);
        }
    }
    
}


void ZeroCrossingCPU::calculateUpsampling(const std::shared_ptr<Buffer> in, std::shared_ptr<Buffer> upsampledImage, std::shared_ptr<Buffer> inPadded) {

    std::vector<float32_t>& inputData = in->getData();
    int height = in->getDims()[HEIGHT];
    int width = in->getDims()[WIDTH];

    std::vector<float32_t>& inputPadded = inPadded->getData();

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width * upsamplingFactor_; j += upsamplingFactor_) {

            inputPadded[i * (width * upsamplingFactor_) + j] = inputData[i * width + static_cast<int>(j / upsamplingFactor_)];

        }
    }

    filterUpsampling(inPadded, upsampledImage, upsamplingFilter_);
}


void ZeroCrossingCPU::calculateEdges(const std::shared_ptr<Buffer> inUpsampled, std::shared_ptr<Buffer> confidences, std::shared_ptr<Buffer> zeroCrossingsMap) {
 
    std::vector<float32_t>& inputUpsampledData = inUpsampled->getData();
    std::vector<float32_t>& confidencesData = confidences->getData();
    std::vector<float32_t>& zeroCrossing = zeroCrossingsMap->getData();

    float32_t marginsUpsampling = static_cast<int>(upsamplingFilter_.size() / 2);
    int height = zeroCrossingsMap->getDims()[HEIGHT];
    int width = zeroCrossingsMap->getDims()[WIDTH];

    /**
     * 
     * We need to start in the next multiple of 4 that is greater than the half of the upsampling size.
     * Otherwise, we will not read the correct value and get an interpolated element.
     * 
     */

    int margins =  upsamplingFactor_ * static_cast<int>(ceil(marginsUpsampling / upsamplingFactor_));

    float32_t upsamplingFactorDiv = 1.f / upsamplingFactor_;

    for (int i = 0; i < height; ++i) {
        for (int j = margins; j < (width - margins); ++j) {

            int posUpsampling =  i * (upsamplingFactor_ * width) + ((j - 1) * upsamplingFactor_);

            for( int k = 1; k < upsamplingFactor_ + 1; ++k) {


                float32_t A = inputUpsampledData[posUpsampling + k];
                float32_t B = inputUpsampledData[posUpsampling + k + 1];

                if ( !((A >= 0.f) ^ (B < 0.f)) ) {
                    
                    int pos = i * width + j;
                    float32_t zcConfidence = confidencesData[pos];

                    if ((zcConfidence >= configParams_.threshold)) {

                        float32_t value = 0.f;

                        if (abs(A-B) != 0.f) {

                            value = (A / (A - B));

                        }
                
                        float32_t posValue = static_cast<float32_t>(k % upsamplingFactor_) * upsamplingFactorDiv;
                        float32_t relativeZeroCrossing = posValue + upsamplingFactorDiv * value;
                        
                        zeroCrossing[pos] = relativeZeroCrossing;
                        break;
                    }    
                }
            }
        }
    }
}


void ZeroCrossingCPU::combineEdges(std::shared_ptr<Buffer> zeroCrossingsMapH, std::shared_ptr<Buffer> zeroCrossingsMapV, std::shared_ptr<Buffer> out) {

    
    std::vector<float32_t>& zeroCrossingsMapHData = zeroCrossingsMapH->getData();
    int height = zeroCrossingsMapH->getDims()[HEIGHT];
    int width = zeroCrossingsMapH->getDims()[WIDTH];

    std::shared_ptr<Buffer> zeroCrossingsMapVTranspose = transpose(zeroCrossingsMapV);
    std::vector<float32_t>& zeroCrossingsMapVData = zeroCrossingsMapVTranspose->getData();
    std::vector<float32_t>& outData = out->getData();

    float32_t hitH;
    float32_t hitV;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {

            hitH = zeroCrossingsMapHData[i * width + j] > 0.f ? 1.f : 0.f;
            hitV = zeroCrossingsMapVData[i * width + j] > 0.f ? 1.f : 0.f;

            if ((hitH > 0.f) || (hitV > 0.f)) {
                outData[i * width + j] = 1.f;
            }
        }
    }

}


void ZeroCrossingCPU::settingArguments(std::shared_ptr<Buffer> in, std::shared_ptr<Buffer> out, const ConfigParams& configParams) {

    checkParams(in, out, configParams);
    setConfigParams(configParams);

    int64_t rows = in->getDims()[HEIGHT];
    int64_t cols = in->getDims()[WIDTH];
    std::vector<int64_t> inputSizeH = {rows, cols};
    std::vector<int64_t> inputSizeV = {cols, rows};
    std::vector<int64_t> inputSizeUpsamplingH = {rows, cols * upsamplingFactor_};
    std::vector<int64_t> inputSizeUpsamplingV = {cols, rows * upsamplingFactor_};

    prepareBuffers(derivativeImage_, inputSizeH, inputSizeV);
    prepareBuffers(upSampledImage_, inputSizeUpsamplingH, inputSizeUpsamplingV);
    prepareBuffers(inPadded_, inputSizeUpsamplingH, inputSizeUpsamplingV);
    prepareBuffers(zeroCrossings_, inputSizeH, inputSizeV);
    prepareBuffers(confidences_, inputSizeH, inputSizeV);


}


void ZeroCrossingCPU::checkParams(std::shared_ptr<Buffer> in, std::shared_ptr<Buffer> out, const ConfigParams& configParams) {

    std::vector<int64_t> inputDims = in->getDims();
    std::vector<int64_t> outputDims = in->getDims();
    size_t inputSize = in->getData().size();
    size_t outputSize = out->getData().size();

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
	    THROW_EXCEPTION("Invalid threshold size");
    }

}


void ZeroCrossingCPU::setConfigParams(const ConfigParams& configParams) {

    configParams_.threshold = configParams.threshold;    
    
    if (configParams_.threshold < 0.f) {
        THROW_EXCEPTION("Threshold can not be negative");
    } 

}


void ZeroCrossingCPU::prepareBuffers(BufferSet& bufferset, std::vector<int64_t>& dimsH, std::vector<int64_t>& dimsV) {
  
    bufferset.h = std::make_shared<Buffer>(dimsH[HEIGHT], dimsH[WIDTH]);
    bufferset.v = std::make_shared<Buffer>(dimsV[HEIGHT], dimsV[WIDTH]);

}


const IZeroCrossing<Buffer>::ConfigParams ZeroCrossingCPU::getConfigParams() {
    
    return configParams_;

}

std::shared_ptr<Buffer> ZeroCrossingCPU::getZeroCrossingH(){

    return zeroCrossings_.h;

}


std::shared_ptr<Buffer> ZeroCrossingCPU::getZeroCrossingV(){

    return zeroCrossings_.v;

}
