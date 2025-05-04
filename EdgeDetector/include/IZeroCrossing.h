/**
 * @class IZeroCrossing
 * @file IZeroCrossing.h
 * @author Eugenio Stabile (eugenio.stabile@photonicsens.com)
 * @brief Interface to define zero crossing algorithms on differents processors
 * @version 2.0.0
 * @date 2024-03-22
 * 
 * Copyright (c) 2024, Photonicsens. All rights reserved.
 * 
 */

#pragma once

#ifndef _IZEROCROSSING_H
#define _IZEROCROSSING_H

#include "IAlgorithm.h"

template <class T>
class IZeroCrossing : public IAlgorithm<T> {

public:
    
    /// @brief Set the threshold that the correctness
    struct ConfigParams {
        float32_t threshold = 0.015f;
    };
    
    virtual void settingArguments(std::shared_ptr<T> in, std::shared_ptr<T> out, const ConfigParams& configParams) = 0;
    virtual const ConfigParams getConfigParams() = 0;
    virtual void setConfigParams(const ConfigParams& configParams) = 0;
      
    virtual std::shared_ptr<T> getZeroCrossingH() = 0;
    virtual std::shared_ptr<T> getZeroCrossingV() = 0;

protected:

    int upsamplingFactor_;
    
};

#endif 