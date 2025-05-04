#include <omp.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <immintrin.h>

#include "EdgeDetectorException.h"
#include "Utils.h"


#define HEIGHT Buffer::DimsIndex::HEIGHT
#define WIDTH Buffer::DimsIndex::WIDTH
#define VECTOR_STEP 4


std::shared_ptr<Buffer> transpose(const std::shared_ptr<Buffer> in) {

    int height = in->getDims()[HEIGHT];
    int width = in->getDims()[WIDTH];
    std::shared_ptr<Buffer> inTranspose = std::make_shared<Buffer>(width, height);

    std::vector<float32_t>& input = in->getData();
    std::vector<float32_t>& output = inTranspose->getData();

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
                
            output[j * height + i] = input[i * width + j];
                
        }
    }

    return inTranspose;

}


std::shared_ptr<Buffer> transposeOptimized(const std::shared_ptr<Buffer> in) {

    const int height = in->getDims()[HEIGHT];
    const int width = in->getDims()[WIDTH];
    std::shared_ptr<Buffer> inTranspose = std::make_shared<Buffer>(width, height);

    const std::vector<float32_t>& input = in->getData();
    std::vector<float32_t>& output = inTranspose->getData();

    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < height - VECTOR_STEP; i+=VECTOR_STEP) {
        for (int j = 0; j < width - VECTOR_STEP; j+=VECTOR_STEP) {
                
            __m128 swap1 = _mm_loadu_ps(&input[i * width + j]);
            __m128 swap2 = _mm_loadu_ps(&input[(i + 1) * width + j]);
            __m128 swap3 = _mm_loadu_ps(&input[(i + 2) * width + j]);
            __m128 swap4 = _mm_loadu_ps(&input[(i + 3) * width + j]);

            _MM_TRANSPOSE4_PS(swap1, swap2, swap3, swap4);
            _mm_prefetch((char*)&input[i * width + j + VECTOR_STEP], _MM_HINT_T0);
            _mm_prefetch((char*)&input[(i + 1) * width + j + VECTOR_STEP], _MM_HINT_T0);
            _mm_prefetch((char*)&input[(i + 2) * width + j + VECTOR_STEP], _MM_HINT_T0);
            _mm_prefetch((char*)&input[(i + 3) * width + j + VECTOR_STEP], _MM_HINT_T0);

            
            _mm_storeu_ps(&output[j * height + i], swap1);
            _mm_storeu_ps(&output[(j + 1) * height + i], swap2);
            _mm_storeu_ps(&output[(j + 2) * height + i], swap3);
            _mm_storeu_ps(&output[(j + 3) * height + i], swap4);
                
        }        
    }
    
    #pragma omp parallel for
    for (int i = height - height % VECTOR_STEP; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            
            output[j * height + i] = input[i * width + j];

        }
    }

    #pragma omp parallel for
    for (int i = 0; i < height - height % VECTOR_STEP; ++i) {
        for (int j = width - width % VECTOR_STEP; j < width; ++j) {

            output[j * height + i] = input[i * width + j];

        }
    }

    return inTranspose;

}


void printMatrix(const std::shared_ptr<Buffer> in, std::string path) {
    
    std::ofstream outputfile(path);

    if (!outputfile) {
        THROW_EXCEPTION("The output file can not be open");
    }

    int height = in->getDims()[HEIGHT];
    int width = in->getDims()[WIDTH];

    std::vector<float32_t>& input = in->getData();

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            outputfile << std::setw(8) << std::fixed << std::setprecision(10) << input[i * width + j] << '\t';
        }
        outputfile << '\n';
    }

    outputfile.close();
    
}


void verifyOutput(const std::shared_ptr<Buffer> in, const std::shared_ptr<Buffer> out) {

    int height = in->getDims()[HEIGHT];
    int width = in->getDims()[WIDTH];
    int countError = 0;
    int countAll = 0;

    std::vector<float32_t>& input = in->getData();
    std::vector<float32_t>& output = out->getData();

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            
            float32_t inputData = input[i * width + j];
            float32_t outputData = output[i * width + j];

            if (inputData > 0.f || outputData > 0.f){ 
                countAll++;
            }

            if (abs(inputData - outputData) > tolerance_) {
                countError++;
                //THROW_EXCEPTION("Are differences between matrices");
            }
        }
    }

    std::cout << "El numero de diferencias es de: " << countError << std::endl;
    std::cout << "El numero de numeros distintos de 0 es " << countAll << std::endl;
    std::cout << "Representa un " << std::fixed << std::setprecision(2) << static_cast<float>(countError) / countAll * 100.f << "% de los numeros distintos de 0. " << std::endl;

}


void verifySynteticMatrixOutput(const std::shared_ptr<Buffer> in, float32_t zeroCrossingExpected) {

    int height = in->getDims()[HEIGHT];
    int width = in->getDims()[WIDTH];
    std::vector<float32_t>& input = in->getData();

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {

            float32_t inputData = input[i * width + j];

            auto isEqual = static_cast<float>(abs(inputData - zeroCrossingExpected)) < tolerance_;
        
            if (!(inputData == 0.f || inputData == 1.f || isEqual)) {
                THROW_EXCEPTION("SyntheticMatrix output is not correct");

            }
        }
    }
}


std::string saveToBin(std::shared_ptr<Buffer> out) {
    
    std::string pathOut = "matrixOut.bin";
    std::vector<float32_t>& output = out->getData();

    std::ofstream writeFile;
    writeFile.open(pathOut, std::ios::out | std::ios::binary);
    if (!output.empty())
    writeFile.write((char*)&output[0], output.size() * sizeof(float32_t));
    return pathOut;

}


void compareBinFiles(const std::string& outputBin, const std::string& outputCorrectBin) {
    
    std::ifstream fileOut(outputBin, std::ios::binary);
    std::ifstream fileCorrectOut(outputCorrectBin, std::ios::binary);

    if (!fileOut.is_open() || !fileCorrectOut.is_open()) {
        THROW_EXCEPTION("Some file can not be open.");
    }

    char byteOut, byteCorrectOut;
    while (fileOut.get(byteOut) && fileCorrectOut.get(byteCorrectOut)) {
        if (byteOut != byteCorrectOut) {
            THROW_EXCEPTION("There are differences between files");
        }
    }
    if (fileOut.get(byteOut) || fileCorrectOut.get(byteCorrectOut)) {
        THROW_EXCEPTION("Both files size are diferents.");
    }

}