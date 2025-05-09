cmake_minimum_required(VERSION 3.23)

project(EdgeProject VERSION 2.0.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS   ON)
set(CMAKE_CXX_STANDARD              17)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            OFF)


if(MSVC)

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/Release/bin")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/Release/lib")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/Release/lib")

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/Debug/bin")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/Debug/lib")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/Debug/lib")

    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    set(CMAKE_CXX_FLAGS_RELEASE " ${CMAKE_CXX_FLAGS_RELEASE} /MP /Gd /std:c++17 /openmp /O2 /nologo /arch:AVX2")
    set(CMAKE_CXX_FLAGS_DEBUG " ${CMAKE_CXX_FLAGS_DEBUG} /MP /Gd /std:c++17 /openmp /Od /nologo /arch:AVX2")

elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/Release/bin")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/Release/lib")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/Release/lib")

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/Debug/bin")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/Debug/lib")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/Debug/lib")

    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fopenmp -O3 -mavx2 -mfma -fstrict-aliasing")
    set(CMAKE_CXX_FLAGS_DEBUG " ${CMAKE_CXX_FLAGS_DEBUG} -fopenmp -mavx2 -mfma -fstrict-aliasing")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lm -L/usr/lib -lpthread -ldl")

endif()

set(LIBRARY_NAME EdgeDetector)
set(BENCHMARK_NAME Benchmarker)
set(TEST_NAME Tester)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

option(USE_TVM "Enable Apache TVM library." ON)
option(BUILD_TESTS "Build all tests." ON)
option(BUILD_BENCHMARKS "Build all benchmarks." ON)
option(ENABLE_WARNINGS "Enable to add warnings to a target." OFF)
option(ENABLE_WARNINGS_AS_ERRORS "Enable to threat warnings as errors." OFF)
option(ENABLE_SANITIZE_ADDR "Enable address sanitizer." OFF)
option(ENABLE_LTO "Enable LTO/IPO." ON)


include(docsDoxygen)

if(USE_TVM)
    add_definitions(-DDMLC_USE_LOGGING_LIBRARY=<tvm/runtime/logging.h>)
    set(TVM_LIB_NAME tvm_runtime)
    include(TVM)
    configure_imported_target(TVM_LIB_NAME)
endif()

if(ENABLE_WARNINGS)
    include(warnings)
endif()

if(ENABLE_SANITIZE_ADDR OR ENABLE_SANITIZE_UNDEF)
    include(sanitizer)
    add_sanitizer_flags(ENABLE_SANITIZE_ADDR ENABLE_SANITIZE_UNDEF)
endif()

if(ENABLE_LTO)
    include(LTO)
endif()


# Adding subdirectories
add_subdirectory(${LIBRARY_NAME})


if(BUILD_TESTS)
set(gtest_force_shared_crt ON CACHE BOOL "Always use msvcrt.dll" FORCE)
enable_testing()

add_subdirectory(Test)
add_subdirectory(Benchmarks)

endif()
