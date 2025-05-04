#include <memory>

#include "EdgeDetectorException.h"
#include "ZeroCrossingTVM.h"
#include "ZeroCrossingCPU.h"
#include "TVMAdapter.h"
#include "OpenCVAdapter.h"

#define HEIGHT Buffer::DimsIndex::HEIGHT
#define WIDTH Buffer::DimsIndex::WIDTH


ZeroCrossingTVM::ZeroCrossingTVM() {
    
    std::shared_ptr<Kernel> kernel = std::make_shared<Kernel>();
    std::vector<std::string> algorithms = {"filterDerivative", "calculateConfidences", "filterUpsampling", "calculateEdges", "combineEdges", "transpose"};
    tvmAdapter_ = std::make_shared<TVMAdapter>(algorithms);   

    derivativeFilter_= tvmAdapter_->vectorToTVM(kernel->getDerivativeFilter());
    upsamplingFilter_ = tvmAdapter_->vectorToTVM(kernel->getUpsamplingFilter());
    upsamplingFactor_ = kernel->getUpsamplingFactor();

    tvmAdapter_->getTVMParams();

}


void ZeroCrossingTVM::compute(std::shared_ptr<BufferTVM> in, std::shared_ptr<BufferTVM> out) {    

    // Horizontal edge computation
    tvmAdapter_->computeTVM("filterDerivative", in, derivativeFilter_, derivativeImage_.h);
    tvmAdapter_->computeTVM("calculateConfidences", derivativeImage_.h, confidences_.h);
    tvmAdapter_->computeTVM("filterUpsampling", derivativeImage_.h, upsamplingFilter_, upSampledImage_.h);
    tvmAdapter_->computeTVM("calculateEdges", confidences_.h, upSampledImage_.h, zeroCrossings_.h);

    // Vertical edge computation
    tvmAdapter_->computeTVM("transpose", in, inTranspose_);
    tvmAdapter_->computeTVM("filterDerivative", inTranspose_, derivativeFilter_, derivativeImage_.v);
    tvmAdapter_->computeTVM("calculateConfidences", derivativeImage_.v, confidences_.v);
    tvmAdapter_->computeTVM("filterUpsampling", derivativeImage_.v, upsamplingFilter_, upSampledImage_.v);
    tvmAdapter_->computeTVM("calculateEdges", confidences_.v, upSampledImage_.v, zeroCrossings_.v);
    
    // Combination
    tvmAdapter_->computeTVM("transpose", zeroCrossings_.v, zeroCrossingsMapVTranspose_);
    tvmAdapter_->computeTVM("combineEdges", zeroCrossings_.h, zeroCrossingsMapVTranspose_, out);

}


void ZeroCrossingTVM::settingArguments(std::shared_ptr<BufferTVM> in, std::shared_ptr<BufferTVM> out, const ConfigParams& configParams) {

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

    inTranspose_ = std::make_shared<BufferTVM>(in->getDims()[WIDTH], in->getDims()[HEIGHT]);
    zeroCrossingsMapVTranspose_ = std::make_shared<BufferTVM>(in->getDims()[HEIGHT], in->getDims()[WIDTH]);

}


void ZeroCrossingTVM::checkParams(std::shared_ptr<BufferTVM> in, std::shared_ptr<BufferTVM> out, const ConfigParams& configParams) {

    std::vector<int64_t> inputDims = in->getDims();
    std::vector<int64_t> outputDims = out->getDims();
    
    size_t inputSize = tvmAdapter_->getSize(in->getData());
    size_t outputSize = tvmAdapter_->getSize(out->getData());

    if (inputSize != outputSize) {
	    THROW_EXCEPTION("Input and output sizes don't match");
    }
    
    if (inputDims != outputDims) {
	    THROW_EXCEPTION("Input and output dimensions don't match");
    }
    
    if (inputSize <= 0 || inputDims[HEIGHT] <= 1 || inputDims[WIDTH] <= tvmAdapter_->getSize(upsamplingFilter_)) {
	    THROW_EXCEPTION("Invalid input dimensions");
    }

    if (outputSize <= 0 || outputDims[HEIGHT] <= 1 || outputDims[WIDTH] <= tvmAdapter_->getSize(upsamplingFilter_)) {
	    THROW_EXCEPTION("Invalid output dimensions");
    }

    if (tvmAdapter_->getSize(derivativeFilter_) == 0) {
	    THROW_EXCEPTION("Invalid derivative filter");
    }

    if (tvmAdapter_->getSize(upsamplingFilter_) == 0) {
	    THROW_EXCEPTION("Invalid upsampling filter");
    }

    if (configParams.threshold < 0) {
	    THROW_EXCEPTION("Invalid threshold size");
    }

}


void ZeroCrossingTVM::setConfigParams(const ConfigParams& configParams) {

    configParams_.threshold = configParams.threshold;    
    
    if (configParams_.threshold < 0.f) {
        THROW_EXCEPTION("Threshold can not be negative");
    } 

}


void ZeroCrossingTVM::prepareBuffers(BufferSet& bufferset, std::vector<int64_t>& dimsH, std::vector<int64_t>& dimsV) {
  
    bufferset.h = std::make_shared<BufferTVM>(dimsH[HEIGHT], dimsH[WIDTH]);
    bufferset.v = std::make_shared<BufferTVM>(dimsV[HEIGHT], dimsV[WIDTH]);

}


const IZeroCrossing<BufferTVM>::ConfigParams ZeroCrossingTVM::getConfigParams() {
    
    return configParams_;

}

std::shared_ptr<BufferTVM> ZeroCrossingTVM::getZeroCrossingH(){

    return zeroCrossings_.h;

}


std::shared_ptr<BufferTVM> ZeroCrossingTVM::getZeroCrossingV(){

    return zeroCrossings_.v;

}