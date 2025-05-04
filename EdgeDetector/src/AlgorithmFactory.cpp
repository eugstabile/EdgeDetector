#include "EdgeDetectorException.h"
#include "AlgorithmFactory.h"


std::shared_ptr<AlgorithmFactory> AlgorithmFactory::instance_ = nullptr;


std::shared_ptr<AlgorithmFactory> AlgorithmFactory::getInstance() {

    if (instance_ == nullptr) {
        instance_.reset(new AlgorithmFactory());
    }

    return instance_;
  
}
