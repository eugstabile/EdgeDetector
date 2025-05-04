if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(TVM_PATH "${PROJECT_SOURCE_DIR}/tvm/build")
    set(TVM_LIB_PATH ${TVM_PATH}/"${TVM_LIB_NAME}.so")
elseif(MSVC)
    set(TVM_PATH "C:/Users/EugenioStabile.MSI-ES/Desarrollo/TesisEugenio/EdgeDetector/tvm/build/Release/")
    set(TVM_LIB_PATH "${TVM_PATH}/${TVM_LIB_NAME}.lib")
endif()

function(configure_imported_target TARGET_NAME)
    find_library(TVM_LIB NAMES ${TVM_LIB_NAME} PATHS ${TVM_PATH})
    add_library(${TARGET_NAME} SHARED IMPORTED)
    set_target_properties(${TARGET_NAME} PROPERTIES IMPORTED_LOCATION ${TVM_LIB})
    set_target_properties(${TARGET_NAME} PROPERTIES
        IMPORTED_IMPLIB_RELEASE ${TVM_LIB_PATH}
        IMPORTED_IMPLIB_DEBUG ${TVM_LIB_PATH}
        IMPORTED_IMPLIB_MINSIZEREL ${TVM_LIB_PATH}
        IMPORTED_IMPLIB_RELWITHDEBINFO ${TVM_LIB_PATH}
    )
endfunction()