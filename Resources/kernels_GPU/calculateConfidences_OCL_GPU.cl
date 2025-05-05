// Function: calculateConfidences_kernel
__kernel void calculateConfidences_kernel(__global float* restrict iD, __global float* restrict oD, int height, int width);
__kernel void calculateConfidences_kernel(__global float* restrict iD, __global float* restrict oD, int height, int width) {
  if ((convert_int(get_group_id(0))) < (height >> 5)) {
    if ((((convert_int(get_group_id(1))) * 32) + (convert_int(get_local_id(1)))) < width) {
      oD[((((convert_int(get_group_id(1))) * 32) + ((((convert_int(get_group_id(0))) * 32) + (convert_int(get_local_id(0)))) * width)) + (convert_int(get_local_id(1))))] = (((((convert_int((7 <= (((convert_int(get_group_id(1))) * 32) + (convert_int(get_local_id(1))))))) & (((convert_int(get_group_id(1))) * 32) + (convert_int(get_local_id(1))))) + 6) < width) ? fabs((iD[(((((convert_int(get_group_id(1))) * 32) + ((((convert_int(get_group_id(0))) * 32) + (convert_int(get_local_id(0)))) * width)) + (convert_int(get_local_id(1)))) - 1)] - iD[((((convert_int(get_group_id(1))) * 32) + ((((convert_int(get_group_id(0))) * 32) + (convert_int(get_local_id(0)))) * width)) + (convert_int(get_local_id(1))))])) : 0.000000e+00f);
    }
  } else {
    if ((((convert_int(get_group_id(0))) * 32) + (convert_int(get_local_id(0)))) < height) {
      if ((((convert_int(get_group_id(1))) * 32) + (convert_int(get_local_id(1)))) < width) {
        oD[((((convert_int(get_group_id(1))) * 32) + ((((convert_int(get_group_id(0))) * 32) + (convert_int(get_local_id(0)))) * width)) + (convert_int(get_local_id(1))))] = (((((convert_int((7 <= (((convert_int(get_group_id(1))) * 32) + (convert_int(get_local_id(1))))))) & (((convert_int(get_group_id(1))) * 32) + (convert_int(get_local_id(1))))) + 6) < width) ? fabs((iD[(((((convert_int(get_group_id(1))) * 32) + ((((convert_int(get_group_id(0))) * 32) + (convert_int(get_local_id(0)))) * width)) + (convert_int(get_local_id(1)))) - 1)] - iD[((((convert_int(get_group_id(1))) * 32) + ((((convert_int(get_group_id(0))) * 32) + (convert_int(get_local_id(0)))) * width)) + (convert_int(get_local_id(1))))])) : 0.000000e+00f);
      }
    }
  }
}