// Function: filterDerivative_kernel
__kernel void filterDerivative_kernel(__global float* restrict iD, __global float* restrict kdD, __global float* restrict oD, int height, int width);
__kernel void filterDerivative_kernel(__global float* restrict iD, __global float* restrict kdD, __global float* restrict oD, int height, int width) {
  float compute[1];
  if ((convert_int(get_group_id(0))) < (height >> 5)) {
    compute[0] = 0.000000e+00f;
    for (int m = 0; m < 13; ++m) {
      if ((((convert_int(get_group_id(1))) * 32) + (convert_int(get_local_id(1)))) < width) {
        compute[0] = (compute[0] + (iD[((((((convert_int(get_group_id(1))) * 32) + ((((convert_int(get_group_id(0))) * 32) + (convert_int(get_local_id(0)))) * width)) + (convert_int(get_local_id(1)))) + m) - 6)] * kdD[m]));
      }
    }
    if ((((convert_int(get_group_id(1))) * 32) + (convert_int(get_local_id(1)))) < width) {
      oD[((((convert_int(get_group_id(1))) * 32) + ((((convert_int(get_group_id(0))) * 32) + (convert_int(get_local_id(0)))) * width)) + (convert_int(get_local_id(1))))] = (((3 <= (((convert_int(get_group_id(1))) * 16) + ((convert_int(get_local_id(1))) >> 1))) & (((((convert_int(get_group_id(1))) * 32) + (convert_int(get_local_id(1)))) + 6) < width)) ? compute[0] : 0.000000e+00f);
    }
  } else {
    compute[0] = 0.000000e+00f;
    for (int m_1 = 0; m_1 < 13; ++m_1) {
      if ((((convert_int(get_group_id(0))) * 32) + (convert_int(get_local_id(0)))) < height) {
        if ((((convert_int(get_group_id(1))) * 32) + (convert_int(get_local_id(1)))) < width) {
          compute[0] = (compute[0] + (iD[((((((convert_int(get_group_id(1))) * 32) + ((((convert_int(get_group_id(0))) * 32) + (convert_int(get_local_id(0)))) * width)) + (convert_int(get_local_id(1)))) + m_1) - 6)] * kdD[m_1]));
        }
      }
    }
    if ((((convert_int(get_group_id(0))) * 32) + (convert_int(get_local_id(0)))) < height) {
      if ((((convert_int(get_group_id(1))) * 32) + (convert_int(get_local_id(1)))) < width) {
        oD[((((convert_int(get_group_id(1))) * 32) + ((((convert_int(get_group_id(0))) * 32) + (convert_int(get_local_id(0)))) * width)) + (convert_int(get_local_id(1))))] = (((3 <= (((convert_int(get_group_id(1))) * 16) + ((convert_int(get_local_id(1))) >> 1))) & (((((convert_int(get_group_id(1))) * 32) + (convert_int(get_local_id(1)))) + 6) < width)) ? compute[0] : 0.000000e+00f);
      }
    }
  }
}

