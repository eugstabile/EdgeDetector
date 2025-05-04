/**
 * @file AlgorithmFactory.h
 * @author Eugenio Stabile (eugenio.stabile@photonicsens.com)
 * @brief Factory for the IAlgorithm interface
 * @version 2.0.0
 * @date 2024-03-22
 * 
 * Copyright (c) 2024, Photonicsens. All rights reserved.
 * 
 */

#pragma once

#ifndef _ALGORITHMFACTORY_H
#define _ALGORITHMFACTORY_H

#include "IAlgorithm.h"
#include "ZeroCrossingCPU.h"
#include "ZeroCrossingOpenMP.h"
#include "ZeroCrossingTVM.h"
#include "ZeroCrossingOpenCL.h"
#include "IBuffer.h"

class AlgorithmFactory {

public:

    /// It shows all version of zero crossing algorithm
    enum AlgorithmType { 
      ZERO_CROSSING_CPU = 0, ///< Sequential zero crossing algorithm
      ZERO_CROSSING_OPEN_MP = 1, ///< Optimized zero crossing algorithm
      ZERO_CROSSING_TVM = 2, ///< TVM zero crossing algorithm
      ZERO_CROSSING_OPENCL = 3 ///< TVM OpenCL zero crossing algorithm
    };

    ~AlgorithmFactory() = default;

    /**
     * @brief Get the Algorithm object of a zero crossing algorithm 
     * 
     * @tparam T can be IAlgorithm or IZeroCrossing
     * @param algorithmType enum that can be the sequential version of ZeroCrossing = 0, or the optimized version = 1
     * @return std::shared_ptr<T> 
     */
    template <class T>
    std::shared_ptr<T> getAlgorithm(AlgorithmType algorithmType) {

        std::shared_ptr<T> algorithm;
      
        switch (algorithmType) {    
            
            case AlgorithmType::ZERO_CROSSING_CPU: {
            
                algorithm = std::dynamic_pointer_cast<T>(std::make_shared<ZeroCrossingCPU>());
                break;
        
            } 

            case AlgorithmType::ZERO_CROSSING_OPEN_MP: {
            
                algorithm = std::dynamic_pointer_cast<T>(std::make_shared<ZeroCrossingOpenMP>());
                break;
        
            } 
            
            case AlgorithmType::ZERO_CROSSING_TVM: {
            
                algorithm = std::dynamic_pointer_cast<T>(std::make_shared<ZeroCrossingTVM>());
                break;
        
            } 

            case AlgorithmType::ZERO_CROSSING_OPENCL: {
            
                algorithm = std::dynamic_pointer_cast<T>(std::make_shared<ZeroCrossingOpenCL>());
                break;
        
            } 
            default: {
                THROW_EXCEPTION( "Unexpected AlgorithmType." );
            }
            
        }

        if (algorithm == nullptr) {
            throw;
        }
        return algorithm;
        
    }

    
    
    /**
     * @brief Get the Instance object. This function gets the instance of the algorithm that currenly are running. If there is any instance, it creates one.
     * 
     * @return * std::shared_ptr<AlgorithmFactory> 
     */
    static std::shared_ptr<AlgorithmFactory> getInstance();

private:

    /**
     * @brief Construct a new Algorithm Factory object
     * 
     */
    AlgorithmFactory() = default;
    static std::shared_ptr<AlgorithmFactory> instance_;

};

#endif
