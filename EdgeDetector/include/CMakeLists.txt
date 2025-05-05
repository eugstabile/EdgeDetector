if(MSVC)
    target_include_directories(${LIBRARY_NAME} PUBLIC   
        "./"
        "${PROJECT_SOURCE_DIR}/tvm/include/"
        "${PROJECT_SOURCE_DIR}/tvm/3rdparty/dlpack/include/"
        "${PROJECT_SOURCE_DIR}/tvm/3rdparty/dmlc-core/include/"
) 
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_include_directories(${LIBRARY_NAME} PUBLIC 
        "./"
        "${PROJECT_SOURCE_DIR}/tvm/include/"
        "${PROJECT_SOURCE_DIR}/tvm/3rdparty/dlpack/include/"
        "${PROJECT_SOURCE_DIR}/tvm/3rdparty/dmlc-core/include/"
)
endif()
