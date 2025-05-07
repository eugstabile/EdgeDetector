set(TESTS
    "BufferTest.cpp"
    "OpenCVAdapterTest.cpp"
    "ZeroCrossingCPUTest.cpp"
    "ZeroCrossingOpenMPTest.cpp"
    "ZeroCrossingOpenCLTest.cpp"
    "ZeroCrossingTVMTest.cpp"
)

add_executable(${TEST_NAME}
    "main.cpp"
    ${TESTS}
)

include(copyResources)

find_package(GTest REQUIRED)
target_link_libraries(${TEST_NAME} PUBLIC GTest::gtest ${LIBRARY_NAME})
  
add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})