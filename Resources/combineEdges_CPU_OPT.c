// tvm target: c -keys=cpu 
#define TVM_EXPORTS
#include "tvm/runtime/c_runtime_api.h"
#include "tvm/runtime/c_backend_api.h"
#include <math.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C"
#endif
TVM_DLL int32_t combineEdges(void* args, int32_t* arg_type_ids, int32_t num_args, void* out_ret_value, int32_t* out_ret_tcode, void* resource_handle);
#ifdef __cplusplus
extern "C"
#endif
TVM_DLL int32_t combineEdges(void* args, int32_t* arg_type_ids, int32_t num_args, void* out_ret_value, int32_t* out_ret_tcode, void* resource_handle) {
  int32_t horizontalData_code = arg_type_ids[0];
  int32_t verticalData_code = arg_type_ids[1];
  int32_t outputData_code = arg_type_ids[2];
  void* horizontalData = (((TVMValue*)args)[0].v_handle);
  void* verticalData = (((TVMValue*)args)[1].v_handle);
  void* outputData = (((TVMValue*)args)[2].v_handle);
  void* horizontalData_1 = (((DLTensor*)horizontalData)[0].data);
  void* combineEdges_horizontalData_shape = (((DLTensor*)horizontalData)[0].shape);
  int32_t height = ((int32_t)((int64_t*)combineEdges_horizontalData_shape)[0]);
  int32_t width = ((int32_t)((int64_t*)combineEdges_horizontalData_shape)[1]);
  void* combineEdges_horizontalData_strides = (((DLTensor*)horizontalData)[0].strides);
  int32_t stride = ((width == 1) ? 0 : ((combineEdges_horizontalData_strides == NULL) ? 1 : ((int32_t)((int64_t*)combineEdges_horizontalData_strides)[1])));
  int32_t stride_1 = ((height == 1) ? 0 : ((combineEdges_horizontalData_strides == NULL) ? width : ((int32_t)((int64_t*)combineEdges_horizontalData_strides)[0])));
  int32_t dev_id = (((DLTensor*)horizontalData)[0].device.device_id);
  void* verticalData_1 = (((DLTensor*)verticalData)[0].data);
  void* combineEdges_verticalData_shape = (((DLTensor*)verticalData)[0].shape);
  void* combineEdges_verticalData_strides = (((DLTensor*)verticalData)[0].strides);
  int32_t stride_2 = ((width == 1) ? 0 : ((combineEdges_verticalData_strides == NULL) ? 1 : ((int32_t)((int64_t*)combineEdges_verticalData_strides)[1])));
  int32_t stride_3 = ((height == 1) ? 0 : ((combineEdges_verticalData_strides == NULL) ? width : ((int32_t)((int64_t*)combineEdges_verticalData_strides)[0])));
  void* outputData_1 = (((DLTensor*)outputData)[0].data);
  void* combineEdges_outputData_shape = (((DLTensor*)outputData)[0].shape);
  void* combineEdges_outputData_strides = (((DLTensor*)outputData)[0].strides);
  int32_t stride_4 = ((width == 1) ? 0 : ((combineEdges_outputData_strides == NULL) ? 1 : ((int32_t)((int64_t*)combineEdges_outputData_strides)[1])));
  int32_t stride_5 = ((height == 1) ? 0 : ((combineEdges_outputData_strides == NULL) ? width : ((int32_t)((int64_t*)combineEdges_outputData_strides)[0])));
  for (int32_t i = 0; i < height; ++i) {
    for (int32_t j = 0; j < width; ++j) {
      ((float*)outputData_1)[((i * stride_5) + (j * stride_4))] = ((float)((0.000000e+00f < ((float*)horizontalData_1)[((i * stride_1) + (j * stride))]) || (0.000000e+00f < ((float*)verticalData_1)[((i * stride_3) + (j * stride_2))])));
    }
  }
  return 0;
}

// CodegenC: NOTE: Auto-generated entry function
#ifdef __cplusplus
extern "C"
#endif
TVM_DLL int32_t __tvm_main__(void* args, int* arg_type_ids, int num_args, void* out_ret_value, int* out_ret_tcode, void* resource_handle) {
  return combineEdges(args, arg_type_ids, num_args, out_ret_value, out_ret_tcode, resource_handle);
}
