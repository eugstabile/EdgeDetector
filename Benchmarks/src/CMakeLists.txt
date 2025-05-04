set(BENCHMARKS
    "Benchmark.cpp"
    "ZeroCrossingBenchmark.cpp"
)

add_executable(${BENCHMARK_NAME}
    ${BENCHMARKS}
    "main.cpp"
)
target_link_libraries(${BENCHMARK_NAME} gtest_main ${OpenCV_LIBRARIES} ${LIBRARY_NAME})
add_test(NAME ${BENCHMARK_NAME} COMMAND ${BENCHMARK_NAME})
