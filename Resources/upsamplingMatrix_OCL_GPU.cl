// Function: upsamplingMatrix_kernel
__kernel void upsamplingMatrix_kernel(__global float* restrict iD, __global float* restrict oD, int height, int width);
__kernel void upsamplingMatrix_kernel(__global float* restrict iD, __global float* restrict oD, int height, int width) {
  
  int row = get_global_id(0);
  int col = get_global_id(1);

  if (col % 4 != 0) {
    oD[row * width + col] = 0.f;
  } else {
    oD[row * width + col] = iD[row * (width / 4) + (col / 4)];
  }
}

