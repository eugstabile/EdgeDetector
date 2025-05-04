if(MSVC)
    target_include_directories(${LIBRARY_NAME} PUBLIC   
        "./"
        "C:/Users/EugenioStabile.MSI-ES/Desarrollo/TesisEugenio/EdgeDetector/tvm/include/"
        "C:/Users/EugenioStabile.MSI-ES/Desarrollo/TesisEugenio/EdgeDetector/tvm/3rdparty/dlpack/include/"
        "C:/Users/EugenioStabile.MSI-ES/Desarrollo/TesisEugenio/EdgeDetector/tvm/3rdparty/dmlc-core/include/"
) 
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_include_directories(${LIBRARY_NAME} PUBLIC 
        "./"
        "/home/eusta/TesisEugenio/EdgeDetector/tvm/include/"
        "/home/eusta/TesisEugenio/EdgeDetector/tvm/3rdparty/dlpack/include/"
        "/home/eusta/TesisEugenio/EdgeDetector/tvm/3rdparty/dmlc-core/include/"
)
endif()
