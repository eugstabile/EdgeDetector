#include <gtest/gtest.h>

int main(int argc, char **argv) {
  
  ::testing::InitGoogleTest(&argc, argv);
  //::testing::GTEST_FLAG(filter) = "ZeroCrossingBenchmark/ZeroCrossingOpenCLBenchmark.*/0:ZeroCrossingBenchmark/ZeroCrossingCPUBenchmark.*/0";
  ::testing::GTEST_FLAG(filter) =  "ZeroCrossingBenchmark/ZeroCrossingTVMBenchmark.benchmark_zeroCrossing_realImage/0"
                                   ":ZeroCrossingBenchmark/ZeroCrossingCPUBenchmark.benchmark_zeroCrossing_realImage/0"
                                   ":ZeroCrossingBenchmark/ZeroCrossingOpenCLBenchmark.benchmark_zeroCrossing_realImage/0"
                                   ":ZeroCrossingBenchmark/ZeroCrossingOpenMPBenchmark.benchmark_zeroCrossing_realImage/0";
  return RUN_ALL_TESTS();

  

}