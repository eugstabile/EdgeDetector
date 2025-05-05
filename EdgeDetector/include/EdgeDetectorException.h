/**
 * @file EdgeDetectorException.h
 * @author Eugenio Stabile 
 * @brief Generic exception for EdgeDetector error handling
 * @version 2.0.0
 * @date 2024-04-05
 * 
 */

#pragma once

#ifndef _EDGEDETECTOREXCEPTION_H
#define _EDGEDETECTOREXCEPTION_H

#include <exception> 
#include <string> 
#include <optional> 


#define THROW_EXCEPTION( msg ) throw EdgeDetectorException( msg )
#define THROW_EXCEPTION_CODE( msg, errorCode ) throw EdgeDetectorException( msg, errorCode )

class EdgeDetectorException : public std::exception { 

public: 

	/**
	 * @brief Construct a new Edge Detector Exception object
	 * 
	 * @param msg 
	 * @param errorCode <optional> 
	 */
	explicit EdgeDetectorException(const std::string& msg) : message_(msg), 
															 errorCode_(std::nullopt) {}

	EdgeDetectorException(const std::string& msg, int code) : message_(msg), 
															  errorCode_(code) {}

	/**
	 * @brief Return the message of the Exception 
	 * 
	 * @return const char* 
	 */
	const char* what() const noexcept override {
		return message_.c_str();
	}

	std::optional<int> code() const noexcept {
        return errorCode_;
    }

private:

	std::string message_;
	std::optional<int> errorCode_;

}; 

#endif