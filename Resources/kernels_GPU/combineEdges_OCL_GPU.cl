// Function: combineEdges_kernel
__kernel void combineEdges_kernel(__global float* restrict hD, __global float* restrict vD, __global float* restrict oD, int height, int width);
__kernel void combineEdges_kernel(__global float* restrict hD, __global float* restrict vD, __global float* restrict oD, int height, int width) {
  if ((convert_int(get_group_id(0))) < (height >> 5)) {
    if ((((convert_int(get_group_id(1))) * 32) + (convert_int(get_local_id(1)))) < width) {
      oD[((((convert_int(get_group_id(1))) * 32) + ((((convert_int(get_group_id(0))) * 32) + (convert_int(get_local_id(0)))) * width)) + (convert_int(get_local_id(1))))] = (convert_float((0 < ((convert_int((0.000000e+00f < hD[((((convert_int(get_group_id(1))) * 32) + ((((convert_int(get_group_id(0))) * 32) + (convert_int(get_local_id(0)))) * width)) + (convert_int(get_local_id(1))))]))) + (convert_int((0.000000e+00f < vD[((((convert_int(get_group_id(1))) * 32) + ((((convert_int(get_group_id(0))) * 32) + (convert_int(get_local_id(0)))) * width)) + (convert_int(get_local_id(1))))])))))));
    }
  } else {
    if ((((convert_int(get_group_id(0))) * 32) + (convert_int(get_local_id(0)))) < height) {
      if ((((convert_int(get_group_id(1))) * 32) + (convert_int(get_local_id(1)))) < width) {
        oD[((((convert_int(get_group_id(1))) * 32) + ((((convert_int(get_group_id(0))) * 32) + (convert_int(get_local_id(0)))) * width)) + (convert_int(get_local_id(1))))] = (convert_float((0 < ((convert_int((0.000000e+00f < hD[((((convert_int(get_group_id(1))) * 32) + ((((convert_int(get_group_id(0))) * 32) + (convert_int(get_local_id(0)))) * width)) + (convert_int(get_local_id(1))))]))) + (convert_int((0.000000e+00f < vD[((((convert_int(get_group_id(1))) * 32) + ((((convert_int(get_group_id(0))) * 32) + (convert_int(get_local_id(0)))) * width)) + (convert_int(get_local_id(1))))])))))));
      }
    }
  }
}

