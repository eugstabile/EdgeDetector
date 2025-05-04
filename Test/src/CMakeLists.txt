set(TESTS
    "BufferTest.cpp"
    "OpenCVAdapterTest.cpp"
    "ZeroCrossingCPUTest.cpp"
    "ZeroCrossingOpenMPTest.cpp"
    "ZeroCrossingOpenCLTest.cpp"
    "ZeroCrossingTVMTest.cpp"
)

add_executable(${TEST_NAME}
    ${TESTS}
    "main.cpp"
)
  
target_link_libraries(${TEST_NAME} PUBLIC gtest_main ${OpenCV_LIBRARIES} ${LIBRARY_NAME})
  
add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})