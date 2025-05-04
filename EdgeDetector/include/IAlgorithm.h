/**
 * @class IAlgorithm
 * @file IAlgorithm.h
 * @author Eugenio Stabile (eugenio.stabile@photonicsens.com)
 * @brief Interface to define the common methods for all algorithms
 * @version 2.0.0
 * @date 2024-03-22
 * 
 * 
 */

#pragma once

#ifndef _ALGORITHM_H
#define _ALGORITHM_H

#include "Utils.h"
#include "Kernel.h"

template <class T>
class IAlgorithm {

public:

    /**
     * @brief 
     * 
     * @param in 
     * @param out 
     */
    virtual void compute(std::shared_ptr<T> in, std::shared_ptr<T> out) = 0;

};

#endif 