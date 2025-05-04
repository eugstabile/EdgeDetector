// tvm target: c -keys=cpu 
#define TVM_EXPORTS
#include "tvm/runtime/c_runtime_api.h"
#include "tvm/runtime/c_backend_api.h"
#include <math.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C"
#endif
TVM_DLL int32_t filterDerivative(void* args, int32_t* arg_type_ids, int32_t num_args, void* out_ret_value, int32_t* out_ret_tcode, void* resource_handle);
#ifdef __cplusplus
extern "C"
#endif
TVM_DLL int32_t filterDerivative(void* args, int32_t* arg_type_ids, int32_t num_args, void* out_ret_value, int32_t* out_ret_tcode, void* resource_handle) {
  int32_t inputData_code = arg_type_ids[0];
  int32_t kernel_code = arg_type_ids[1];
  int32_t outputData_code = arg_type_ids[2];
  void* inputData = (((TVMValue*)args)[0].v_handle);
  void* kernel = (((TVMValue*)args)[1].v_handle);
  void* outputData = (((TVMValue*)args)[2].v_handle);
  void* inputData_1 = (((DLTensor*)inputData)[0].data);
  void* filterDerivative_inputData_shape = (((DLTensor*)inputData)[0].shape);
  int32_t height = ((int32_t)((int64_t*)filterDerivative_inputData_shape)[0]);
  int32_t width = ((int32_t)((int64_t*)filterDerivative_inputData_shape)[1]);
  void* filterDerivative_inputData_strides = (((DLTensor*)inputData)[0].strides);
  int32_t stride = ((width == 1) ? 0 : ((filterDerivative_inputData_strides == NULL) ? 1 : ((int32_t)((int64_t*)filterDerivative_inputData_strides)[1])));
  int32_t stride_1 = ((height == 1) ? 0 : ((filterDerivative_inputData_strides == NULL) ? width : ((int32_t)((int64_t*)filterDerivative_inputData_strides)[0])));
  int32_t dev_id = (((DLTensor*)inputData)[0].device.device_id);
  void* kernel_1 = (((DLTensor*)kernel)[0].data);
  void* filterDerivative_kernel_shape = (((DLTensor*)kernel)[0].shape);
  int32_t sizeKernel = ((int32_t)((int64_t*)filterDerivative_kernel_shape)[0]);
  void* filterDerivative_kernel_strides = (((DLTensor*)kernel)[0].strides);
  int32_t stride_2 = ((sizeKernel == 1) ? 0 : ((filterDerivative_kernel_strides == NULL) ? 1 : ((int32_t)((int64_t*)filterDerivative_kernel_strides)[0])));
  void* outputData_1 = (((DLTensor*)outputData)[0].data);
  void* filterDerivative_outputData_shape = (((DLTensor*)outputData)[0].shape);
  void* filterDerivative_outputData_strides = (((DLTensor*)outputData)[0].strides);
  int32_t stride_3 = ((width == 1) ? 0 : ((filterDerivative_outputData_strides == NULL) ? 1 : ((int32_t)((int64_t*)filterDerivative_outputData_strides)[1])));
  int32_t stride_4 = ((height == 1) ? 0 : ((filterDerivative_outputData_strides == NULL) ? width : ((int32_t)((int64_t*)filterDerivative_outputData_strides)[0])));
  void* intermediate = TVMBackendAllocWorkspace(1, dev_id, ((uint64_t)4 * ((uint64_t)(height * width))), 2, 32);
  if (intermediate == NULL) {
    return -1;
  }
  for (int32_t i = 0; i < height; ++i) {
    for (int32_t j = 0; j < (sizeKernel / 2); ++j) {
      ((float*)intermediate)[((i * width) + j)] = 0.000000e+00f;
      if (0 <= (j - (sizeKernel / 2))) {
        for (int32_t m = 0; m < (((sizeKernel / 2) * 2) + 1); ++m) {
          ((float*)intermediate)[((i * width) + j)] = (((float*)intermediate)[((i * width) + j)] + (((float*)inputData_1)[((i * stride_1) + (((j + m) - (sizeKernel / 2)) * stride))] * ((float*)kernel_1)[(m * stride_2)]));
        }
      }
    }
    for (int32_t j_1 = 0; j_1 < (width - (sizeKernel / 2)); ++j_1) {
      ((float*)intermediate)[(((sizeKernel / 2) + (i * width)) + j_1)] = 0.000000e+00f;
      for (int32_t m_1 = 0; m_1 < (((sizeKernel / 2) * 2) + 1); ++m_1) {
        ((float*)intermediate)[(((sizeKernel / 2) + (i * width)) + j_1)] = (((float*)intermediate)[(((sizeKernel / 2) + (i * width)) + j_1)] + (((float*)inputData_1)[((i * stride_1) + ((j_1 + m_1) * stride))] * ((float*)kernel_1)[(m_1 * stride_2)]));
      }
    }
  }
  for (int32_t i_1 = 0; i_1 < height; ++i_1) {
    for (int32_t j_2 = 0; j_2 < width; ++j_2) {
      ((float*)outputData_1)[((i_1 * stride_4) + (j_2 * stride_3))] = ((((sizeKernel / 2) <= j_2) && (j_2 < (width - (sizeKernel / 2)))) ? ((float*)intermediate)[((i_1 * width) + j_2)] : 0.000000e+00f);
    }
  }
  if (TVMBackendFreeWorkspace(1, dev_id, intermediate) != 0) {
    return -1;
  }
  return 0;
}

// CodegenC: NOTE: Auto-generated entry function
#ifdef __cplusplus
extern "C"
#endif
TVM_DLL int32_t __tvm_main__(void* args, int* arg_type_ids, int num_args, void* out_ret_value, int* out_ret_tcode, void* resource_handle) {
  return filterDerivative(args, arg_type_ids, num_args, out_ret_value, out_ret_tcode, resource_handle);
}
