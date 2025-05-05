// Function: filterUpsamplingGPU_kernel
__kernel void filterUpsamplingGPU_kernel(__global float* restrict iD, __global float* restrict zD, __global float* restrict oD, int height, int width);
__kernel void filterUpsamplingGPU_kernel(__global float* restrict iD, __global float* restrict zD, __global float* restrict oD, int height, int width) {
  float filterUp[1];
  if ((convert_int(get_group_id(0))) < (height >> 5)) {
    filterUp[0] = 0.000000e+00f;
    for (int u = 0; u < 53; ++u) {
      if ((((convert_int(get_group_id(1))) * 32) + (convert_int(get_local_id(1)))) < width) {
        filterUp[0] = (filterUp[0] + (iD[((((((convert_int(get_group_id(1))) * 32) + ((((convert_int(get_group_id(0))) * 32) + (convert_int(get_local_id(0)))) * width)) + (convert_int(get_local_id(1)))) + u) - 26)] * zD[u]));
      }
    }
    if ((((convert_int(get_group_id(1))) * 32) + (convert_int(get_local_id(1)))) < width) {
      oD[((((convert_int(get_group_id(1))) * 32) + ((((convert_int(get_group_id(0))) * 32) + (convert_int(get_local_id(0)))) * width)) + (convert_int(get_local_id(1))))] = (((7 <= (((convert_int(get_group_id(1))) * 8) + ((convert_int(get_local_id(1))) >> 2))) & (((((convert_int(get_group_id(1))) * 32) + (convert_int(get_local_id(1)))) + 28) < width)) ? ((((convert_int(get_local_id(1))) % 4) == 0) ? iD[((((convert_int(get_group_id(1))) * 32) + ((((convert_int(get_group_id(0))) * 32) + (convert_int(get_local_id(0)))) * width)) + (convert_int(get_local_id(1))))] : filterUp[0]) : 0.000000e+00f);
    }
  } else {
    filterUp[0] = 0.000000e+00f;
    for (int u_1 = 0; u_1 < 53; ++u_1) {
      if ((((convert_int(get_group_id(0))) * 32) + (convert_int(get_local_id(0)))) < height) {
        if ((((convert_int(get_group_id(1))) * 32) + (convert_int(get_local_id(1)))) < width) {
          filterUp[0] = (filterUp[0] + (iD[((((((convert_int(get_group_id(1))) * 32) + ((((convert_int(get_group_id(0))) * 32) + (convert_int(get_local_id(0)))) * width)) + (convert_int(get_local_id(1)))) + u_1) - 26)] * zD[u_1]));
        }
      }
    }
    if ((((convert_int(get_group_id(0))) * 32) + (convert_int(get_local_id(0)))) < height) {
      if ((((convert_int(get_group_id(1))) * 32) + (convert_int(get_local_id(1)))) < width) {
        oD[((((convert_int(get_group_id(1))) * 32) + ((((convert_int(get_group_id(0))) * 32) + (convert_int(get_local_id(0)))) * width)) + (convert_int(get_local_id(1))))] = (((7 <= (((convert_int(get_group_id(1))) * 8) + ((convert_int(get_local_id(1))) >> 2))) & (((((convert_int(get_group_id(1))) * 32) + (convert_int(get_local_id(1)))) + 28) < width)) ? ((((convert_int(get_local_id(1))) % 4) == 0) ? iD[((((convert_int(get_group_id(1))) * 32) + ((((convert_int(get_group_id(0))) * 32) + (convert_int(get_local_id(0)))) * width)) + (convert_int(get_local_id(1))))] : filterUp[0]) : 0.000000e+00f);
      }
    }
  }
}

