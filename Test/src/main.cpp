#include <gtest/gtest.h>

int main(int argc, char **argv) {
  
    ::testing::InitGoogleTest(&argc, argv);
    //::testing::GTEST_FLAG(filter) = "ZeroCrossingTest/ZeroCrossingTVMTest*";
    //::testing::GTEST_FLAG(filter) = "ZeroCrossingTest/ZeroCrossingCPUTest.zeroCrossingCPU_compute_realImage_success/0";
    //::testing::GTEST_FLAG(filter) = "ZeroCrossingTest/ZeroCrossingOpenCLTest.zeroCrossingOpenCL_compute_realImage_success/0:ZeroCrossingTest/ZeroCrossingOpenCLTest.zeroCrossingOpenCL_compute_syntheticMatrix_success/0";
    //::testing::GTEST_FLAG(filter) = "ZeroCrossingTest/ZeroCrossingOpenCLTest*";
    return RUN_ALL_TESTS();

}
