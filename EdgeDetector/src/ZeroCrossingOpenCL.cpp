#include <memory>

#include "EdgeDetectorException.h"
#include "ZeroCrossingOpenCL.h"
#include "ZeroCrossingCPU.h"
#include "OpenCLAdapter.h"
#include "OpenCVAdapter.h"

#define HEIGHT Buffer::DimsIndex::HEIGHT
#define WIDTH Buffer::DimsIndex::WIDTH


ZeroCrossingOpenCL::ZeroCrossingOpenCL() {
    
    std::shared_ptr<Kernel> kernel = std::make_shared<Kernel>();
 
    derivativeFilter_= kernel->getDerivativeFilter();
    upsamplingFilter_ = kernel->getUpsamplingFilter();
    upsamplingFactor_ = kernel->getUpsamplingFactor();
    openCLAdapter_->getOpenCLParams(openclParams_);

}


void ZeroCrossingOpenCL::compute(const std::shared_ptr<Buffer>& in, std::shared_ptr<Buffer>& out) {    

    // Horizontal edge computation
    openCLAdapter_->computeOpenCL("filterDerivative", openclParams_, in, derivativeFilter_, derivativeImage_.h);
    openCLAdapter_->computeOpenCL("calculateConfidences", openclParams_, derivativeImage_.h, confidences_.h);
    openCLAdapter_->computeOpenCL("upsamplingMatrix", openclParams_, derivativeImage_.h, inPadded_.h); 
    openCLAdapter_->computeOpenCL("filterUpsamplingGPU", openclParams_, inPadded_.h, upsamplingFilter_, upSampledImage_.h);
    openCLAdapter_->computeOpenCL("calculateEdges", openclParams_, confidences_.h, upSampledImage_.h, zeroCrossings_.h);
    
    // Vertical edge computation
    openCLAdapter_->computeOpenCL("transpose", openclParams_, in, inTranspose_);

    openCLAdapter_->computeOpenCL("filterDerivative", openclParams_, inTranspose_, derivativeFilter_, derivativeImage_.v);
    openCLAdapter_->computeOpenCL("calculateConfidences", openclParams_, derivativeImage_.v, confidences_.v);
    openCLAdapter_->computeOpenCL("upsamplingMatrix", openclParams_, derivativeImage_.v, inPadded_.v);
    openCLAdapter_->computeOpenCL("filterUpsamplingGPU", openclParams_, inPadded_.v, upsamplingFilter_, upSampledImage_.v);
    openCLAdapter_->computeOpenCL("calculateEdges", openclParams_, confidences_.v, upSampledImage_.v, zeroCrossings_.v);

    // Combine computation
    openCLAdapter_->computeOpenCL("transpose", openclParams_, zeroCrossings_.v, zeroCrossingsMapVTranspose_);
    openCLAdapter_->computeOpenCL("combineEdges", openclParams_, zeroCrossings_.h, zeroCrossingsMapVTranspose_, out);
    
}


void ZeroCrossingOpenCL::settingArguments(const std::shared_ptr<Buffer>& in, std::shared_ptr<Buffer>& out, const ConfigParams& configParams) {

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

    inTranspose_ = std::make_shared<Buffer>(in->getDims()[WIDTH], in->getDims()[HEIGHT]);
    zeroCrossingsMapVTranspose_ = std::make_shared<Buffer>(in->getDims()[HEIGHT], in->getDims()[WIDTH]);

}


void ZeroCrossingOpenCL::checkParams(const std::shared_ptr<Buffer>& in, std::shared_ptr<Buffer>& out, const ConfigParams& configParams) {


    std::vector<int64_t> inputDims = in->getDims();
    std::vector<int64_t> outputDims = out->getDims();
    
    size_t inputSize = openCLAdapter_->getSize(in->getData());
    size_t outputSize = openCLAdapter_->getSize(out->getData());

    if (inputSize != outputSize) {
	    THROW_EXCEPTION("Input and output sizes don't match");
    }
    
    if (inputDims != outputDims) {
	    THROW_EXCEPTION("Input and output dimensions don't match");
    }
    
    if (inputSize <= 0 || inputDims[HEIGHT] <= 1 || inputDims[WIDTH] <= openCLAdapter_->getSize(upsamplingFilter_)) {
	    THROW_EXCEPTION("Invalid input dimensions");
    }

    if (outputSize <= 0 || outputDims[HEIGHT] <= 1 || outputDims[WIDTH] <= openCLAdapter_->getSize(upsamplingFilter_)) {
	    THROW_EXCEPTION("Invalid output dimensions");
    }

    if (openCLAdapter_->getSize(derivativeFilter_) == 0) {
	    THROW_EXCEPTION("Invalid derivative filter");
    }

    if (openCLAdapter_->getSize(upsamplingFilter_) == 0) {
	    THROW_EXCEPTION("Invalid upsampling filter");
    }

    if (configParams.threshold < 0) {
	    THROW_EXCEPTION("Invalid threshold size");
    }

}


void ZeroCrossingOpenCL::setConfigParams(const ConfigParams& configParams) {

    configParams_.threshold = configParams.threshold;    
    
    if (configParams_.threshold < 0.f) {
        THROW_EXCEPTION("Threshold can not be negative");
    } 

}


void ZeroCrossingOpenCL::prepareBuffers(BufferSet& bufferset, const std::vector<int64_t>& dimsH, const std::vector<int64_t>& dimsV) {
  
    bufferset.h = std::make_shared<Buffer>(dimsH[HEIGHT], dimsH[WIDTH]);
    bufferset.v = std::make_shared<Buffer>(dimsV[HEIGHT], dimsV[WIDTH]);

}


const IZeroCrossing<Buffer>::ConfigParams ZeroCrossingOpenCL::getConfigParams() {
    
    return configParams_;

}

std::shared_ptr<Buffer> ZeroCrossingOpenCL::getZeroCrossingH(){

    return zeroCrossings_.h;

}


std::shared_ptr<Buffer> ZeroCrossingOpenCL::getZeroCrossingV(){

    return zeroCrossings_.v;

}