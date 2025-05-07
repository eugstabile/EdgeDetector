add_library(${LIBRARY_NAME}
    "AlgorithmFactory.cpp"
    "Buffer.cpp"
    "BufferTVM.cpp"
    "Kernel.cpp"
    "OpenCLAdapter.cpp"
    "OpenCVAdapter.cpp"
    "SyntheticMatrix.cpp"
    "TVMAdapter.cpp"
    "Utils.cpp"
    "ZeroCrossingCPU.cpp"
    "ZeroCrossingOpenCL.cpp"
    "ZeroCrossingOpenMP.cpp"
    "ZeroCrossingTVM.cpp"
)

# OpenCV libraries
find_package(OpenCV REQUIRED core imgproc highgui)

# OpenMP libraries
find_package(OpenMP REQUIRED)

# OpenCL libraries
find_package(OpenCL REQUIRED)

target_link_libraries(${LIBRARY_NAME} PUBLIC    OpenMP::OpenMP_CXX 
                                                OpenCL::OpenCL 
                                                opencv_core 
                                                opencv_imgproc 
                                                opencv_highgui  
                                                TVM_LIB_NAME)