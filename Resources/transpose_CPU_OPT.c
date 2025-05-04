// tvm target: c -keys=cpu 
#define TVM_EXPORTS
#include "tvm/runtime/c_runtime_api.h"
#include "tvm/runtime/c_backend_api.h"
#include <math.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C"
#endif
TVM_DLL int32_t transpose(void* args, int32_t* arg_type_ids, int32_t num_args, void* out_ret_value, int32_t* out_ret_tcode, void* resource_handle);
#ifdef __cplusplus
extern "C"
#endif
TVM_DLL int32_t transpose(void* args, int32_t* arg_type_ids, int32_t num_args, void* out_ret_value, int32_t* out_ret_tcode, void* resource_handle) {
  int32_t derivativeData_code = arg_type_ids[0];
  int32_t outputData_code = arg_type_ids[1];
  void* derivativeData = (((TVMValue*)args)[0].v_handle);
  void* outputData = (((TVMValue*)args)[1].v_handle);
  void* derivativeData_1 = (((DLTensor*)derivativeData)[0].data);
  void* transpose_derivativeData_shape = (((DLTensor*)derivativeData)[0].shape);
  int32_t height = ((int32_t)((int64_t*)transpose_derivativeData_shape)[0]);
  int32_t width = ((int32_t)((int64_t*)transpose_derivativeData_shape)[1]);
  void* transpose_derivativeData_strides = (((DLTensor*)derivativeData)[0].strides);
  int32_t stride = ((width == 1) ? 0 : ((transpose_derivativeData_strides == NULL) ? 1 : ((int32_t)((int64_t*)transpose_derivativeData_strides)[1])));
  int32_t stride_1 = ((height == 1) ? 0 : ((transpose_derivativeData_strides == NULL) ? width : ((int32_t)((int64_t*)transpose_derivativeData_strides)[0])));
  int32_t dev_id = (((DLTensor*)derivativeData)[0].device.device_id);
  void* outputData_1 = (((DLTensor*)outputData)[0].data);
  void* transpose_outputData_shape = (((DLTensor*)outputData)[0].shape);
  void* transpose_outputData_strides = (((DLTensor*)outputData)[0].strides);
  int32_t stride_2 = ((height == 1) ? 0 : ((transpose_outputData_strides == NULL) ? 1 : ((int32_t)((int64_t*)transpose_outputData_strides)[1])));
  int32_t stride_3 = ((width == 1) ? 0 : ((transpose_outputData_strides == NULL) ? height : ((int32_t)((int64_t*)transpose_outputData_strides)[0])));
  for (int32_t i = 0; i < width; ++i) {
    for (int32_t j = 0; j < height; ++j) {
      ((float*)outputData_1)[((i * stride_3) + (j * stride_2))] = ((float*)derivativeData_1)[((j * stride_1) + (i * stride))];
    }
  }
  return 0;
}

// CodegenC: NOTE: Auto-generated entry function
#ifdef __cplusplus
extern "C"
#endif
TVM_DLL int32_t __tvm_main__(void* args, int* arg_type_ids, int num_args, void* out_ret_value, int* out_ret_tcode, void* resource_handle) {
  return transpose(args, arg_type_ids, num_args, out_ret_value, out_ret_tcode, resource_handle);
}
