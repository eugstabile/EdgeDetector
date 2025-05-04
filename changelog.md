
# Changelog

## [2.0.0] - 2024-05-17

Fixed CPU version, added optimized CPU version.


### Added


#### AlgorithmFactory:

 - A new entry is added to the AlgorithmType enum for the optimized CPU version.

#### Utils:

 - The function **verifySyntheticMatrixOutput** checks if the synthetic matrix output is correct.


#### ZeroCrossingCPU:

   - Added **filterUpsampling** function. Previously, **filter2D** was used for both filters (derivative and upsampling). Now they are separated.


#### ZeroCrossingOpenMP:

 - Optimized CPU version with vectorization (SSE) and parallelization (OpenMP).

 - This version performs the derivative filter, upsampling filter, and edge search in the **calculateEdges** function. On each iteration:
    - Creates a new vector (*derivative data*) by applying the derivative filter to the input data.
    - Applies the upsampling filter to the derivative data if there is a zero crossing, and stores the result in the output vector. 


#### Benchmarks:

 - The **ZeroCrossingBenchmark** header unifies the configuration of benchmarks for different functions using GoogleTest [Fixtures](https://github.com/google/googletest/blob/main/docs/primer.md#test-fixtures-using-the-same-data-configuration-for-multiple-tests-same-data-multiple-tests).


#### Test:

 - The **ZeroCrossingTest** header unifies the configuration of tests for different functions using GoogleTest Fixtures.

 - The unit test version of **ZeroCrossingOpenMPTest** is created for the optimized CPU version.
   - It contains the same unit tests as the CPU version and a test that checks if the result is correct with respect to the sequential version (*zeroCrossingOpenMP_compute_sameOutputAsCPU*). 



### Changed


#### CMakeLists:

 - The -O2 (MSVC)  / -O3 (GCC) flags is addded for optimization in the *Release* variant.
 - Flags for vectorization are added.


#### Utils:

 - The **transpose** function was optimized for both CPU versions.
 - The **printMatrix** function now returns the first 10 decimal values.
 

#### ZeroCrossingCPU:

The CPU version has been modified for the derivative filter and upsampling. The previous version calculated the upsampling across the entire original matrix without preserving the original values, resulting in an altered signal. Consequently, the calculateEdges function searched for zero crossings in the entire upsampled signal, often leading to incorrect results due to the modified signal.
In the current version, the original values are preserved during upsampling. The calculateEdges function now searches for zero crossings in the original signal instead of the upsampled signal. If a zero crossing is found, it then verifies the zero crossing within a specific range of the upsampled signal. This approach ensures that the calculation is both more efficient and accurate.

 - The **filter2D** function is now called **filterDerivative**. 
 
 - In **calculateUpsampling**, the creation of a Buffer object *inPadded* to store the upsampling matrix is removed. Instead, it is done with a vector *inPadded* (same name).

 - **calculateEdges** selects 2 values where there is a zero crossing and does the interpolation without modifying those 2 points. Also, it verifies if there is a zero crossing before performing the interpolation.
 


#### Benchmarks:


 - The **Benchmark** file is modified to add the column *configuration*, which prints the version selected in the Markdown file output.

 - The **ZeroCrossingBenchmark** file is modified to use GoogleTest Fixtures. Also, benchmarks are added for the optimized CPU version.


#### Test:


 - The **ZeroCrossingCPUTest** file is modified to use GoogleTest Fixtures. Also, unit tests are added for the optimized CPU version.

 - Created new unit tests (*zeroCrossingCPU_validate_SyntheticMatrix_Horizontal_success*) and (*zeroCrossingCPU_validate_SyntheticMatrix_Vertical_success*) to verify the output of the zeroCrossings both horizontally and vertically.



### Fixed


#### ZeroCrossingCPU:

 -  The performance of the version is improved by 10%.


#### Benchmarks:

 - Error messages are displayed for all exceptions.


#### Test:

 - Error messages are displayed for all exceptions.