/**
 * @file OpenCVAdapter.h
 * @author Eugenio Stabile
 * @brief Adapter to OpenCV library to manage the input/output image
 * @version 2.0.0
 * @date 2024-03-18
 * 
 * 
 */

#pragma once

#ifndef _OPENCVADAPTER_H
#define _OPENCVADAPTER_H

#include <iterator>
#include <opencv2/core/core.hpp>

#include "Utils.h"

using float32_t = float;

class OpenCVAdapter {

public:
  
    OpenCVAdapter() = default;
    ~OpenCVAdapter() = default;

    /**
     * @brief This function gets an image by passing a path and it convertes into a Buffer object
     * 
     * @param path 
     * @return std::shared_ptr<Buffer> 
     */
    std::shared_ptr<Buffer> obtainImage(const std::string& path);
    
    /**
     * @brief This function stores an image with the designed name
     * 
     * @param inputImage 
     * @param imageName 
     */
    void saveImage(const std::shared_ptr<Buffer>& inputImage, const std::string& imageName);
    
    /**
     * @brief This function displays an Buffer object using OpenCV.
     * 
     * @param inputImage 
     * @param titleWindow 
     */
    void showImage(const std::shared_ptr<Buffer>& inputImage, const std::string& titleWindow);
    
    /**
     * @brief This fuction transforms a T object into a CV::Mat 
     * 
     * @param inputImage 
     * @return cv::Mat 
     */
    cv::Mat bufferToMat(const std::shared_ptr<Buffer>& inputImage);

    /**
     * @brief This fuction transforms a CV::Mat into a Buffer object 
     * 
     * @param image 
     * @return std::shared_ptr<Buffer> 
     */
    std::shared_ptr<Buffer> matToBuffer(cv::Mat& image);

    /**
     * @brief This function convert a cv::Mat with an RGB channel into a Buffer object 
     * 
     * @param imageRgb 
     * @return std::shared_ptr<Buffer> 
     */
    std::shared_ptr<Buffer> convertRgb2Gray(const cv::Mat& imageRgb);
    
    /**
     * @brief This function stores an cv::Mat image into a text plain format.
     * 
     * @param in 
     * @param path 
     */
    void printMatrixOpenCV(const cv::Mat& in, const std::string& path);
    
    /**
     * @brief Get the Bit Depth object
     * 
     * @return int 
     */
    int getBitDepth();

    /**
     * @brief Set the Bit Depth object
     * 
     * @param bitDepth 
     */
    void setBitDepth(int bitDepth);
    
private:

    const std::string pathFormat_ = ".png";
    std::vector<float32_t> image_;
    int bitDepth_ = 8;

};

#endif 