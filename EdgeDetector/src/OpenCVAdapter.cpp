#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include "EdgeDetectorException.h"
#include "OpenCVAdapter.h"

#define HEIGHT Buffer::DimsIndex::HEIGHT
#define WIDTH Buffer::DimsIndex::WIDTH

constexpr float LUMA_RED_FACTOR = 0.2989360212937f;
constexpr float LUMA_GREEN_FACTOR = 0.5870430744511f;
constexpr float LUMA_BLUE_FACTOR = 0.1140209042551f;


std::shared_ptr<Buffer> OpenCVAdapter::obtainImage(const std::string& path) {

    cv::Mat input = cv::imread(path + pathFormat_, cv::IMREAD_UNCHANGED);

    if (input.empty()) {
        THROW_EXCEPTION( "Invalid image path!" );
    }
    
    std::vector<int64_t> dimsImage = {static_cast<int64_t>(input.rows), static_cast<int64_t>(input.cols)};
    cv::Mat inputFloat;
    input.convertTo(inputFloat, CV_32F);
    inputFloat /= (pow(2, bitDepth_) - 1);
    std::shared_ptr<Buffer> buffer = input.channels() == 3 ? convertRgb2Gray(inputFloat) : matToBuffer(inputFloat);
    
    return buffer;

}


void OpenCVAdapter::saveImage(const std::shared_ptr<Buffer>& inputImage, const std::string& imageName) {
       
    std::shared_ptr<Buffer> inputCopy = std::make_shared<Buffer>(*inputImage);
    std::vector<int64_t> dimsImage = inputCopy->getDims();

    if (dimsImage.size() != 2) {
        THROW_EXCEPTION( "Invalid dimensions. 2 dims expected." );    
    }

    int height = static_cast<int64_t>(dimsImage[HEIGHT]);
    int width = static_cast<int64_t>(dimsImage[WIDTH]);
    cv::Mat image(height, width, CV_32F, inputCopy->getData().data());

    const std::string outputPath = imageName + pathFormat_;
    
    cv::normalize(image, image, 0, 255, cv::NORM_MINMAX);
    image.convertTo(image, CV_8U);

    if(!cv::imwrite(outputPath, image)){
        THROW_EXCEPTION( "Something wrong saving the image." );
    }
    
}


void OpenCVAdapter::showImage(const std::shared_ptr<Buffer>& inputImage, const std::string& titleWindow) {

    std::vector<int64_t> dimsImage = inputImage->getDims();
    int height = static_cast<int64_t>(dimsImage[HEIGHT]);
    int width = static_cast<int64_t>(dimsImage[WIDTH]);
    cv::Mat image(height, width, CV_32F, inputImage->getData().data());

    if (image.empty()) {
        THROW_EXCEPTION( "Empty image." );
    }


    cv::imshow(titleWindow, image);
    cv::waitKey(0);
    cv::destroyAllWindows();

}


cv::Mat OpenCVAdapter::bufferToMat(const std::shared_ptr<Buffer>& inputImage) {
    
    std::vector<int64_t> dimsImage = inputImage->getDims();
    int height = static_cast<int64_t>(dimsImage[HEIGHT]);
    int width = static_cast<int64_t>(dimsImage[WIDTH]);

    cv::Mat image(height, width, CV_32F, inputImage->getData().data());    
    return image;

}


std::shared_ptr<Buffer> OpenCVAdapter::matToBuffer(cv::Mat& image) {
    
    std::vector<int64_t> dimsImage = {static_cast<int64_t>(image.rows), static_cast<int64_t>(image.cols)};
    std::vector<float> array((float *)image.data, (float *)image.data + image.rows * image.cols);
    std::shared_ptr<Buffer> buffer = std::make_shared<Buffer>();
    buffer->setData(array, dimsImage);
    return buffer;

}


std::shared_ptr<Buffer> OpenCVAdapter::convertRgb2Gray(const cv::Mat& imageRgb) {
	
	std::vector<cv::Mat> channels(3);
	cv::split(imageRgb, channels);
	cv::Mat blueCh = channels[0];
	cv::Mat greenCh = channels[1];
	cv::Mat redCh = channels[2];
	cv::Mat lumaImage = (LUMA_RED_FACTOR* redCh) + (LUMA_GREEN_FACTOR * greenCh) + (LUMA_BLUE_FACTOR * blueCh);

    std::shared_ptr<Buffer> output = matToBuffer(lumaImage);   
	return output;

}


void OpenCVAdapter::printMatrixOpenCV(const cv::Mat& in, const std::string& path) {

	std::vector<int64_t> dimsImage = {static_cast<int64_t>(in.rows), static_cast<int64_t>(in.cols)};
    std::vector<float32_t> array((float32_t *)in.data, (float32_t *)in.data + in.rows * in.cols);
    std::vector<float32_t> image = array;

    std::shared_ptr<Buffer> buffer = std::make_shared<Buffer>();
    buffer->setData(image, dimsImage);
	printMatrix(buffer, path);

}


int OpenCVAdapter::getBitDepth() {
    
    return bitDepth_;

}


void OpenCVAdapter::setBitDepth(int bitDepth) {
    
    bitDepth_ = bitDepth;

}