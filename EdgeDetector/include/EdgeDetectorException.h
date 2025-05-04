/**
 * @file EdgeDetectorException.h
 * @author Eugenio Stabile (eugenio.stabile@photonicsens.com)
 * @brief Generic exception for EdgeDetector error handling
 * @version 2.0.0
 * @date 2024-04-05
 * 
 * 
 */

#pragma once

#ifndef _EDGEDETECTOREXCEPTION_H
#define _EDGEDETECTOREXCEPTION_H

#include <exception> 
#include <string> 


#define THROW_EXCEPTION( msg )  throw EdgeDetectorException( msg )

class EdgeDetectorException : public std::exception { 

public: 

	/**
	 * @brief Construct a new Edge Detector Exception object
	 * 
	 * @param msg 
	 */
	EdgeDetectorException(const char* msg); 

	/**
	 * @brief Return the message of the Exception 
	 * 
	 * @return const char* 
	 */
	const char* what() noexcept;

private: 

	std::string message_; 

}; 

#endif