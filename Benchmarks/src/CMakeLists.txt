set(BENCHMARKS
    "Benchmark.cpp"
    "ZeroCrossingBenchmark.cpp"
)

add_executable(${BENCHMARK_NAME}
    "main.cpp"
    ${BENCHMARKS}
)

find_package(GTest REQUIRED)
target_link_libraries(${BENCHMARK_NAME} GTest::gtest ${LIBRARY_NAME})

add_test(NAME ${BENCHMARK_NAME} COMMAND ${BENCHMARK_NAME})