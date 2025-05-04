// Function: coherentFilter_kernel
__kernel void coherentFilter_kernel(__global float* restrict iD, __global float* restrict kD, __global float* restrict oD, int height, int width);
__kernel void coherentFilter_kernel(__global float* restrict iD, __global float* restrict kD, __global float* restrict oD, int height, int width) {
  float kernelCompute[1];
  if ((convert_int(get_group_id(0))) < (height >> 6)) {
    for (int row_inner_inner = 0; row_inner_inner < 8; ++row_inner_inner) {
      for (int col_inner_inner = 0; col_inner_inner < 8; ++col_inner_inner) {
        kernelCompute[0] = 0.000000e+00f;
        for (int k = 0; k < 5; ++k) {
          for (int pos = 0; pos < 5; ++pos) {
            if (((((convert_int(get_group_id(1))) * 64) + ((convert_int(get_local_id(1))) * 8)) + col_inner_inner) < width) {
              kernelCompute[0] = (kernelCompute[0] + (iD[(((((((convert_int(get_group_id(1))) * 64) + (k * 9)) + ((convert_int(get_local_id(1))) * 8)) + (((((convert_int(get_group_id(0))) * 64) + ((convert_int(get_local_id(0))) * 8)) + row_inner_inner) * width)) + col_inner_inner) - 18)] * kD[pos]));
            }
          }
        }
        if (((((convert_int(get_group_id(1))) * 64) + ((convert_int(get_local_id(1))) * 8)) + col_inner_inner) < width) {
          oD[(((((convert_int(get_group_id(1))) * 64) + ((convert_int(get_local_id(1))) * 8)) + (((((convert_int(get_group_id(0))) * 64) + ((convert_int(get_local_id(0))) * 8)) + row_inner_inner) * width)) + col_inner_inner)] = (((9 <= ((((convert_int(get_group_id(0))) * 32) + ((convert_int(get_local_id(0))) * 4)) + (row_inner_inner >> 1))) & ((((((convert_int(get_group_id(0))) * 64) + ((convert_int(get_local_id(0))) * 8)) + row_inner_inner) + 18) < height)) ? (((9 <= ((((convert_int(get_group_id(1))) * 32) + ((convert_int(get_local_id(1))) * 4)) + (col_inner_inner >> 1))) & ((((((convert_int(get_group_id(1))) * 64) + ((convert_int(get_local_id(1))) * 8)) + col_inner_inner) + 18) < width)) ? kernelCompute[0] : iD[(((((convert_int(get_group_id(1))) * 64) + ((convert_int(get_local_id(1))) * 8)) + (((((convert_int(get_group_id(0))) * 64) + ((convert_int(get_local_id(0))) * 8)) + row_inner_inner) * width)) + col_inner_inner)]) : iD[(((((convert_int(get_group_id(1))) * 64) + ((convert_int(get_local_id(1))) * 8)) + (((((convert_int(get_group_id(0))) * 64) + ((convert_int(get_local_id(0))) * 8)) + row_inner_inner) * width)) + col_inner_inner)]);
        }
      }
    }
  } else {
    for (int row_inner_inner_1 = 0; row_inner_inner_1 < 8; ++row_inner_inner_1) {
      for (int col_inner_inner_1 = 0; col_inner_inner_1 < 8; ++col_inner_inner_1) {
        kernelCompute[0] = 0.000000e+00f;
        for (int k_1 = 0; k_1 < 5; ++k_1) {
          for (int pos_1 = 0; pos_1 < 5; ++pos_1) {
            if (((((convert_int(get_group_id(0))) * 64) + ((convert_int(get_local_id(0))) * 8)) + row_inner_inner_1) < height) {
              if (((((convert_int(get_group_id(1))) * 64) + ((convert_int(get_local_id(1))) * 8)) + col_inner_inner_1) < width) {
                kernelCompute[0] = (kernelCompute[0] + (iD[(((((((convert_int(get_group_id(1))) * 64) + (k_1 * 9)) + ((convert_int(get_local_id(1))) * 8)) + (((((convert_int(get_group_id(0))) * 64) + ((convert_int(get_local_id(0))) * 8)) + row_inner_inner_1) * width)) + col_inner_inner_1) - 18)] * kD[pos_1]));
              }
            }
          }
        }
        if (((((convert_int(get_group_id(0))) * 64) + ((convert_int(get_local_id(0))) * 8)) + row_inner_inner_1) < height) {
          if (((((convert_int(get_group_id(1))) * 64) + ((convert_int(get_local_id(1))) * 8)) + col_inner_inner_1) < width) {
            oD[(((((convert_int(get_group_id(1))) * 64) + ((convert_int(get_local_id(1))) * 8)) + (((((convert_int(get_group_id(0))) * 64) + ((convert_int(get_local_id(0))) * 8)) + row_inner_inner_1) * width)) + col_inner_inner_1)] = (((9 <= ((((convert_int(get_group_id(0))) * 32) + ((convert_int(get_local_id(0))) * 4)) + (row_inner_inner_1 >> 1))) & ((((((convert_int(get_group_id(0))) * 64) + ((convert_int(get_local_id(0))) * 8)) + row_inner_inner_1) + 18) < height)) ? (((9 <= ((((convert_int(get_group_id(1))) * 32) + ((convert_int(get_local_id(1))) * 4)) + (col_inner_inner_1 >> 1))) & ((((((convert_int(get_group_id(1))) * 64) + ((convert_int(get_local_id(1))) * 8)) + col_inner_inner_1) + 18) < width)) ? kernelCompute[0] : iD[(((((convert_int(get_group_id(1))) * 64) + ((convert_int(get_local_id(1))) * 8)) + (((((convert_int(get_group_id(0))) * 64) + ((convert_int(get_local_id(0))) * 8)) + row_inner_inner_1) * width)) + col_inner_inner_1)]) : iD[(((((convert_int(get_group_id(1))) * 64) + ((convert_int(get_local_id(1))) * 8)) + (((((convert_int(get_group_id(0))) * 64) + ((convert_int(get_local_id(0))) * 8)) + row_inner_inner_1) * width)) + col_inner_inner_1)]);
          }
        }
      }
    }
  }
}

