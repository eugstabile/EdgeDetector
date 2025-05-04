add_library(${LIBRARY_NAME} STATIC 
    "AlgorithmFactory.cpp"
    "Buffer.cpp"
    "BufferTVM.cpp"
    "EdgeDetectorException.cpp"
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

if(OpenMP_CXX_FOUND)
    target_link_libraries(${LIBRARY_NAME} PUBLIC OpenMP::OpenMP_CXX OpenCL::OpenCL ${OpenCV_LIBRARIES} TVM_LIB_NAME)
else()
    target_link_libraries(${LIBRARY_NAME} PUBLIC ${OpenCV_LIBRARIES} TVM_LIB_NAME)
endif()