// Function: transpose_kernel
__kernel void transpose_kernel(__global float* restrict iD, __global float* restrict oD, int height, int width);
__kernel void transpose_kernel(__global float* restrict iD, __global float* restrict oD, int height, int width) {
  for (int j_outer = 0; j_outer < ((height + 31) >> 5); ++j_outer) {
    if ((convert_int(get_group_id(0))) < (width >> 5)) {
      for (int j_inner = 0; j_inner < 32; ++j_inner) {
        if (((j_outer * 32) + j_inner) < height) {
          oD[(((j_outer * 32) + ((((convert_int(get_group_id(0))) * 32) + (convert_int(get_local_id(0)))) * height)) + j_inner)] = iD[((((convert_int(get_group_id(0))) * 32) + (((j_outer * 32) + j_inner) * width)) + (convert_int(get_local_id(0))))];
        }
      }
    } else {
      for (int j_inner_1 = 0; j_inner_1 < 32; ++j_inner_1) {
        if ((((convert_int(get_group_id(0))) * 32) + (convert_int(get_local_id(0)))) < width) {
          if (((j_outer * 32) + j_inner_1) < height) {
            oD[(((j_outer * 32) + ((((convert_int(get_group_id(0))) * 32) + (convert_int(get_local_id(0)))) * height)) + j_inner_1)] = iD[((((convert_int(get_group_id(0))) * 32) + (((j_outer * 32) + j_inner_1) * width)) + (convert_int(get_local_id(0))))];
          }
        }
      }
    }
  }
}