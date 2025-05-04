// tvm target: c -keys=cpu 
#define TVM_EXPORTS
#include "tvm/runtime/c_runtime_api.h"
#include "tvm/runtime/c_backend_api.h"
#include <math.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C"
#endif
TVM_DLL int32_t filterUpsampling(void* args, int32_t* arg_type_ids, int32_t num_args, void* out_ret_value, int32_t* out_ret_tcode, void* resource_handle);
#ifdef __cplusplus
extern "C"
#endif
TVM_DLL int32_t filterUpsampling(void* args, int32_t* arg_type_ids, int32_t num_args, void* out_ret_value, int32_t* out_ret_tcode, void* resource_handle) {
  int32_t derivativeData_code = arg_type_ids[0];
  int32_t zeroCrossingData_code = arg_type_ids[1];
  int32_t outputData_code = arg_type_ids[2];
  void* derivativeData = (((TVMValue*)args)[0].v_handle);
  void* zeroCrossingData = (((TVMValue*)args)[1].v_handle);
  void* outputData = (((TVMValue*)args)[2].v_handle);
  void* derivativeData_1 = (((DLTensor*)derivativeData)[0].data);
  void* filterUpsampling_derivativeData_shape = (((DLTensor*)derivativeData)[0].shape);
  int32_t height = ((int32_t)((int64_t*)filterUpsampling_derivativeData_shape)[0]);
  int32_t width = ((int32_t)((int64_t*)filterUpsampling_derivativeData_shape)[1]);
  void* filterUpsampling_derivativeData_strides = (((DLTensor*)derivativeData)[0].strides);
  int32_t stride = ((width == 1) ? 0 : ((filterUpsampling_derivativeData_strides == NULL) ? 1 : ((int32_t)((int64_t*)filterUpsampling_derivativeData_strides)[1])));
  int32_t stride_1 = ((height == 1) ? 0 : ((filterUpsampling_derivativeData_strides == NULL) ? width : ((int32_t)((int64_t*)filterUpsampling_derivativeData_strides)[0])));
  int32_t dev_id = (((DLTensor*)derivativeData)[0].device.device_id);
  void* zeroCrossingData_1 = (((DLTensor*)zeroCrossingData)[0].data);
  void* filterUpsampling_zeroCrossingData_shape = (((DLTensor*)zeroCrossingData)[0].shape);
  int32_t sizeKernel = ((int32_t)((int64_t*)filterUpsampling_zeroCrossingData_shape)[0]);
  void* filterUpsampling_zeroCrossingData_strides = (((DLTensor*)zeroCrossingData)[0].strides);
  int32_t stride_2 = ((sizeKernel == 1) ? 0 : ((filterUpsampling_zeroCrossingData_strides == NULL) ? 1 : ((int32_t)((int64_t*)filterUpsampling_zeroCrossingData_strides)[0])));
  void* outputData_1 = (((DLTensor*)outputData)[0].data);
  void* filterUpsampling_outputData_shape = (((DLTensor*)outputData)[0].shape);
  void* filterUpsampling_outputData_strides = (((DLTensor*)outputData)[0].strides);
  int32_t stride_3 = (((width * 4) == 1) ? 0 : ((filterUpsampling_outputData_strides == NULL) ? 1 : ((int32_t)((int64_t*)filterUpsampling_outputData_strides)[1])));
  int32_t stride_4 = ((height == 1) ? 0 : ((filterUpsampling_outputData_strides == NULL) ? (width * 4) : ((int32_t)((int64_t*)filterUpsampling_outputData_strides)[0])));
  void* inpaddedData = TVMBackendAllocWorkspace(1, dev_id, ((uint64_t)4 * ((uint64_t)(height * ((width * 4) + ((sizeKernel / 2) * 2))))), 2, 32);
  if (inpaddedData == NULL) {
    return -1;
  }
  void* upsamplingData = TVMBackendAllocWorkspace(1, dev_id, ((uint64_t)4 * ((uint64_t)((height * width) * 4))), 2, 32);
  if (upsamplingData == NULL) {
    return -1;
  }
  for (int32_t i_outer_j_outer_fused = 0; i_outer_j_outer_fused < (((height + 127) >> 7) * (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)); ++i_outer_j_outer_fused) {
    int32_t v_ = height - ((((((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) >= 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) >= 0)) || (((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) < 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) <= 0))) ? (i_outer_j_outer_fused / (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) : ((i_outer_j_outer_fused / (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) - 1)) * 128);
    for (int32_t i_inner = 0; i_inner < ((v_) < (128) ? (v_) : (128)); ++i_inner) {
      int32_t v__1 = (sizeKernel / 2) - ((((((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) >= 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) >= 0)) || (((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) < 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) <= 0))) ? (i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) : ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) + (((((sizeKernel / 2) + 63) >> 1) + width) >> 5))) * 128);
      for (int32_t j_inner = 0; j_inner < ((v__1) > (0) ? (v__1) : (0)); ++j_inner) {
        if ((((((((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) >= 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) >= 0)) || (((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) < 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) <= 0))) ? (i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) : ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) + (((((sizeKernel / 2) + 63) >> 1) + width) >> 5))) * 128) + j_inner) < ((width * 4) + ((sizeKernel / 2) * 2))) {
          if (0 <= ((((((((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) >= 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) >= 0)) || (((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) < 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) <= 0))) ? (i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) : ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) + (((((sizeKernel / 2) + 63) >> 1) + width) >> 5))) * 128) + j_inner) - (sizeKernel / 2))) {
            if (((((((((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) >= 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) >= 0)) || (((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) < 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) <= 0))) ? (i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) : ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) + (((((sizeKernel / 2) + 63) >> 1) + width) >> 5))) * 128) + j_inner) - (sizeKernel / 2)) < (width * 4)) {
              ((float*)inpaddedData)[((((((((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) >= 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) >= 0)) || (((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) < 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) <= 0))) ? (i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) : ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) + (((((sizeKernel / 2) + 63) >> 1) + width) >> 5))) * 128) + ((((((((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) >= 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) >= 0)) || (((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) < 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) <= 0))) ? (i_outer_j_outer_fused / (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) : ((i_outer_j_outer_fused / (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) - 1)) * 128) + i_inner) * ((width * 4) + ((sizeKernel / 2) * 2)))) + j_inner)] = ((((j_inner - (sizeKernel / 2)) % 4) == 0) ? ((float*)derivativeData_1)[(((((((((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) >= 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) >= 0)) || (((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) < 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) <= 0))) ? (i_outer_j_outer_fused / (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) : ((i_outer_j_outer_fused / (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) - 1)) * 128) + i_inner) * stride_1) + ((((((((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) >= 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) >= 0)) || (((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) < 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) <= 0))) ? (i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) : ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) + (((((sizeKernel / 2) + 63) >> 1) + width) >> 5))) * 32) + ((j_inner - (sizeKernel / 2)) >> 2)) * stride))] : 0.000000e+00f);
            }
          }
        }
      }
      int32_t v__2 = sizeKernel / 2;
      int32_t v__3 = (sizeKernel / 2) * 2;
      int32_t v__4 = ((width * 4) + ((v__2) < (v__3) ? (v__2) : (v__3))) - ((((((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) >= 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) >= 0)) || (((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) < 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) <= 0))) ? (i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) : ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) + (((((sizeKernel / 2) + 63) >> 1) + width) >> 5))) * 128);
      for (int32_t j_inner_1 = 0; j_inner_1 < (((v__4) < (128) ? (v__4) : (128)) - ((v__1) > (0) ? (v__1) : (0))); ++j_inner_1) {
        int32_t v__5 = (((((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) >= 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) >= 0)) || (((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) < 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) <= 0))) ? (i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) : ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) + (((((sizeKernel / 2) + 63) >> 1) + width) >> 5))) * 128;
        int32_t v__6 = sizeKernel / 2;
        ((float*)inpaddedData)[((((v__5) > (v__6) ? (v__5) : (v__6)) + ((((((((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) >= 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) >= 0)) || (((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) < 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) <= 0))) ? (i_outer_j_outer_fused / (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) : ((i_outer_j_outer_fused / (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) - 1)) * 128) + i_inner) * ((width * 4) + ((sizeKernel / 2) * 2)))) + j_inner_1)] = (((((((v__1) > (0) ? (v__1) : (0)) + j_inner_1) - (sizeKernel / 2)) % 4) == 0) ? ((float*)derivativeData_1)[(((((((((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) >= 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) >= 0)) || (((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) < 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) <= 0))) ? (i_outer_j_outer_fused / (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) : ((i_outer_j_outer_fused / (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) - 1)) * 128) + i_inner) * stride_1) + ((((((((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) >= 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) >= 0)) || (((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) < 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) <= 0))) ? (i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) : ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) + (((((sizeKernel / 2) + 63) >> 1) + width) >> 5))) * 32) + (((((v__1) > (0) ? (v__1) : (0)) + j_inner_1) - (sizeKernel / 2)) >> 2)) * stride))] : 0.000000e+00f);
      }
      int32_t v__7 = sizeKernel / 2;
      int32_t v__8 = (sizeKernel / 2) * 2;
      for (int32_t j_inner_2 = 0; j_inner_2 < (((((((((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) >= 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) >= 0)) || (((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) < 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) <= 0))) ? (i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) : ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) + (((((sizeKernel / 2) + 63) >> 1) + width) >> 5))) * 128) + 128) - ((v__7) < (v__8) ? (v__7) : (v__8))) - (width * 4)); ++j_inner_2) {
        int32_t v__9 = ((((((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) >= 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) >= 0)) || (((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) < 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) <= 0))) ? (i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) : ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) + (((((sizeKernel / 2) + 63) >> 1) + width) >> 5))) * 128) + 128;
        int32_t v__10 = sizeKernel / 2;
        int32_t v__11 = (sizeKernel / 2) * 2;
        int32_t v__12 = (width * 4) + ((v__10) < (v__11) ? (v__10) : (v__11));
        if ((((v__9) < (v__12) ? (v__9) : (v__12)) + j_inner_2) < ((width * 4) + ((sizeKernel / 2) * 2))) {
          if (0 <= ((((v__9) < (v__12) ? (v__9) : (v__12)) + j_inner_2) - (sizeKernel / 2))) {
            if (((((v__9) < (v__12) ? (v__9) : (v__12)) + j_inner_2) - (sizeKernel / 2)) < (width * 4)) {
              int32_t v__13 = ((width * 4) + ((v__10) < (v__11) ? (v__10) : (v__11))) - ((((((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) >= 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) >= 0)) || (((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) < 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) <= 0))) ? (i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) : ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) + (((((sizeKernel / 2) + 63) >> 1) + width) >> 5))) * 128);
              ((float*)inpaddedData)[((((v__9) < (v__12) ? (v__9) : (v__12)) + ((((((((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) >= 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) >= 0)) || (((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) < 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) <= 0))) ? (i_outer_j_outer_fused / (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) : ((i_outer_j_outer_fused / (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) - 1)) * 128) + i_inner) * ((width * 4) + ((sizeKernel / 2) * 2)))) + j_inner_2)] = (((((((v__13) < (128) ? (v__13) : (128)) + j_inner_2) - (sizeKernel / 2)) % 4) == 0) ? ((float*)derivativeData_1)[(((((((((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) >= 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) >= 0)) || (((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) < 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) <= 0))) ? (i_outer_j_outer_fused / (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) : ((i_outer_j_outer_fused / (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) - 1)) * 128) + i_inner) * stride_1) + ((((((((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) >= 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) >= 0)) || (((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) < 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) <= 0))) ? (i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) : ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) + (((((sizeKernel / 2) + 63) >> 1) + width) >> 5))) * 32) + (((((v__13) < (128) ? (v__13) : (128)) + j_inner_2) - (sizeKernel / 2)) >> 2)) * stride))] : 0.000000e+00f);
            }
          }
        }
      }
    }
    for (int32_t i_inner_1 = 0; i_inner_1 < ((((((((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) >= 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) >= 0)) || (((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) < 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) <= 0))) ? (i_outer_j_outer_fused / (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) : ((i_outer_j_outer_fused / (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) - 1)) * 128) + 128) - height); ++i_inner_1) {
      int32_t v__14 = ((((((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) >= 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) >= 0)) || (((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) < 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) <= 0))) ? (i_outer_j_outer_fused / (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) : ((i_outer_j_outer_fused / (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) - 1)) * 128) + 128;
      if ((((v__14) < (height) ? (v__14) : (height)) + i_inner_1) < height) {
        for (int32_t j_inner_3 = 0; j_inner_3 < 128; ++j_inner_3) {
          if ((((((((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) >= 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) >= 0)) || (((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) < 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) <= 0))) ? (i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) : ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) + (((((sizeKernel / 2) + 63) >> 1) + width) >> 5))) * 128) + j_inner_3) < ((width * 4) + ((sizeKernel / 2) * 2))) {
            if (0 <= ((((((((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) >= 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) >= 0)) || (((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) < 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) <= 0))) ? (i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) : ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) + (((((sizeKernel / 2) + 63) >> 1) + width) >> 5))) * 128) + j_inner_3) - (sizeKernel / 2))) {
              if (((((((((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) >= 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) >= 0)) || (((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) < 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) <= 0))) ? (i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) : ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) + (((((sizeKernel / 2) + 63) >> 1) + width) >> 5))) * 128) + j_inner_3) - (sizeKernel / 2)) < (width * 4)) {
                ((float*)inpaddedData)[((((((((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) >= 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) >= 0)) || (((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) < 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) <= 0))) ? (i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) : ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) + (((((sizeKernel / 2) + 63) >> 1) + width) >> 5))) * 128) + ((((v__14) < (height) ? (v__14) : (height)) + i_inner_1) * ((width * 4) + ((sizeKernel / 2) * 2)))) + j_inner_3)] = ((((j_inner_3 - (sizeKernel / 2)) % 4) == 0) ? ((float*)derivativeData_1)[(((((v__14) < (height) ? (v__14) : (height)) + i_inner_1) * stride_1) + ((((((((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) >= 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) >= 0)) || (((((((sizeKernel / 2) + 63) >> 1) + width) >> 5) < 0) && ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) <= 0))) ? (i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) : ((i_outer_j_outer_fused % (((((sizeKernel / 2) + 63) >> 1) + width) >> 5)) + (((((sizeKernel / 2) + 63) >> 1) + width) >> 5))) * 32) + ((j_inner_3 - (sizeKernel / 2)) >> 2)) * stride))] : 0.000000e+00f);
              }
            }
          }
        }
      }
    }
  }
  for (int32_t i_outer = 0; i_outer < (height >> 7); ++i_outer) {
    void* upsamplingData_local = TVMBackendAllocWorkspace(1, dev_id, ((uint64_t)4 * ((uint64_t)(width * 512))), 2, 32);
    if (upsamplingData_local == NULL) {
      return -1;
    }
    for (int32_t i_c = 0; i_c < 128; ++i_c) {
      for (int32_t j_c = 0; j_c < (width * 4); ++j_c) {
        ((float*)upsamplingData_local)[(((i_c * width) * 4) + j_c)] = 0.000000e+00f;
        if (j_c < ((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2)))) {
          for (int32_t m = 0; m < (((sizeKernel / 2) * 2) + 1); ++m) {
            ((float*)upsamplingData_local)[(((i_c * width) * 4) + j_c)] = (((float*)upsamplingData_local)[(((i_c * width) * 4) + j_c)] + (((float*)inpaddedData)[(((((i_outer * 128) + i_c) * ((width * 4) + ((sizeKernel / 2) * 2))) + j_c) + m)] * ((float*)zeroCrossingData_1)[(m * stride_2)]));
          }
        }
      }
    }
    for (int32_t j_outer = 0; j_outer < (width >> 5); ++j_outer) {
      for (int32_t i_inner_2 = 0; i_inner_2 < 128; ++i_inner_2) {
        for (int32_t j_inner_4 = 0; j_inner_4 < 128; ++j_inner_4) {
          if (((j_outer * 128) + j_inner_4) < ((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2)))) {
            int32_t cse_var_1 = (j_outer * 128);
            ((float*)upsamplingData)[((cse_var_1 + ((((i_outer * 128) + i_inner_2) * width) * 4)) + j_inner_4)] = ((float*)upsamplingData_local)[((cse_var_1 + ((i_inner_2 * width) * 4)) + j_inner_4)];
          }
        }
      }
    }
    for (int32_t j_outer_1 = 0; j_outer_1 < (((width & 31) + 31) >> 5); ++j_outer_1) {
      for (int32_t i_inner_3 = 0; i_inner_3 < 128; ++i_inner_3) {
        for (int32_t j_inner_5 = 0; j_inner_5 < 128; ++j_inner_5) {
          if (((((width >> 5) * 128) + (j_outer_1 * 128)) + j_inner_5) < (width * 4)) {
            if (((((width >> 5) * 128) + (j_outer_1 * 128)) + j_inner_5) < ((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2)))) {
              ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_1 * 128)) + ((((i_outer * 128) + i_inner_3) * width) * 4)) + j_inner_5)] = ((float*)upsamplingData_local)[(((((width >> 5) * 128) + (j_outer_1 * 128)) + ((i_inner_3 * width) * 4)) + j_inner_5)];
            }
          }
        }
      }
    }
    if (TVMBackendFreeWorkspace(1, dev_id, upsamplingData_local) != 0) {
      return -1;
    }
  }
  for (int32_t i_outer_1 = 0; i_outer_1 < (((height & 127) + 127) >> 7); ++i_outer_1) {
    void* upsamplingData_local_1 = TVMBackendAllocWorkspace(1, dev_id, ((uint64_t)4 * ((uint64_t)(width * 512))), 2, 32);
    if (upsamplingData_local_1 == NULL) {
      return -1;
    }
    for (int32_t i_c_1 = 0; i_c_1 < 128; ++i_c_1) {
      for (int32_t j_c_1 = 0; j_c_1 < (width * 4); ++j_c_1) {
        ((float*)upsamplingData_local_1)[(((i_c_1 * width) * 4) + j_c_1)] = 0.000000e+00f;
        if (((((height >> 7) * 128) + (i_outer_1 * 128)) + i_c_1) < height) {
          if (j_c_1 < ((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2)))) {
            for (int32_t m_1 = 0; m_1 < (((sizeKernel / 2) * 2) + 1); ++m_1) {
              ((float*)upsamplingData_local_1)[(((i_c_1 * width) * 4) + j_c_1)] = (((float*)upsamplingData_local_1)[(((i_c_1 * width) * 4) + j_c_1)] + (((float*)inpaddedData)[(((((((height >> 7) * 128) + (i_outer_1 * 128)) + i_c_1) * ((width * 4) + ((sizeKernel / 2) * 2))) + j_c_1) + m_1)] * ((float*)zeroCrossingData_1)[(m_1 * stride_2)]));
            }
          }
        }
      }
    }
    for (int32_t j_outer_2 = 0; j_outer_2 < ((width + 31) >> 5); ++j_outer_2) {
      for (int32_t i_inner_4 = 0; i_inner_4 < 128; ++i_inner_4) {
        if (((((height >> 7) * 128) + (i_outer_1 * 128)) + i_inner_4) < height) {
          for (int32_t j_inner_6 = 0; j_inner_6 < 128; ++j_inner_6) {
            if (((j_outer_2 * 128) + j_inner_6) < (width * 4)) {
              if (((j_outer_2 * 128) + j_inner_6) < ((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2)))) {
                int32_t cse_var_2 = (j_outer_2 * 128);
                ((float*)upsamplingData)[((cse_var_2 + ((((((height >> 7) * 128) + (i_outer_1 * 128)) + i_inner_4) * width) * 4)) + j_inner_6)] = ((float*)upsamplingData_local_1)[((cse_var_2 + ((i_inner_4 * width) * 4)) + j_inner_6)];
              }
            }
          }
        }
      }
    }
    if (TVMBackendFreeWorkspace(1, dev_id, upsamplingData_local_1) != 0) {
      return -1;
    }
  }
  int32_t v__15 = (height - 127) >> 7;
  int32_t v__16 = (height >> 7) - 1;
  int32_t v__17 = (v__15) < (v__16) ? (v__15) : (v__16);
  int32_t v__18 = (height - 113) >> 7;
  int32_t v__19 = (v__17) < (v__18) ? (v__17) : (v__18);
  int32_t v__20 = (height - 95) >> 7;
  int32_t v__21 = (v__19) < (v__20) ? (v__19) : (v__20);
  int32_t v__22 = (height - 102) >> 7;
  int32_t v__23 = (v__21) < (v__22) ? (v__21) : (v__22);
  int32_t v__24 = (height - 97) >> 7;
  int32_t v__25 = (v__23) < (v__24) ? (v__23) : (v__24);
  int32_t v__26 = (height - 71) >> 7;
  int32_t v__27 = (v__25) < (v__26) ? (v__25) : (v__26);
  int32_t v__28 = (height - 69) >> 7;
  int32_t v__29 = (v__27) < (v__28) ? (v__27) : (v__28);
  int32_t v__30 = (height - 68) >> 7;
  int32_t v__31 = (v__29) < (v__30) ? (v__29) : (v__30);
  int32_t v__32 = (height - 67) >> 7;
  int32_t v__33 = (v__31) < (v__32) ? (v__31) : (v__32);
  int32_t v__34 = (height - 30) >> 7;
  int32_t v__35 = (v__33) < (v__34) ? (v__33) : (v__34);
  int32_t v__36 = (height - 6) >> 7;
  int32_t v__37 = (v__35) < (v__36) ? (v__35) : (v__36);
  int32_t v__38 = (height - 21) >> 7;
  int32_t v__39 = (v__37) < (v__38) ? (v__37) : (v__38);
  int32_t v__40 = (height - 44) >> 7;
  int32_t v__41 = (v__39) < (v__40) ? (v__39) : (v__40);
  int32_t v__42 = (height - 17) >> 7;
  int32_t v__43 = (v__41) < (v__42) ? (v__41) : (v__42);
  int32_t v__44 = (height - 20) >> 7;
  int32_t v__45 = (v__43) < (v__44) ? (v__43) : (v__44);
  int32_t v__46 = (height - 25) >> 7;
  int32_t v__47 = (v__45) < (v__46) ? (v__45) : (v__46);
  int32_t v__48 = (height - 66) >> 7;
  int32_t v__49 = (v__47) < (v__48) ? (v__47) : (v__48);
  int32_t v__50 = (height - 19) >> 7;
  int32_t v__51 = (v__49) < (v__50) ? (v__49) : (v__50);
  int32_t v__52 = (height - 56) >> 7;
  int32_t v__53 = (v__51) < (v__52) ? (v__51) : (v__52);
  int32_t v__54 = (height - 18) >> 7;
  int32_t v__55 = (v__53) < (v__54) ? (v__53) : (v__54);
  int32_t v__56 = (height - 75) >> 7;
  int32_t v__57 = (v__55) < (v__56) ? (v__55) : (v__56);
  int32_t v__58 = (height - 40) >> 7;
  int32_t v__59 = (v__57) < (v__58) ? (v__57) : (v__58);
  int32_t v__60 = (height - 96) >> 7;
  int32_t v__61 = (v__59) < (v__60) ? (v__59) : (v__60);
  int32_t v__62 = (height - 16) >> 7;
  int32_t v__63 = (v__61) < (v__62) ? (v__61) : (v__62);
  int32_t v__64 = (height - 117) >> 7;
  int32_t v__65 = (v__63) < (v__64) ? (v__63) : (v__64);
  int32_t v__66 = (height - 60) >> 7;
  int32_t v__67 = (v__65) < (v__66) ? (v__65) : (v__66);
  int32_t v__68 = (height - 24) >> 7;
  int32_t v__69 = (v__67) < (v__68) ? (v__67) : (v__68);
  int32_t v__70 = (height - 38) >> 7;
  int32_t v__71 = (v__69) < (v__70) ? (v__69) : (v__70);
  int32_t v__72 = (height - 90) >> 7;
  int32_t v__73 = (v__71) < (v__72) ? (v__71) : (v__72);
  int32_t v__74 = (height - 23) >> 7;
  int32_t v__75 = (v__73) < (v__74) ? (v__73) : (v__74);
  int32_t v__76 = (height - 53) >> 7;
  int32_t v__77 = (v__75) < (v__76) ? (v__75) : (v__76);
  int32_t v__78 = (height - 65) >> 7;
  int32_t v__79 = (v__77) < (v__78) ? (v__77) : (v__78);
  int32_t v__80 = (height - 1) >> 7;
  int32_t v__81 = (v__79) < (v__80) ? (v__79) : (v__80);
  int32_t v__82 = (height - 70) >> 7;
  int32_t v__83 = (v__81) < (v__82) ? (v__81) : (v__82);
  int32_t v__84 = (height - 34) >> 7;
  int32_t v__85 = (v__83) < (v__84) ? (v__83) : (v__84);
  int32_t v__86 = (height - 101) >> 7;
  int32_t v__87 = (v__85) < (v__86) ? (v__85) : (v__86);
  int32_t v__88 = (height - 55) >> 7;
  int32_t v__89 = (v__87) < (v__88) ? (v__87) : (v__88);
  int32_t v__90 = (height - 57) >> 7;
  int32_t v__91 = (v__89) < (v__90) ? (v__89) : (v__90);
  int32_t v__92 = (height - 27) >> 7;
  int32_t v__93 = (v__91) < (v__92) ? (v__91) : (v__92);
  int32_t v__94 = (height - 108) >> 7;
  int32_t v__95 = (v__93) < (v__94) ? (v__93) : (v__94);
  int32_t v__96 = (height - 85) >> 7;
  int32_t v__97 = (v__95) < (v__96) ? (v__95) : (v__96);
  int32_t v__98 = (height - 3) >> 7;
  int32_t v__99 = (v__97) < (v__98) ? (v__97) : (v__98);
  int32_t v__100 = (height - 14) >> 7;
  int32_t v__101 = (v__99) < (v__100) ? (v__99) : (v__100);
  int32_t v__102 = (height - 109) >> 7;
  int32_t v__103 = (v__101) < (v__102) ? (v__101) : (v__102);
  int32_t v__104 = (height - 63) >> 7;
  int32_t v__105 = (v__103) < (v__104) ? (v__103) : (v__104);
  int32_t v__106 = (height - 28) >> 7;
  int32_t v__107 = (v__105) < (v__106) ? (v__105) : (v__106);
  int32_t v__108 = (height - 54) >> 7;
  int32_t v__109 = (v__107) < (v__108) ? (v__107) : (v__108);
  int32_t v__110 = (height - 15) >> 7;
  int32_t v__111 = (v__109) < (v__110) ? (v__109) : (v__110);
  int32_t v__112 = (height - 29) >> 7;
  int32_t v__113 = (v__111) < (v__112) ? (v__111) : (v__112);
  int32_t v__114 = (height - 36) >> 7;
  int32_t v__115 = (v__113) < (v__114) ? (v__113) : (v__114);
  int32_t v__116 = (height - 12) >> 7;
  int32_t v__117 = (v__115) < (v__116) ? (v__115) : (v__116);
  int32_t v__118 = (height - 119) >> 7;
  int32_t v__119 = (v__117) < (v__118) ? (v__117) : (v__118);
  int32_t v__120 = (height - 13) >> 7;
  int32_t v__121 = (v__119) < (v__120) ? (v__119) : (v__120);
  int32_t v__122 = (height - 77) >> 7;
  int32_t v__123 = (v__121) < (v__122) ? (v__121) : (v__122);
  int32_t v__124 = (height - 7) >> 7;
  int32_t v__125 = (v__123) < (v__124) ? (v__123) : (v__124);
  int32_t v__126 = (height - 120) >> 7;
  int32_t v__127 = (v__125) < (v__126) ? (v__125) : (v__126);
  int32_t v__128 = (height - 118) >> 7;
  int32_t v__129 = (v__127) < (v__128) ? (v__127) : (v__128);
  int32_t v__130 = (height - 8) >> 7;
  int32_t v__131 = (v__129) < (v__130) ? (v__129) : (v__130);
  int32_t v__132 = (height - 64) >> 7;
  int32_t v__133 = (v__131) < (v__132) ? (v__131) : (v__132);
  int32_t v__134 = (height - 42) >> 7;
  int32_t v__135 = (v__133) < (v__134) ? (v__133) : (v__134);
  int32_t v__136 = (height - 37) >> 7;
  int32_t v__137 = (v__135) < (v__136) ? (v__135) : (v__136);
  int32_t v__138 = (height - 99) >> 7;
  int32_t v__139 = (v__137) < (v__138) ? (v__137) : (v__138);
  int32_t v__140 = (height - 5) >> 7;
  int32_t v__141 = (v__139) < (v__140) ? (v__139) : (v__140);
  int32_t v__142 = (height - 31) >> 7;
  int32_t v__143 = (v__141) < (v__142) ? (v__141) : (v__142);
  int32_t v__144 = (height - 92) >> 7;
  int32_t v__145 = (v__143) < (v__144) ? (v__143) : (v__144);
  int32_t v__146 = (height - 47) >> 7;
  int32_t v__147 = (v__145) < (v__146) ? (v__145) : (v__146);
  int32_t v__148 = (height - 32) >> 7;
  int32_t v__149 = (v__147) < (v__148) ? (v__147) : (v__148);
  int32_t v__150 = (height - 91) >> 7;
  int32_t v__151 = (v__149) < (v__150) ? (v__149) : (v__150);
  int32_t v__152 = (height - 80) >> 7;
  int32_t v__153 = (v__151) < (v__152) ? (v__151) : (v__152);
  int32_t v__154 = (height - 33) >> 7;
  int32_t v__155 = (v__153) < (v__154) ? (v__153) : (v__154);
  int32_t v__156 = (height - 39) >> 7;
  int32_t v__157 = (v__155) < (v__156) ? (v__155) : (v__156);
  int32_t v__158 = (height - 41) >> 7;
  int32_t v__159 = (v__157) < (v__158) ? (v__157) : (v__158);
  int32_t v__160 = (height - 26) >> 7;
  int32_t v__161 = (v__159) < (v__160) ? (v__159) : (v__160);
  int32_t v__162 = (height - 107) >> 7;
  int32_t v__163 = (v__161) < (v__162) ? (v__161) : (v__162);
  int32_t v__164 = (height - 4) >> 7;
  int32_t v__165 = (v__163) < (v__164) ? (v__163) : (v__164);
  int32_t v__166 = (height - 9) >> 7;
  int32_t v__167 = (v__165) < (v__166) ? (v__165) : (v__166);
  int32_t v__168 = (height - 43) >> 7;
  int32_t v__169 = (v__167) < (v__168) ? (v__167) : (v__168);
  int32_t v__170 = (height - 46) >> 7;
  int32_t v__171 = (v__169) < (v__170) ? (v__169) : (v__170);
  int32_t v__172 = (height - 45) >> 7;
  int32_t v__173 = (v__171) < (v__172) ? (v__171) : (v__172);
  int32_t v__174 = (height - 22) >> 7;
  int32_t v__175 = (v__173) < (v__174) ? (v__173) : (v__174);
  int32_t v__176 = (height - 123) >> 7;
  int32_t v__177 = (v__175) < (v__176) ? (v__175) : (v__176);
  int32_t v__178 = (height - 51) >> 7;
  int32_t v__179 = (v__177) < (v__178) ? (v__177) : (v__178);
  int32_t v__180 = (height - 98) >> 7;
  int32_t v__181 = (v__179) < (v__180) ? (v__179) : (v__180);
  int32_t v__182 = (height - 114) >> 7;
  int32_t v__183 = (v__181) < (v__182) ? (v__181) : (v__182);
  int32_t v__184 = (height - 48) >> 7;
  int32_t v__185 = (v__183) < (v__184) ? (v__183) : (v__184);
  int32_t v__186 = (height - 122) >> 7;
  int32_t v__187 = (v__185) < (v__186) ? (v__185) : (v__186);
  int32_t v__188 = (height - 62) >> 7;
  int32_t v__189 = (v__187) < (v__188) ? (v__187) : (v__188);
  int32_t v__190 = (height - 35) >> 7;
  int32_t v__191 = (v__189) < (v__190) ? (v__189) : (v__190);
  int32_t v__192 = (height - 49) >> 7;
  int32_t v__193 = (v__191) < (v__192) ? (v__191) : (v__192);
  int32_t v__194 = (height - 50) >> 7;
  int32_t v__195 = (v__193) < (v__194) ? (v__193) : (v__194);
  int32_t v__196 = (height - 2) >> 7;
  int32_t v__197 = (v__195) < (v__196) ? (v__195) : (v__196);
  int32_t v__198 = (height - 10) >> 7;
  int32_t v__199 = (v__197) < (v__198) ? (v__197) : (v__198);
  int32_t v__200 = (height - 52) >> 7;
  int32_t v__201 = (v__199) < (v__200) ? (v__199) : (v__200);
  int32_t v__202 = (height - 58) >> 7;
  int32_t v__203 = (v__201) < (v__202) ? (v__201) : (v__202);
  int32_t v__204 = (height - 121) >> 7;
  int32_t v__205 = (v__203) < (v__204) ? (v__203) : (v__204);
  int32_t v__206 = (height - 59) >> 7;
  int32_t v__207 = (v__205) < (v__206) ? (v__205) : (v__206);
  int32_t v__208 = (height - 11) >> 7;
  int32_t v__209 = (v__207) < (v__208) ? (v__207) : (v__208);
  int32_t v__210 = (height - 61) >> 7;
  int32_t v__211 = ((v__209) < (v__210) ? (v__209) : (v__210)) + 1;
  int32_t v__212 = (height + 127) >> 7;
  for (int32_t i_outer_2 = 0; i_outer_2 < ((v__211) < (v__212) ? (v__211) : (v__212)); ++i_outer_2) {
    for (int32_t j_outer_3 = 0; j_outer_3 < (width >> 5); ++j_outer_3) {
      for (int32_t j_inner_s = 0; j_inner_s < 128; ++j_inner_s) {
        int32_t cse_var_4 = (j_outer_3 * 128);
        int32_t cse_var_3 = (cse_var_4 + j_inner_s);
        ((float*)outputData_1)[(((i_outer_2 * stride_4) * 128) + (cse_var_3 * stride_3))] = (((cse_var_3 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_3)) ? 0.000000e+00f : (((j_inner_s % 4) == 0) ? ((float*)derivativeData_1)[(((i_outer_2 * stride_1) * 128) + (((j_outer_3 * 32) + (j_inner_s >> 2)) * stride))] : ((float*)upsamplingData)[((((i_outer_2 * width) * 512) + cse_var_4) + j_inner_s)]));
      }
      for (int32_t j_inner_s_1 = 0; j_inner_s_1 < 128; ++j_inner_s_1) {
        int32_t cse_var_7 = (j_outer_3 * 128);
        int32_t cse_var_6 = ((i_outer_2 * 128) + 1);
        int32_t cse_var_5 = (cse_var_7 + j_inner_s_1);
        ((float*)outputData_1)[((cse_var_6 * stride_4) + (cse_var_5 * stride_3))] = (((cse_var_5 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_5)) ? 0.000000e+00f : (((j_inner_s_1 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_6 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_1 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_7 + ((cse_var_6 * width) * 4)) + j_inner_s_1)]));
      }
      for (int32_t j_inner_s_2 = 0; j_inner_s_2 < 128; ++j_inner_s_2) {
        int32_t cse_var_10 = (j_outer_3 * 128);
        int32_t cse_var_9 = ((i_outer_2 * 128) + 2);
        int32_t cse_var_8 = (cse_var_10 + j_inner_s_2);
        ((float*)outputData_1)[((cse_var_9 * stride_4) + (cse_var_8 * stride_3))] = (((cse_var_8 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_8)) ? 0.000000e+00f : (((j_inner_s_2 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_9 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_2 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_10 + ((cse_var_9 * width) * 4)) + j_inner_s_2)]));
      }
      for (int32_t j_inner_s_3 = 0; j_inner_s_3 < 128; ++j_inner_s_3) {
        int32_t cse_var_13 = (j_outer_3 * 128);
        int32_t cse_var_12 = ((i_outer_2 * 128) + 3);
        int32_t cse_var_11 = (cse_var_13 + j_inner_s_3);
        ((float*)outputData_1)[((cse_var_12 * stride_4) + (cse_var_11 * stride_3))] = (((cse_var_11 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_11)) ? 0.000000e+00f : (((j_inner_s_3 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_12 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_3 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_13 + ((cse_var_12 * width) * 4)) + j_inner_s_3)]));
      }
      for (int32_t j_inner_s_4 = 0; j_inner_s_4 < 128; ++j_inner_s_4) {
        int32_t cse_var_16 = (j_outer_3 * 128);
        int32_t cse_var_15 = ((i_outer_2 * 128) + 4);
        int32_t cse_var_14 = (cse_var_16 + j_inner_s_4);
        ((float*)outputData_1)[((cse_var_15 * stride_4) + (cse_var_14 * stride_3))] = (((cse_var_14 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_14)) ? 0.000000e+00f : (((j_inner_s_4 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_15 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_4 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_16 + ((cse_var_15 * width) * 4)) + j_inner_s_4)]));
      }
      for (int32_t j_inner_s_5 = 0; j_inner_s_5 < 128; ++j_inner_s_5) {
        int32_t cse_var_19 = (j_outer_3 * 128);
        int32_t cse_var_18 = ((i_outer_2 * 128) + 5);
        int32_t cse_var_17 = (cse_var_19 + j_inner_s_5);
        ((float*)outputData_1)[((cse_var_18 * stride_4) + (cse_var_17 * stride_3))] = (((cse_var_17 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_17)) ? 0.000000e+00f : (((j_inner_s_5 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_18 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_5 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_19 + ((cse_var_18 * width) * 4)) + j_inner_s_5)]));
      }
      for (int32_t j_inner_s_6 = 0; j_inner_s_6 < 128; ++j_inner_s_6) {
        int32_t cse_var_22 = (j_outer_3 * 128);
        int32_t cse_var_21 = ((i_outer_2 * 128) + 6);
        int32_t cse_var_20 = (cse_var_22 + j_inner_s_6);
        ((float*)outputData_1)[((cse_var_21 * stride_4) + (cse_var_20 * stride_3))] = (((cse_var_20 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_20)) ? 0.000000e+00f : (((j_inner_s_6 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_21 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_6 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_22 + ((cse_var_21 * width) * 4)) + j_inner_s_6)]));
      }
      for (int32_t j_inner_s_7 = 0; j_inner_s_7 < 128; ++j_inner_s_7) {
        int32_t cse_var_25 = (j_outer_3 * 128);
        int32_t cse_var_24 = ((i_outer_2 * 128) + 7);
        int32_t cse_var_23 = (cse_var_25 + j_inner_s_7);
        ((float*)outputData_1)[((cse_var_24 * stride_4) + (cse_var_23 * stride_3))] = (((cse_var_23 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_23)) ? 0.000000e+00f : (((j_inner_s_7 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_24 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_7 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_25 + ((cse_var_24 * width) * 4)) + j_inner_s_7)]));
      }
      for (int32_t j_inner_s_8 = 0; j_inner_s_8 < 128; ++j_inner_s_8) {
        int32_t cse_var_28 = (j_outer_3 * 128);
        int32_t cse_var_27 = ((i_outer_2 * 128) + 8);
        int32_t cse_var_26 = (cse_var_28 + j_inner_s_8);
        ((float*)outputData_1)[((cse_var_27 * stride_4) + (cse_var_26 * stride_3))] = (((cse_var_26 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_26)) ? 0.000000e+00f : (((j_inner_s_8 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_27 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_8 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_28 + ((cse_var_27 * width) * 4)) + j_inner_s_8)]));
      }
      for (int32_t j_inner_s_9 = 0; j_inner_s_9 < 128; ++j_inner_s_9) {
        int32_t cse_var_31 = (j_outer_3 * 128);
        int32_t cse_var_30 = ((i_outer_2 * 128) + 9);
        int32_t cse_var_29 = (cse_var_31 + j_inner_s_9);
        ((float*)outputData_1)[((cse_var_30 * stride_4) + (cse_var_29 * stride_3))] = (((cse_var_29 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_29)) ? 0.000000e+00f : (((j_inner_s_9 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_30 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_9 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_31 + ((cse_var_30 * width) * 4)) + j_inner_s_9)]));
      }
      for (int32_t j_inner_s_10 = 0; j_inner_s_10 < 128; ++j_inner_s_10) {
        int32_t cse_var_34 = (j_outer_3 * 128);
        int32_t cse_var_33 = ((i_outer_2 * 128) + 10);
        int32_t cse_var_32 = (cse_var_34 + j_inner_s_10);
        ((float*)outputData_1)[((cse_var_33 * stride_4) + (cse_var_32 * stride_3))] = (((cse_var_32 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_32)) ? 0.000000e+00f : (((j_inner_s_10 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_33 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_10 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_34 + ((cse_var_33 * width) * 4)) + j_inner_s_10)]));
      }
      for (int32_t j_inner_s_11 = 0; j_inner_s_11 < 128; ++j_inner_s_11) {
        int32_t cse_var_37 = (j_outer_3 * 128);
        int32_t cse_var_36 = ((i_outer_2 * 128) + 11);
        int32_t cse_var_35 = (cse_var_37 + j_inner_s_11);
        ((float*)outputData_1)[((cse_var_36 * stride_4) + (cse_var_35 * stride_3))] = (((cse_var_35 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_35)) ? 0.000000e+00f : (((j_inner_s_11 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_36 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_11 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_37 + ((cse_var_36 * width) * 4)) + j_inner_s_11)]));
      }
      for (int32_t j_inner_s_12 = 0; j_inner_s_12 < 128; ++j_inner_s_12) {
        int32_t cse_var_40 = (j_outer_3 * 128);
        int32_t cse_var_39 = ((i_outer_2 * 128) + 12);
        int32_t cse_var_38 = (cse_var_40 + j_inner_s_12);
        ((float*)outputData_1)[((cse_var_39 * stride_4) + (cse_var_38 * stride_3))] = (((cse_var_38 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_38)) ? 0.000000e+00f : (((j_inner_s_12 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_39 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_12 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_40 + ((cse_var_39 * width) * 4)) + j_inner_s_12)]));
      }
      for (int32_t j_inner_s_13 = 0; j_inner_s_13 < 128; ++j_inner_s_13) {
        int32_t cse_var_43 = (j_outer_3 * 128);
        int32_t cse_var_42 = ((i_outer_2 * 128) + 13);
        int32_t cse_var_41 = (cse_var_43 + j_inner_s_13);
        ((float*)outputData_1)[((cse_var_42 * stride_4) + (cse_var_41 * stride_3))] = (((cse_var_41 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_41)) ? 0.000000e+00f : (((j_inner_s_13 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_42 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_13 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_43 + ((cse_var_42 * width) * 4)) + j_inner_s_13)]));
      }
      for (int32_t j_inner_s_14 = 0; j_inner_s_14 < 128; ++j_inner_s_14) {
        int32_t cse_var_46 = (j_outer_3 * 128);
        int32_t cse_var_45 = ((i_outer_2 * 128) + 14);
        int32_t cse_var_44 = (cse_var_46 + j_inner_s_14);
        ((float*)outputData_1)[((cse_var_45 * stride_4) + (cse_var_44 * stride_3))] = (((cse_var_44 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_44)) ? 0.000000e+00f : (((j_inner_s_14 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_45 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_14 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_46 + ((cse_var_45 * width) * 4)) + j_inner_s_14)]));
      }
      for (int32_t j_inner_s_15 = 0; j_inner_s_15 < 128; ++j_inner_s_15) {
        int32_t cse_var_49 = (j_outer_3 * 128);
        int32_t cse_var_48 = ((i_outer_2 * 128) + 15);
        int32_t cse_var_47 = (cse_var_49 + j_inner_s_15);
        ((float*)outputData_1)[((cse_var_48 * stride_4) + (cse_var_47 * stride_3))] = (((cse_var_47 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_47)) ? 0.000000e+00f : (((j_inner_s_15 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_48 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_15 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_49 + ((cse_var_48 * width) * 4)) + j_inner_s_15)]));
      }
      for (int32_t j_inner_s_16 = 0; j_inner_s_16 < 128; ++j_inner_s_16) {
        int32_t cse_var_52 = (j_outer_3 * 128);
        int32_t cse_var_51 = ((i_outer_2 * 128) + 16);
        int32_t cse_var_50 = (cse_var_52 + j_inner_s_16);
        ((float*)outputData_1)[((cse_var_51 * stride_4) + (cse_var_50 * stride_3))] = (((cse_var_50 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_50)) ? 0.000000e+00f : (((j_inner_s_16 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_51 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_16 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_52 + ((cse_var_51 * width) * 4)) + j_inner_s_16)]));
      }
      for (int32_t j_inner_s_17 = 0; j_inner_s_17 < 128; ++j_inner_s_17) {
        int32_t cse_var_55 = (j_outer_3 * 128);
        int32_t cse_var_54 = ((i_outer_2 * 128) + 17);
        int32_t cse_var_53 = (cse_var_55 + j_inner_s_17);
        ((float*)outputData_1)[((cse_var_54 * stride_4) + (cse_var_53 * stride_3))] = (((cse_var_53 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_53)) ? 0.000000e+00f : (((j_inner_s_17 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_54 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_17 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_55 + ((cse_var_54 * width) * 4)) + j_inner_s_17)]));
      }
      for (int32_t j_inner_s_18 = 0; j_inner_s_18 < 128; ++j_inner_s_18) {
        int32_t cse_var_58 = (j_outer_3 * 128);
        int32_t cse_var_57 = ((i_outer_2 * 128) + 18);
        int32_t cse_var_56 = (cse_var_58 + j_inner_s_18);
        ((float*)outputData_1)[((cse_var_57 * stride_4) + (cse_var_56 * stride_3))] = (((cse_var_56 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_56)) ? 0.000000e+00f : (((j_inner_s_18 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_57 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_18 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_58 + ((cse_var_57 * width) * 4)) + j_inner_s_18)]));
      }
      for (int32_t j_inner_s_19 = 0; j_inner_s_19 < 128; ++j_inner_s_19) {
        int32_t cse_var_61 = (j_outer_3 * 128);
        int32_t cse_var_60 = ((i_outer_2 * 128) + 19);
        int32_t cse_var_59 = (cse_var_61 + j_inner_s_19);
        ((float*)outputData_1)[((cse_var_60 * stride_4) + (cse_var_59 * stride_3))] = (((cse_var_59 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_59)) ? 0.000000e+00f : (((j_inner_s_19 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_60 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_19 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_61 + ((cse_var_60 * width) * 4)) + j_inner_s_19)]));
      }
      for (int32_t j_inner_s_20 = 0; j_inner_s_20 < 128; ++j_inner_s_20) {
        int32_t cse_var_64 = (j_outer_3 * 128);
        int32_t cse_var_63 = ((i_outer_2 * 128) + 20);
        int32_t cse_var_62 = (cse_var_64 + j_inner_s_20);
        ((float*)outputData_1)[((cse_var_63 * stride_4) + (cse_var_62 * stride_3))] = (((cse_var_62 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_62)) ? 0.000000e+00f : (((j_inner_s_20 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_63 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_20 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_64 + ((cse_var_63 * width) * 4)) + j_inner_s_20)]));
      }
      for (int32_t j_inner_s_21 = 0; j_inner_s_21 < 128; ++j_inner_s_21) {
        int32_t cse_var_67 = (j_outer_3 * 128);
        int32_t cse_var_66 = ((i_outer_2 * 128) + 21);
        int32_t cse_var_65 = (cse_var_67 + j_inner_s_21);
        ((float*)outputData_1)[((cse_var_66 * stride_4) + (cse_var_65 * stride_3))] = (((cse_var_65 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_65)) ? 0.000000e+00f : (((j_inner_s_21 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_66 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_21 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_67 + ((cse_var_66 * width) * 4)) + j_inner_s_21)]));
      }
      for (int32_t j_inner_s_22 = 0; j_inner_s_22 < 128; ++j_inner_s_22) {
        int32_t cse_var_70 = (j_outer_3 * 128);
        int32_t cse_var_69 = ((i_outer_2 * 128) + 22);
        int32_t cse_var_68 = (cse_var_70 + j_inner_s_22);
        ((float*)outputData_1)[((cse_var_69 * stride_4) + (cse_var_68 * stride_3))] = (((cse_var_68 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_68)) ? 0.000000e+00f : (((j_inner_s_22 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_69 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_22 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_70 + ((cse_var_69 * width) * 4)) + j_inner_s_22)]));
      }
      for (int32_t j_inner_s_23 = 0; j_inner_s_23 < 128; ++j_inner_s_23) {
        int32_t cse_var_73 = (j_outer_3 * 128);
        int32_t cse_var_72 = ((i_outer_2 * 128) + 23);
        int32_t cse_var_71 = (cse_var_73 + j_inner_s_23);
        ((float*)outputData_1)[((cse_var_72 * stride_4) + (cse_var_71 * stride_3))] = (((cse_var_71 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_71)) ? 0.000000e+00f : (((j_inner_s_23 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_72 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_23 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_73 + ((cse_var_72 * width) * 4)) + j_inner_s_23)]));
      }
      for (int32_t j_inner_s_24 = 0; j_inner_s_24 < 128; ++j_inner_s_24) {
        int32_t cse_var_76 = (j_outer_3 * 128);
        int32_t cse_var_75 = ((i_outer_2 * 128) + 24);
        int32_t cse_var_74 = (cse_var_76 + j_inner_s_24);
        ((float*)outputData_1)[((cse_var_75 * stride_4) + (cse_var_74 * stride_3))] = (((cse_var_74 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_74)) ? 0.000000e+00f : (((j_inner_s_24 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_75 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_24 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_76 + ((cse_var_75 * width) * 4)) + j_inner_s_24)]));
      }
      for (int32_t j_inner_s_25 = 0; j_inner_s_25 < 128; ++j_inner_s_25) {
        int32_t cse_var_79 = (j_outer_3 * 128);
        int32_t cse_var_78 = ((i_outer_2 * 128) + 25);
        int32_t cse_var_77 = (cse_var_79 + j_inner_s_25);
        ((float*)outputData_1)[((cse_var_78 * stride_4) + (cse_var_77 * stride_3))] = (((cse_var_77 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_77)) ? 0.000000e+00f : (((j_inner_s_25 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_78 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_25 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_79 + ((cse_var_78 * width) * 4)) + j_inner_s_25)]));
      }
      for (int32_t j_inner_s_26 = 0; j_inner_s_26 < 128; ++j_inner_s_26) {
        int32_t cse_var_82 = (j_outer_3 * 128);
        int32_t cse_var_81 = ((i_outer_2 * 128) + 26);
        int32_t cse_var_80 = (cse_var_82 + j_inner_s_26);
        ((float*)outputData_1)[((cse_var_81 * stride_4) + (cse_var_80 * stride_3))] = (((cse_var_80 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_80)) ? 0.000000e+00f : (((j_inner_s_26 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_81 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_26 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_82 + ((cse_var_81 * width) * 4)) + j_inner_s_26)]));
      }
      for (int32_t j_inner_s_27 = 0; j_inner_s_27 < 128; ++j_inner_s_27) {
        int32_t cse_var_85 = (j_outer_3 * 128);
        int32_t cse_var_84 = ((i_outer_2 * 128) + 27);
        int32_t cse_var_83 = (cse_var_85 + j_inner_s_27);
        ((float*)outputData_1)[((cse_var_84 * stride_4) + (cse_var_83 * stride_3))] = (((cse_var_83 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_83)) ? 0.000000e+00f : (((j_inner_s_27 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_84 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_27 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_85 + ((cse_var_84 * width) * 4)) + j_inner_s_27)]));
      }
      for (int32_t j_inner_s_28 = 0; j_inner_s_28 < 128; ++j_inner_s_28) {
        int32_t cse_var_88 = (j_outer_3 * 128);
        int32_t cse_var_87 = ((i_outer_2 * 128) + 28);
        int32_t cse_var_86 = (cse_var_88 + j_inner_s_28);
        ((float*)outputData_1)[((cse_var_87 * stride_4) + (cse_var_86 * stride_3))] = (((cse_var_86 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_86)) ? 0.000000e+00f : (((j_inner_s_28 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_87 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_28 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_88 + ((cse_var_87 * width) * 4)) + j_inner_s_28)]));
      }
      for (int32_t j_inner_s_29 = 0; j_inner_s_29 < 128; ++j_inner_s_29) {
        int32_t cse_var_91 = (j_outer_3 * 128);
        int32_t cse_var_90 = ((i_outer_2 * 128) + 29);
        int32_t cse_var_89 = (cse_var_91 + j_inner_s_29);
        ((float*)outputData_1)[((cse_var_90 * stride_4) + (cse_var_89 * stride_3))] = (((cse_var_89 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_89)) ? 0.000000e+00f : (((j_inner_s_29 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_90 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_29 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_91 + ((cse_var_90 * width) * 4)) + j_inner_s_29)]));
      }
      for (int32_t j_inner_s_30 = 0; j_inner_s_30 < 128; ++j_inner_s_30) {
        int32_t cse_var_94 = (j_outer_3 * 128);
        int32_t cse_var_93 = ((i_outer_2 * 128) + 30);
        int32_t cse_var_92 = (cse_var_94 + j_inner_s_30);
        ((float*)outputData_1)[((cse_var_93 * stride_4) + (cse_var_92 * stride_3))] = (((cse_var_92 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_92)) ? 0.000000e+00f : (((j_inner_s_30 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_93 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_30 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_94 + ((cse_var_93 * width) * 4)) + j_inner_s_30)]));
      }
      for (int32_t j_inner_s_31 = 0; j_inner_s_31 < 128; ++j_inner_s_31) {
        int32_t cse_var_97 = (j_outer_3 * 128);
        int32_t cse_var_96 = ((i_outer_2 * 128) + 31);
        int32_t cse_var_95 = (cse_var_97 + j_inner_s_31);
        ((float*)outputData_1)[((cse_var_96 * stride_4) + (cse_var_95 * stride_3))] = (((cse_var_95 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_95)) ? 0.000000e+00f : (((j_inner_s_31 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_96 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_31 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_97 + ((cse_var_96 * width) * 4)) + j_inner_s_31)]));
      }
      for (int32_t j_inner_s_32 = 0; j_inner_s_32 < 128; ++j_inner_s_32) {
        int32_t cse_var_100 = (j_outer_3 * 128);
        int32_t cse_var_99 = ((i_outer_2 * 128) + 32);
        int32_t cse_var_98 = (cse_var_100 + j_inner_s_32);
        ((float*)outputData_1)[((cse_var_99 * stride_4) + (cse_var_98 * stride_3))] = (((cse_var_98 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_98)) ? 0.000000e+00f : (((j_inner_s_32 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_99 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_32 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_100 + ((cse_var_99 * width) * 4)) + j_inner_s_32)]));
      }
      for (int32_t j_inner_s_33 = 0; j_inner_s_33 < 128; ++j_inner_s_33) {
        int32_t cse_var_103 = (j_outer_3 * 128);
        int32_t cse_var_102 = ((i_outer_2 * 128) + 33);
        int32_t cse_var_101 = (cse_var_103 + j_inner_s_33);
        ((float*)outputData_1)[((cse_var_102 * stride_4) + (cse_var_101 * stride_3))] = (((cse_var_101 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_101)) ? 0.000000e+00f : (((j_inner_s_33 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_102 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_33 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_103 + ((cse_var_102 * width) * 4)) + j_inner_s_33)]));
      }
      for (int32_t j_inner_s_34 = 0; j_inner_s_34 < 128; ++j_inner_s_34) {
        int32_t cse_var_106 = (j_outer_3 * 128);
        int32_t cse_var_105 = ((i_outer_2 * 128) + 34);
        int32_t cse_var_104 = (cse_var_106 + j_inner_s_34);
        ((float*)outputData_1)[((cse_var_105 * stride_4) + (cse_var_104 * stride_3))] = (((cse_var_104 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_104)) ? 0.000000e+00f : (((j_inner_s_34 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_105 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_34 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_106 + ((cse_var_105 * width) * 4)) + j_inner_s_34)]));
      }
      for (int32_t j_inner_s_35 = 0; j_inner_s_35 < 128; ++j_inner_s_35) {
        int32_t cse_var_109 = (j_outer_3 * 128);
        int32_t cse_var_108 = ((i_outer_2 * 128) + 35);
        int32_t cse_var_107 = (cse_var_109 + j_inner_s_35);
        ((float*)outputData_1)[((cse_var_108 * stride_4) + (cse_var_107 * stride_3))] = (((cse_var_107 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_107)) ? 0.000000e+00f : (((j_inner_s_35 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_108 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_35 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_109 + ((cse_var_108 * width) * 4)) + j_inner_s_35)]));
      }
      for (int32_t j_inner_s_36 = 0; j_inner_s_36 < 128; ++j_inner_s_36) {
        int32_t cse_var_112 = (j_outer_3 * 128);
        int32_t cse_var_111 = ((i_outer_2 * 128) + 36);
        int32_t cse_var_110 = (cse_var_112 + j_inner_s_36);
        ((float*)outputData_1)[((cse_var_111 * stride_4) + (cse_var_110 * stride_3))] = (((cse_var_110 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_110)) ? 0.000000e+00f : (((j_inner_s_36 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_111 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_36 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_112 + ((cse_var_111 * width) * 4)) + j_inner_s_36)]));
      }
      for (int32_t j_inner_s_37 = 0; j_inner_s_37 < 128; ++j_inner_s_37) {
        int32_t cse_var_115 = (j_outer_3 * 128);
        int32_t cse_var_114 = ((i_outer_2 * 128) + 37);
        int32_t cse_var_113 = (cse_var_115 + j_inner_s_37);
        ((float*)outputData_1)[((cse_var_114 * stride_4) + (cse_var_113 * stride_3))] = (((cse_var_113 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_113)) ? 0.000000e+00f : (((j_inner_s_37 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_114 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_37 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_115 + ((cse_var_114 * width) * 4)) + j_inner_s_37)]));
      }
      for (int32_t j_inner_s_38 = 0; j_inner_s_38 < 128; ++j_inner_s_38) {
        int32_t cse_var_118 = (j_outer_3 * 128);
        int32_t cse_var_117 = ((i_outer_2 * 128) + 38);
        int32_t cse_var_116 = (cse_var_118 + j_inner_s_38);
        ((float*)outputData_1)[((cse_var_117 * stride_4) + (cse_var_116 * stride_3))] = (((cse_var_116 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_116)) ? 0.000000e+00f : (((j_inner_s_38 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_117 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_38 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_118 + ((cse_var_117 * width) * 4)) + j_inner_s_38)]));
      }
      for (int32_t j_inner_s_39 = 0; j_inner_s_39 < 128; ++j_inner_s_39) {
        int32_t cse_var_121 = (j_outer_3 * 128);
        int32_t cse_var_120 = ((i_outer_2 * 128) + 39);
        int32_t cse_var_119 = (cse_var_121 + j_inner_s_39);
        ((float*)outputData_1)[((cse_var_120 * stride_4) + (cse_var_119 * stride_3))] = (((cse_var_119 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_119)) ? 0.000000e+00f : (((j_inner_s_39 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_120 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_39 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_121 + ((cse_var_120 * width) * 4)) + j_inner_s_39)]));
      }
      for (int32_t j_inner_s_40 = 0; j_inner_s_40 < 128; ++j_inner_s_40) {
        int32_t cse_var_124 = (j_outer_3 * 128);
        int32_t cse_var_123 = ((i_outer_2 * 128) + 40);
        int32_t cse_var_122 = (cse_var_124 + j_inner_s_40);
        ((float*)outputData_1)[((cse_var_123 * stride_4) + (cse_var_122 * stride_3))] = (((cse_var_122 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_122)) ? 0.000000e+00f : (((j_inner_s_40 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_123 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_40 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_124 + ((cse_var_123 * width) * 4)) + j_inner_s_40)]));
      }
      for (int32_t j_inner_s_41 = 0; j_inner_s_41 < 128; ++j_inner_s_41) {
        int32_t cse_var_127 = (j_outer_3 * 128);
        int32_t cse_var_126 = ((i_outer_2 * 128) + 41);
        int32_t cse_var_125 = (cse_var_127 + j_inner_s_41);
        ((float*)outputData_1)[((cse_var_126 * stride_4) + (cse_var_125 * stride_3))] = (((cse_var_125 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_125)) ? 0.000000e+00f : (((j_inner_s_41 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_126 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_41 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_127 + ((cse_var_126 * width) * 4)) + j_inner_s_41)]));
      }
      for (int32_t j_inner_s_42 = 0; j_inner_s_42 < 128; ++j_inner_s_42) {
        int32_t cse_var_130 = (j_outer_3 * 128);
        int32_t cse_var_129 = ((i_outer_2 * 128) + 42);
        int32_t cse_var_128 = (cse_var_130 + j_inner_s_42);
        ((float*)outputData_1)[((cse_var_129 * stride_4) + (cse_var_128 * stride_3))] = (((cse_var_128 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_128)) ? 0.000000e+00f : (((j_inner_s_42 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_129 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_42 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_130 + ((cse_var_129 * width) * 4)) + j_inner_s_42)]));
      }
      for (int32_t j_inner_s_43 = 0; j_inner_s_43 < 128; ++j_inner_s_43) {
        int32_t cse_var_133 = (j_outer_3 * 128);
        int32_t cse_var_132 = ((i_outer_2 * 128) + 43);
        int32_t cse_var_131 = (cse_var_133 + j_inner_s_43);
        ((float*)outputData_1)[((cse_var_132 * stride_4) + (cse_var_131 * stride_3))] = (((cse_var_131 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_131)) ? 0.000000e+00f : (((j_inner_s_43 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_132 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_43 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_133 + ((cse_var_132 * width) * 4)) + j_inner_s_43)]));
      }
      for (int32_t j_inner_s_44 = 0; j_inner_s_44 < 128; ++j_inner_s_44) {
        int32_t cse_var_136 = (j_outer_3 * 128);
        int32_t cse_var_135 = ((i_outer_2 * 128) + 44);
        int32_t cse_var_134 = (cse_var_136 + j_inner_s_44);
        ((float*)outputData_1)[((cse_var_135 * stride_4) + (cse_var_134 * stride_3))] = (((cse_var_134 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_134)) ? 0.000000e+00f : (((j_inner_s_44 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_135 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_44 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_136 + ((cse_var_135 * width) * 4)) + j_inner_s_44)]));
      }
      for (int32_t j_inner_s_45 = 0; j_inner_s_45 < 128; ++j_inner_s_45) {
        int32_t cse_var_139 = (j_outer_3 * 128);
        int32_t cse_var_138 = ((i_outer_2 * 128) + 45);
        int32_t cse_var_137 = (cse_var_139 + j_inner_s_45);
        ((float*)outputData_1)[((cse_var_138 * stride_4) + (cse_var_137 * stride_3))] = (((cse_var_137 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_137)) ? 0.000000e+00f : (((j_inner_s_45 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_138 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_45 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_139 + ((cse_var_138 * width) * 4)) + j_inner_s_45)]));
      }
      for (int32_t j_inner_s_46 = 0; j_inner_s_46 < 128; ++j_inner_s_46) {
        int32_t cse_var_142 = (j_outer_3 * 128);
        int32_t cse_var_141 = ((i_outer_2 * 128) + 46);
        int32_t cse_var_140 = (cse_var_142 + j_inner_s_46);
        ((float*)outputData_1)[((cse_var_141 * stride_4) + (cse_var_140 * stride_3))] = (((cse_var_140 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_140)) ? 0.000000e+00f : (((j_inner_s_46 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_141 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_46 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_142 + ((cse_var_141 * width) * 4)) + j_inner_s_46)]));
      }
      for (int32_t j_inner_s_47 = 0; j_inner_s_47 < 128; ++j_inner_s_47) {
        int32_t cse_var_145 = (j_outer_3 * 128);
        int32_t cse_var_144 = ((i_outer_2 * 128) + 47);
        int32_t cse_var_143 = (cse_var_145 + j_inner_s_47);
        ((float*)outputData_1)[((cse_var_144 * stride_4) + (cse_var_143 * stride_3))] = (((cse_var_143 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_143)) ? 0.000000e+00f : (((j_inner_s_47 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_144 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_47 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_145 + ((cse_var_144 * width) * 4)) + j_inner_s_47)]));
      }
      for (int32_t j_inner_s_48 = 0; j_inner_s_48 < 128; ++j_inner_s_48) {
        int32_t cse_var_148 = (j_outer_3 * 128);
        int32_t cse_var_147 = ((i_outer_2 * 128) + 48);
        int32_t cse_var_146 = (cse_var_148 + j_inner_s_48);
        ((float*)outputData_1)[((cse_var_147 * stride_4) + (cse_var_146 * stride_3))] = (((cse_var_146 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_146)) ? 0.000000e+00f : (((j_inner_s_48 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_147 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_48 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_148 + ((cse_var_147 * width) * 4)) + j_inner_s_48)]));
      }
      for (int32_t j_inner_s_49 = 0; j_inner_s_49 < 128; ++j_inner_s_49) {
        int32_t cse_var_151 = (j_outer_3 * 128);
        int32_t cse_var_150 = ((i_outer_2 * 128) + 49);
        int32_t cse_var_149 = (cse_var_151 + j_inner_s_49);
        ((float*)outputData_1)[((cse_var_150 * stride_4) + (cse_var_149 * stride_3))] = (((cse_var_149 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_149)) ? 0.000000e+00f : (((j_inner_s_49 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_150 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_49 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_151 + ((cse_var_150 * width) * 4)) + j_inner_s_49)]));
      }
      for (int32_t j_inner_s_50 = 0; j_inner_s_50 < 128; ++j_inner_s_50) {
        int32_t cse_var_154 = (j_outer_3 * 128);
        int32_t cse_var_153 = ((i_outer_2 * 128) + 50);
        int32_t cse_var_152 = (cse_var_154 + j_inner_s_50);
        ((float*)outputData_1)[((cse_var_153 * stride_4) + (cse_var_152 * stride_3))] = (((cse_var_152 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_152)) ? 0.000000e+00f : (((j_inner_s_50 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_153 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_50 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_154 + ((cse_var_153 * width) * 4)) + j_inner_s_50)]));
      }
      for (int32_t j_inner_s_51 = 0; j_inner_s_51 < 128; ++j_inner_s_51) {
        int32_t cse_var_157 = (j_outer_3 * 128);
        int32_t cse_var_156 = ((i_outer_2 * 128) + 51);
        int32_t cse_var_155 = (cse_var_157 + j_inner_s_51);
        ((float*)outputData_1)[((cse_var_156 * stride_4) + (cse_var_155 * stride_3))] = (((cse_var_155 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_155)) ? 0.000000e+00f : (((j_inner_s_51 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_156 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_51 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_157 + ((cse_var_156 * width) * 4)) + j_inner_s_51)]));
      }
      for (int32_t j_inner_s_52 = 0; j_inner_s_52 < 128; ++j_inner_s_52) {
        int32_t cse_var_160 = (j_outer_3 * 128);
        int32_t cse_var_159 = ((i_outer_2 * 128) + 52);
        int32_t cse_var_158 = (cse_var_160 + j_inner_s_52);
        ((float*)outputData_1)[((cse_var_159 * stride_4) + (cse_var_158 * stride_3))] = (((cse_var_158 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_158)) ? 0.000000e+00f : (((j_inner_s_52 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_159 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_52 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_160 + ((cse_var_159 * width) * 4)) + j_inner_s_52)]));
      }
      for (int32_t j_inner_s_53 = 0; j_inner_s_53 < 128; ++j_inner_s_53) {
        int32_t cse_var_163 = (j_outer_3 * 128);
        int32_t cse_var_162 = ((i_outer_2 * 128) + 53);
        int32_t cse_var_161 = (cse_var_163 + j_inner_s_53);
        ((float*)outputData_1)[((cse_var_162 * stride_4) + (cse_var_161 * stride_3))] = (((cse_var_161 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_161)) ? 0.000000e+00f : (((j_inner_s_53 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_162 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_53 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_163 + ((cse_var_162 * width) * 4)) + j_inner_s_53)]));
      }
      for (int32_t j_inner_s_54 = 0; j_inner_s_54 < 128; ++j_inner_s_54) {
        int32_t cse_var_166 = (j_outer_3 * 128);
        int32_t cse_var_165 = ((i_outer_2 * 128) + 54);
        int32_t cse_var_164 = (cse_var_166 + j_inner_s_54);
        ((float*)outputData_1)[((cse_var_165 * stride_4) + (cse_var_164 * stride_3))] = (((cse_var_164 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_164)) ? 0.000000e+00f : (((j_inner_s_54 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_165 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_54 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_166 + ((cse_var_165 * width) * 4)) + j_inner_s_54)]));
      }
      for (int32_t j_inner_s_55 = 0; j_inner_s_55 < 128; ++j_inner_s_55) {
        int32_t cse_var_169 = (j_outer_3 * 128);
        int32_t cse_var_168 = ((i_outer_2 * 128) + 55);
        int32_t cse_var_167 = (cse_var_169 + j_inner_s_55);
        ((float*)outputData_1)[((cse_var_168 * stride_4) + (cse_var_167 * stride_3))] = (((cse_var_167 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_167)) ? 0.000000e+00f : (((j_inner_s_55 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_168 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_55 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_169 + ((cse_var_168 * width) * 4)) + j_inner_s_55)]));
      }
      for (int32_t j_inner_s_56 = 0; j_inner_s_56 < 128; ++j_inner_s_56) {
        int32_t cse_var_172 = (j_outer_3 * 128);
        int32_t cse_var_171 = ((i_outer_2 * 128) + 56);
        int32_t cse_var_170 = (cse_var_172 + j_inner_s_56);
        ((float*)outputData_1)[((cse_var_171 * stride_4) + (cse_var_170 * stride_3))] = (((cse_var_170 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_170)) ? 0.000000e+00f : (((j_inner_s_56 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_171 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_56 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_172 + ((cse_var_171 * width) * 4)) + j_inner_s_56)]));
      }
      for (int32_t j_inner_s_57 = 0; j_inner_s_57 < 128; ++j_inner_s_57) {
        int32_t cse_var_175 = (j_outer_3 * 128);
        int32_t cse_var_174 = ((i_outer_2 * 128) + 57);
        int32_t cse_var_173 = (cse_var_175 + j_inner_s_57);
        ((float*)outputData_1)[((cse_var_174 * stride_4) + (cse_var_173 * stride_3))] = (((cse_var_173 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_173)) ? 0.000000e+00f : (((j_inner_s_57 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_174 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_57 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_175 + ((cse_var_174 * width) * 4)) + j_inner_s_57)]));
      }
      for (int32_t j_inner_s_58 = 0; j_inner_s_58 < 128; ++j_inner_s_58) {
        int32_t cse_var_178 = (j_outer_3 * 128);
        int32_t cse_var_177 = ((i_outer_2 * 128) + 58);
        int32_t cse_var_176 = (cse_var_178 + j_inner_s_58);
        ((float*)outputData_1)[((cse_var_177 * stride_4) + (cse_var_176 * stride_3))] = (((cse_var_176 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_176)) ? 0.000000e+00f : (((j_inner_s_58 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_177 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_58 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_178 + ((cse_var_177 * width) * 4)) + j_inner_s_58)]));
      }
      for (int32_t j_inner_s_59 = 0; j_inner_s_59 < 128; ++j_inner_s_59) {
        int32_t cse_var_181 = (j_outer_3 * 128);
        int32_t cse_var_180 = ((i_outer_2 * 128) + 59);
        int32_t cse_var_179 = (cse_var_181 + j_inner_s_59);
        ((float*)outputData_1)[((cse_var_180 * stride_4) + (cse_var_179 * stride_3))] = (((cse_var_179 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_179)) ? 0.000000e+00f : (((j_inner_s_59 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_180 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_59 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_181 + ((cse_var_180 * width) * 4)) + j_inner_s_59)]));
      }
      for (int32_t j_inner_s_60 = 0; j_inner_s_60 < 128; ++j_inner_s_60) {
        int32_t cse_var_184 = (j_outer_3 * 128);
        int32_t cse_var_183 = ((i_outer_2 * 128) + 60);
        int32_t cse_var_182 = (cse_var_184 + j_inner_s_60);
        ((float*)outputData_1)[((cse_var_183 * stride_4) + (cse_var_182 * stride_3))] = (((cse_var_182 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_182)) ? 0.000000e+00f : (((j_inner_s_60 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_183 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_60 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_184 + ((cse_var_183 * width) * 4)) + j_inner_s_60)]));
      }
      for (int32_t j_inner_s_61 = 0; j_inner_s_61 < 128; ++j_inner_s_61) {
        int32_t cse_var_187 = (j_outer_3 * 128);
        int32_t cse_var_186 = ((i_outer_2 * 128) + 61);
        int32_t cse_var_185 = (cse_var_187 + j_inner_s_61);
        ((float*)outputData_1)[((cse_var_186 * stride_4) + (cse_var_185 * stride_3))] = (((cse_var_185 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_185)) ? 0.000000e+00f : (((j_inner_s_61 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_186 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_61 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_187 + ((cse_var_186 * width) * 4)) + j_inner_s_61)]));
      }
      for (int32_t j_inner_s_62 = 0; j_inner_s_62 < 128; ++j_inner_s_62) {
        int32_t cse_var_190 = (j_outer_3 * 128);
        int32_t cse_var_189 = ((i_outer_2 * 128) + 62);
        int32_t cse_var_188 = (cse_var_190 + j_inner_s_62);
        ((float*)outputData_1)[((cse_var_189 * stride_4) + (cse_var_188 * stride_3))] = (((cse_var_188 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_188)) ? 0.000000e+00f : (((j_inner_s_62 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_189 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_62 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_190 + ((cse_var_189 * width) * 4)) + j_inner_s_62)]));
      }
      for (int32_t j_inner_s_63 = 0; j_inner_s_63 < 128; ++j_inner_s_63) {
        int32_t cse_var_193 = (j_outer_3 * 128);
        int32_t cse_var_192 = ((i_outer_2 * 128) + 63);
        int32_t cse_var_191 = (cse_var_193 + j_inner_s_63);
        ((float*)outputData_1)[((cse_var_192 * stride_4) + (cse_var_191 * stride_3))] = (((cse_var_191 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_191)) ? 0.000000e+00f : (((j_inner_s_63 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_192 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_63 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_193 + ((cse_var_192 * width) * 4)) + j_inner_s_63)]));
      }
      for (int32_t j_inner_s_64 = 0; j_inner_s_64 < 128; ++j_inner_s_64) {
        int32_t cse_var_196 = (j_outer_3 * 128);
        int32_t cse_var_195 = ((i_outer_2 * 128) + 64);
        int32_t cse_var_194 = (cse_var_196 + j_inner_s_64);
        ((float*)outputData_1)[((cse_var_195 * stride_4) + (cse_var_194 * stride_3))] = (((cse_var_194 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_194)) ? 0.000000e+00f : (((j_inner_s_64 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_195 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_64 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_196 + ((cse_var_195 * width) * 4)) + j_inner_s_64)]));
      }
      for (int32_t j_inner_s_65 = 0; j_inner_s_65 < 128; ++j_inner_s_65) {
        int32_t cse_var_199 = (j_outer_3 * 128);
        int32_t cse_var_198 = ((i_outer_2 * 128) + 65);
        int32_t cse_var_197 = (cse_var_199 + j_inner_s_65);
        ((float*)outputData_1)[((cse_var_198 * stride_4) + (cse_var_197 * stride_3))] = (((cse_var_197 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_197)) ? 0.000000e+00f : (((j_inner_s_65 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_198 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_65 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_199 + ((cse_var_198 * width) * 4)) + j_inner_s_65)]));
      }
      for (int32_t j_inner_s_66 = 0; j_inner_s_66 < 128; ++j_inner_s_66) {
        int32_t cse_var_202 = (j_outer_3 * 128);
        int32_t cse_var_201 = ((i_outer_2 * 128) + 66);
        int32_t cse_var_200 = (cse_var_202 + j_inner_s_66);
        ((float*)outputData_1)[((cse_var_201 * stride_4) + (cse_var_200 * stride_3))] = (((cse_var_200 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_200)) ? 0.000000e+00f : (((j_inner_s_66 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_201 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_66 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_202 + ((cse_var_201 * width) * 4)) + j_inner_s_66)]));
      }
      for (int32_t j_inner_s_67 = 0; j_inner_s_67 < 128; ++j_inner_s_67) {
        int32_t cse_var_205 = (j_outer_3 * 128);
        int32_t cse_var_204 = ((i_outer_2 * 128) + 67);
        int32_t cse_var_203 = (cse_var_205 + j_inner_s_67);
        ((float*)outputData_1)[((cse_var_204 * stride_4) + (cse_var_203 * stride_3))] = (((cse_var_203 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_203)) ? 0.000000e+00f : (((j_inner_s_67 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_204 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_67 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_205 + ((cse_var_204 * width) * 4)) + j_inner_s_67)]));
      }
      for (int32_t j_inner_s_68 = 0; j_inner_s_68 < 128; ++j_inner_s_68) {
        int32_t cse_var_208 = (j_outer_3 * 128);
        int32_t cse_var_207 = ((i_outer_2 * 128) + 68);
        int32_t cse_var_206 = (cse_var_208 + j_inner_s_68);
        ((float*)outputData_1)[((cse_var_207 * stride_4) + (cse_var_206 * stride_3))] = (((cse_var_206 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_206)) ? 0.000000e+00f : (((j_inner_s_68 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_207 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_68 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_208 + ((cse_var_207 * width) * 4)) + j_inner_s_68)]));
      }
      for (int32_t j_inner_s_69 = 0; j_inner_s_69 < 128; ++j_inner_s_69) {
        int32_t cse_var_211 = (j_outer_3 * 128);
        int32_t cse_var_210 = ((i_outer_2 * 128) + 69);
        int32_t cse_var_209 = (cse_var_211 + j_inner_s_69);
        ((float*)outputData_1)[((cse_var_210 * stride_4) + (cse_var_209 * stride_3))] = (((cse_var_209 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_209)) ? 0.000000e+00f : (((j_inner_s_69 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_210 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_69 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_211 + ((cse_var_210 * width) * 4)) + j_inner_s_69)]));
      }
      for (int32_t j_inner_s_70 = 0; j_inner_s_70 < 128; ++j_inner_s_70) {
        int32_t cse_var_214 = (j_outer_3 * 128);
        int32_t cse_var_213 = ((i_outer_2 * 128) + 70);
        int32_t cse_var_212 = (cse_var_214 + j_inner_s_70);
        ((float*)outputData_1)[((cse_var_213 * stride_4) + (cse_var_212 * stride_3))] = (((cse_var_212 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_212)) ? 0.000000e+00f : (((j_inner_s_70 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_213 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_70 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_214 + ((cse_var_213 * width) * 4)) + j_inner_s_70)]));
      }
      for (int32_t j_inner_s_71 = 0; j_inner_s_71 < 128; ++j_inner_s_71) {
        int32_t cse_var_217 = (j_outer_3 * 128);
        int32_t cse_var_216 = ((i_outer_2 * 128) + 71);
        int32_t cse_var_215 = (cse_var_217 + j_inner_s_71);
        ((float*)outputData_1)[((cse_var_216 * stride_4) + (cse_var_215 * stride_3))] = (((cse_var_215 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_215)) ? 0.000000e+00f : (((j_inner_s_71 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_216 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_71 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_217 + ((cse_var_216 * width) * 4)) + j_inner_s_71)]));
      }
      for (int32_t j_inner_s_72 = 0; j_inner_s_72 < 128; ++j_inner_s_72) {
        int32_t cse_var_220 = (j_outer_3 * 128);
        int32_t cse_var_219 = ((i_outer_2 * 128) + 72);
        int32_t cse_var_218 = (cse_var_220 + j_inner_s_72);
        ((float*)outputData_1)[((cse_var_219 * stride_4) + (cse_var_218 * stride_3))] = (((cse_var_218 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_218)) ? 0.000000e+00f : (((j_inner_s_72 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_219 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_72 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_220 + ((cse_var_219 * width) * 4)) + j_inner_s_72)]));
      }
      for (int32_t j_inner_s_73 = 0; j_inner_s_73 < 128; ++j_inner_s_73) {
        int32_t cse_var_223 = (j_outer_3 * 128);
        int32_t cse_var_222 = ((i_outer_2 * 128) + 73);
        int32_t cse_var_221 = (cse_var_223 + j_inner_s_73);
        ((float*)outputData_1)[((cse_var_222 * stride_4) + (cse_var_221 * stride_3))] = (((cse_var_221 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_221)) ? 0.000000e+00f : (((j_inner_s_73 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_222 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_73 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_223 + ((cse_var_222 * width) * 4)) + j_inner_s_73)]));
      }
      for (int32_t j_inner_s_74 = 0; j_inner_s_74 < 128; ++j_inner_s_74) {
        int32_t cse_var_226 = (j_outer_3 * 128);
        int32_t cse_var_225 = ((i_outer_2 * 128) + 74);
        int32_t cse_var_224 = (cse_var_226 + j_inner_s_74);
        ((float*)outputData_1)[((cse_var_225 * stride_4) + (cse_var_224 * stride_3))] = (((cse_var_224 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_224)) ? 0.000000e+00f : (((j_inner_s_74 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_225 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_74 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_226 + ((cse_var_225 * width) * 4)) + j_inner_s_74)]));
      }
      for (int32_t j_inner_s_75 = 0; j_inner_s_75 < 128; ++j_inner_s_75) {
        int32_t cse_var_229 = (j_outer_3 * 128);
        int32_t cse_var_228 = ((i_outer_2 * 128) + 75);
        int32_t cse_var_227 = (cse_var_229 + j_inner_s_75);
        ((float*)outputData_1)[((cse_var_228 * stride_4) + (cse_var_227 * stride_3))] = (((cse_var_227 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_227)) ? 0.000000e+00f : (((j_inner_s_75 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_228 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_75 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_229 + ((cse_var_228 * width) * 4)) + j_inner_s_75)]));
      }
      for (int32_t j_inner_s_76 = 0; j_inner_s_76 < 128; ++j_inner_s_76) {
        int32_t cse_var_232 = (j_outer_3 * 128);
        int32_t cse_var_231 = ((i_outer_2 * 128) + 76);
        int32_t cse_var_230 = (cse_var_232 + j_inner_s_76);
        ((float*)outputData_1)[((cse_var_231 * stride_4) + (cse_var_230 * stride_3))] = (((cse_var_230 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_230)) ? 0.000000e+00f : (((j_inner_s_76 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_231 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_76 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_232 + ((cse_var_231 * width) * 4)) + j_inner_s_76)]));
      }
      for (int32_t j_inner_s_77 = 0; j_inner_s_77 < 128; ++j_inner_s_77) {
        int32_t cse_var_235 = (j_outer_3 * 128);
        int32_t cse_var_234 = ((i_outer_2 * 128) + 77);
        int32_t cse_var_233 = (cse_var_235 + j_inner_s_77);
        ((float*)outputData_1)[((cse_var_234 * stride_4) + (cse_var_233 * stride_3))] = (((cse_var_233 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_233)) ? 0.000000e+00f : (((j_inner_s_77 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_234 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_77 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_235 + ((cse_var_234 * width) * 4)) + j_inner_s_77)]));
      }
      for (int32_t j_inner_s_78 = 0; j_inner_s_78 < 128; ++j_inner_s_78) {
        int32_t cse_var_238 = (j_outer_3 * 128);
        int32_t cse_var_237 = ((i_outer_2 * 128) + 78);
        int32_t cse_var_236 = (cse_var_238 + j_inner_s_78);
        ((float*)outputData_1)[((cse_var_237 * stride_4) + (cse_var_236 * stride_3))] = (((cse_var_236 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_236)) ? 0.000000e+00f : (((j_inner_s_78 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_237 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_78 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_238 + ((cse_var_237 * width) * 4)) + j_inner_s_78)]));
      }
      for (int32_t j_inner_s_79 = 0; j_inner_s_79 < 128; ++j_inner_s_79) {
        int32_t cse_var_241 = (j_outer_3 * 128);
        int32_t cse_var_240 = ((i_outer_2 * 128) + 79);
        int32_t cse_var_239 = (cse_var_241 + j_inner_s_79);
        ((float*)outputData_1)[((cse_var_240 * stride_4) + (cse_var_239 * stride_3))] = (((cse_var_239 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_239)) ? 0.000000e+00f : (((j_inner_s_79 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_240 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_79 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_241 + ((cse_var_240 * width) * 4)) + j_inner_s_79)]));
      }
      for (int32_t j_inner_s_80 = 0; j_inner_s_80 < 128; ++j_inner_s_80) {
        int32_t cse_var_244 = (j_outer_3 * 128);
        int32_t cse_var_243 = ((i_outer_2 * 128) + 80);
        int32_t cse_var_242 = (cse_var_244 + j_inner_s_80);
        ((float*)outputData_1)[((cse_var_243 * stride_4) + (cse_var_242 * stride_3))] = (((cse_var_242 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_242)) ? 0.000000e+00f : (((j_inner_s_80 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_243 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_80 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_244 + ((cse_var_243 * width) * 4)) + j_inner_s_80)]));
      }
      for (int32_t j_inner_s_81 = 0; j_inner_s_81 < 128; ++j_inner_s_81) {
        int32_t cse_var_247 = (j_outer_3 * 128);
        int32_t cse_var_246 = ((i_outer_2 * 128) + 81);
        int32_t cse_var_245 = (cse_var_247 + j_inner_s_81);
        ((float*)outputData_1)[((cse_var_246 * stride_4) + (cse_var_245 * stride_3))] = (((cse_var_245 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_245)) ? 0.000000e+00f : (((j_inner_s_81 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_246 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_81 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_247 + ((cse_var_246 * width) * 4)) + j_inner_s_81)]));
      }
      for (int32_t j_inner_s_82 = 0; j_inner_s_82 < 128; ++j_inner_s_82) {
        int32_t cse_var_250 = (j_outer_3 * 128);
        int32_t cse_var_249 = ((i_outer_2 * 128) + 82);
        int32_t cse_var_248 = (cse_var_250 + j_inner_s_82);
        ((float*)outputData_1)[((cse_var_249 * stride_4) + (cse_var_248 * stride_3))] = (((cse_var_248 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_248)) ? 0.000000e+00f : (((j_inner_s_82 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_249 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_82 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_250 + ((cse_var_249 * width) * 4)) + j_inner_s_82)]));
      }
      for (int32_t j_inner_s_83 = 0; j_inner_s_83 < 128; ++j_inner_s_83) {
        int32_t cse_var_253 = (j_outer_3 * 128);
        int32_t cse_var_252 = ((i_outer_2 * 128) + 83);
        int32_t cse_var_251 = (cse_var_253 + j_inner_s_83);
        ((float*)outputData_1)[((cse_var_252 * stride_4) + (cse_var_251 * stride_3))] = (((cse_var_251 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_251)) ? 0.000000e+00f : (((j_inner_s_83 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_252 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_83 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_253 + ((cse_var_252 * width) * 4)) + j_inner_s_83)]));
      }
      for (int32_t j_inner_s_84 = 0; j_inner_s_84 < 128; ++j_inner_s_84) {
        int32_t cse_var_256 = (j_outer_3 * 128);
        int32_t cse_var_255 = ((i_outer_2 * 128) + 84);
        int32_t cse_var_254 = (cse_var_256 + j_inner_s_84);
        ((float*)outputData_1)[((cse_var_255 * stride_4) + (cse_var_254 * stride_3))] = (((cse_var_254 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_254)) ? 0.000000e+00f : (((j_inner_s_84 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_255 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_84 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_256 + ((cse_var_255 * width) * 4)) + j_inner_s_84)]));
      }
      for (int32_t j_inner_s_85 = 0; j_inner_s_85 < 128; ++j_inner_s_85) {
        int32_t cse_var_259 = (j_outer_3 * 128);
        int32_t cse_var_258 = ((i_outer_2 * 128) + 85);
        int32_t cse_var_257 = (cse_var_259 + j_inner_s_85);
        ((float*)outputData_1)[((cse_var_258 * stride_4) + (cse_var_257 * stride_3))] = (((cse_var_257 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_257)) ? 0.000000e+00f : (((j_inner_s_85 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_258 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_85 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_259 + ((cse_var_258 * width) * 4)) + j_inner_s_85)]));
      }
      for (int32_t j_inner_s_86 = 0; j_inner_s_86 < 128; ++j_inner_s_86) {
        int32_t cse_var_262 = (j_outer_3 * 128);
        int32_t cse_var_261 = ((i_outer_2 * 128) + 86);
        int32_t cse_var_260 = (cse_var_262 + j_inner_s_86);
        ((float*)outputData_1)[((cse_var_261 * stride_4) + (cse_var_260 * stride_3))] = (((cse_var_260 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_260)) ? 0.000000e+00f : (((j_inner_s_86 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_261 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_86 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_262 + ((cse_var_261 * width) * 4)) + j_inner_s_86)]));
      }
      for (int32_t j_inner_s_87 = 0; j_inner_s_87 < 128; ++j_inner_s_87) {
        int32_t cse_var_265 = (j_outer_3 * 128);
        int32_t cse_var_264 = ((i_outer_2 * 128) + 87);
        int32_t cse_var_263 = (cse_var_265 + j_inner_s_87);
        ((float*)outputData_1)[((cse_var_264 * stride_4) + (cse_var_263 * stride_3))] = (((cse_var_263 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_263)) ? 0.000000e+00f : (((j_inner_s_87 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_264 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_87 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_265 + ((cse_var_264 * width) * 4)) + j_inner_s_87)]));
      }
      for (int32_t j_inner_s_88 = 0; j_inner_s_88 < 128; ++j_inner_s_88) {
        int32_t cse_var_268 = (j_outer_3 * 128);
        int32_t cse_var_267 = ((i_outer_2 * 128) + 88);
        int32_t cse_var_266 = (cse_var_268 + j_inner_s_88);
        ((float*)outputData_1)[((cse_var_267 * stride_4) + (cse_var_266 * stride_3))] = (((cse_var_266 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_266)) ? 0.000000e+00f : (((j_inner_s_88 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_267 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_88 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_268 + ((cse_var_267 * width) * 4)) + j_inner_s_88)]));
      }
      for (int32_t j_inner_s_89 = 0; j_inner_s_89 < 128; ++j_inner_s_89) {
        int32_t cse_var_271 = (j_outer_3 * 128);
        int32_t cse_var_270 = ((i_outer_2 * 128) + 89);
        int32_t cse_var_269 = (cse_var_271 + j_inner_s_89);
        ((float*)outputData_1)[((cse_var_270 * stride_4) + (cse_var_269 * stride_3))] = (((cse_var_269 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_269)) ? 0.000000e+00f : (((j_inner_s_89 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_270 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_89 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_271 + ((cse_var_270 * width) * 4)) + j_inner_s_89)]));
      }
      for (int32_t j_inner_s_90 = 0; j_inner_s_90 < 128; ++j_inner_s_90) {
        int32_t cse_var_274 = (j_outer_3 * 128);
        int32_t cse_var_273 = ((i_outer_2 * 128) + 90);
        int32_t cse_var_272 = (cse_var_274 + j_inner_s_90);
        ((float*)outputData_1)[((cse_var_273 * stride_4) + (cse_var_272 * stride_3))] = (((cse_var_272 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_272)) ? 0.000000e+00f : (((j_inner_s_90 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_273 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_90 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_274 + ((cse_var_273 * width) * 4)) + j_inner_s_90)]));
      }
      for (int32_t j_inner_s_91 = 0; j_inner_s_91 < 128; ++j_inner_s_91) {
        int32_t cse_var_277 = (j_outer_3 * 128);
        int32_t cse_var_276 = ((i_outer_2 * 128) + 91);
        int32_t cse_var_275 = (cse_var_277 + j_inner_s_91);
        ((float*)outputData_1)[((cse_var_276 * stride_4) + (cse_var_275 * stride_3))] = (((cse_var_275 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_275)) ? 0.000000e+00f : (((j_inner_s_91 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_276 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_91 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_277 + ((cse_var_276 * width) * 4)) + j_inner_s_91)]));
      }
      for (int32_t j_inner_s_92 = 0; j_inner_s_92 < 128; ++j_inner_s_92) {
        int32_t cse_var_280 = (j_outer_3 * 128);
        int32_t cse_var_279 = ((i_outer_2 * 128) + 92);
        int32_t cse_var_278 = (cse_var_280 + j_inner_s_92);
        ((float*)outputData_1)[((cse_var_279 * stride_4) + (cse_var_278 * stride_3))] = (((cse_var_278 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_278)) ? 0.000000e+00f : (((j_inner_s_92 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_279 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_92 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_280 + ((cse_var_279 * width) * 4)) + j_inner_s_92)]));
      }
      for (int32_t j_inner_s_93 = 0; j_inner_s_93 < 128; ++j_inner_s_93) {
        int32_t cse_var_283 = (j_outer_3 * 128);
        int32_t cse_var_282 = ((i_outer_2 * 128) + 93);
        int32_t cse_var_281 = (cse_var_283 + j_inner_s_93);
        ((float*)outputData_1)[((cse_var_282 * stride_4) + (cse_var_281 * stride_3))] = (((cse_var_281 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_281)) ? 0.000000e+00f : (((j_inner_s_93 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_282 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_93 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_283 + ((cse_var_282 * width) * 4)) + j_inner_s_93)]));
      }
      for (int32_t j_inner_s_94 = 0; j_inner_s_94 < 128; ++j_inner_s_94) {
        int32_t cse_var_286 = (j_outer_3 * 128);
        int32_t cse_var_285 = ((i_outer_2 * 128) + 94);
        int32_t cse_var_284 = (cse_var_286 + j_inner_s_94);
        ((float*)outputData_1)[((cse_var_285 * stride_4) + (cse_var_284 * stride_3))] = (((cse_var_284 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_284)) ? 0.000000e+00f : (((j_inner_s_94 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_285 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_94 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_286 + ((cse_var_285 * width) * 4)) + j_inner_s_94)]));
      }
      for (int32_t j_inner_s_95 = 0; j_inner_s_95 < 128; ++j_inner_s_95) {
        int32_t cse_var_289 = (j_outer_3 * 128);
        int32_t cse_var_288 = ((i_outer_2 * 128) + 95);
        int32_t cse_var_287 = (cse_var_289 + j_inner_s_95);
        ((float*)outputData_1)[((cse_var_288 * stride_4) + (cse_var_287 * stride_3))] = (((cse_var_287 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_287)) ? 0.000000e+00f : (((j_inner_s_95 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_288 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_95 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_289 + ((cse_var_288 * width) * 4)) + j_inner_s_95)]));
      }
      for (int32_t j_inner_s_96 = 0; j_inner_s_96 < 128; ++j_inner_s_96) {
        int32_t cse_var_292 = (j_outer_3 * 128);
        int32_t cse_var_291 = ((i_outer_2 * 128) + 96);
        int32_t cse_var_290 = (cse_var_292 + j_inner_s_96);
        ((float*)outputData_1)[((cse_var_291 * stride_4) + (cse_var_290 * stride_3))] = (((cse_var_290 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_290)) ? 0.000000e+00f : (((j_inner_s_96 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_291 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_96 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_292 + ((cse_var_291 * width) * 4)) + j_inner_s_96)]));
      }
      for (int32_t j_inner_s_97 = 0; j_inner_s_97 < 128; ++j_inner_s_97) {
        int32_t cse_var_295 = (j_outer_3 * 128);
        int32_t cse_var_294 = ((i_outer_2 * 128) + 97);
        int32_t cse_var_293 = (cse_var_295 + j_inner_s_97);
        ((float*)outputData_1)[((cse_var_294 * stride_4) + (cse_var_293 * stride_3))] = (((cse_var_293 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_293)) ? 0.000000e+00f : (((j_inner_s_97 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_294 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_97 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_295 + ((cse_var_294 * width) * 4)) + j_inner_s_97)]));
      }
      for (int32_t j_inner_s_98 = 0; j_inner_s_98 < 128; ++j_inner_s_98) {
        int32_t cse_var_298 = (j_outer_3 * 128);
        int32_t cse_var_297 = ((i_outer_2 * 128) + 98);
        int32_t cse_var_296 = (cse_var_298 + j_inner_s_98);
        ((float*)outputData_1)[((cse_var_297 * stride_4) + (cse_var_296 * stride_3))] = (((cse_var_296 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_296)) ? 0.000000e+00f : (((j_inner_s_98 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_297 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_98 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_298 + ((cse_var_297 * width) * 4)) + j_inner_s_98)]));
      }
      for (int32_t j_inner_s_99 = 0; j_inner_s_99 < 128; ++j_inner_s_99) {
        int32_t cse_var_301 = (j_outer_3 * 128);
        int32_t cse_var_300 = ((i_outer_2 * 128) + 99);
        int32_t cse_var_299 = (cse_var_301 + j_inner_s_99);
        ((float*)outputData_1)[((cse_var_300 * stride_4) + (cse_var_299 * stride_3))] = (((cse_var_299 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_299)) ? 0.000000e+00f : (((j_inner_s_99 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_300 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_99 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_301 + ((cse_var_300 * width) * 4)) + j_inner_s_99)]));
      }
      for (int32_t j_inner_s_100 = 0; j_inner_s_100 < 128; ++j_inner_s_100) {
        int32_t cse_var_304 = (j_outer_3 * 128);
        int32_t cse_var_303 = ((i_outer_2 * 128) + 100);
        int32_t cse_var_302 = (cse_var_304 + j_inner_s_100);
        ((float*)outputData_1)[((cse_var_303 * stride_4) + (cse_var_302 * stride_3))] = (((cse_var_302 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_302)) ? 0.000000e+00f : (((j_inner_s_100 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_303 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_100 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_304 + ((cse_var_303 * width) * 4)) + j_inner_s_100)]));
      }
      for (int32_t j_inner_s_101 = 0; j_inner_s_101 < 128; ++j_inner_s_101) {
        int32_t cse_var_307 = (j_outer_3 * 128);
        int32_t cse_var_306 = ((i_outer_2 * 128) + 101);
        int32_t cse_var_305 = (cse_var_307 + j_inner_s_101);
        ((float*)outputData_1)[((cse_var_306 * stride_4) + (cse_var_305 * stride_3))] = (((cse_var_305 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_305)) ? 0.000000e+00f : (((j_inner_s_101 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_306 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_101 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_307 + ((cse_var_306 * width) * 4)) + j_inner_s_101)]));
      }
      for (int32_t j_inner_s_102 = 0; j_inner_s_102 < 128; ++j_inner_s_102) {
        int32_t cse_var_310 = (j_outer_3 * 128);
        int32_t cse_var_309 = ((i_outer_2 * 128) + 102);
        int32_t cse_var_308 = (cse_var_310 + j_inner_s_102);
        ((float*)outputData_1)[((cse_var_309 * stride_4) + (cse_var_308 * stride_3))] = (((cse_var_308 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_308)) ? 0.000000e+00f : (((j_inner_s_102 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_309 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_102 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_310 + ((cse_var_309 * width) * 4)) + j_inner_s_102)]));
      }
      for (int32_t j_inner_s_103 = 0; j_inner_s_103 < 128; ++j_inner_s_103) {
        int32_t cse_var_313 = (j_outer_3 * 128);
        int32_t cse_var_312 = ((i_outer_2 * 128) + 103);
        int32_t cse_var_311 = (cse_var_313 + j_inner_s_103);
        ((float*)outputData_1)[((cse_var_312 * stride_4) + (cse_var_311 * stride_3))] = (((cse_var_311 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_311)) ? 0.000000e+00f : (((j_inner_s_103 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_312 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_103 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_313 + ((cse_var_312 * width) * 4)) + j_inner_s_103)]));
      }
      for (int32_t j_inner_s_104 = 0; j_inner_s_104 < 128; ++j_inner_s_104) {
        int32_t cse_var_316 = (j_outer_3 * 128);
        int32_t cse_var_315 = ((i_outer_2 * 128) + 104);
        int32_t cse_var_314 = (cse_var_316 + j_inner_s_104);
        ((float*)outputData_1)[((cse_var_315 * stride_4) + (cse_var_314 * stride_3))] = (((cse_var_314 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_314)) ? 0.000000e+00f : (((j_inner_s_104 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_315 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_104 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_316 + ((cse_var_315 * width) * 4)) + j_inner_s_104)]));
      }
      for (int32_t j_inner_s_105 = 0; j_inner_s_105 < 128; ++j_inner_s_105) {
        int32_t cse_var_319 = (j_outer_3 * 128);
        int32_t cse_var_318 = ((i_outer_2 * 128) + 105);
        int32_t cse_var_317 = (cse_var_319 + j_inner_s_105);
        ((float*)outputData_1)[((cse_var_318 * stride_4) + (cse_var_317 * stride_3))] = (((cse_var_317 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_317)) ? 0.000000e+00f : (((j_inner_s_105 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_318 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_105 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_319 + ((cse_var_318 * width) * 4)) + j_inner_s_105)]));
      }
      for (int32_t j_inner_s_106 = 0; j_inner_s_106 < 128; ++j_inner_s_106) {
        int32_t cse_var_322 = (j_outer_3 * 128);
        int32_t cse_var_321 = ((i_outer_2 * 128) + 106);
        int32_t cse_var_320 = (cse_var_322 + j_inner_s_106);
        ((float*)outputData_1)[((cse_var_321 * stride_4) + (cse_var_320 * stride_3))] = (((cse_var_320 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_320)) ? 0.000000e+00f : (((j_inner_s_106 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_321 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_106 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_322 + ((cse_var_321 * width) * 4)) + j_inner_s_106)]));
      }
      for (int32_t j_inner_s_107 = 0; j_inner_s_107 < 128; ++j_inner_s_107) {
        int32_t cse_var_325 = (j_outer_3 * 128);
        int32_t cse_var_324 = ((i_outer_2 * 128) + 107);
        int32_t cse_var_323 = (cse_var_325 + j_inner_s_107);
        ((float*)outputData_1)[((cse_var_324 * stride_4) + (cse_var_323 * stride_3))] = (((cse_var_323 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_323)) ? 0.000000e+00f : (((j_inner_s_107 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_324 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_107 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_325 + ((cse_var_324 * width) * 4)) + j_inner_s_107)]));
      }
      for (int32_t j_inner_s_108 = 0; j_inner_s_108 < 128; ++j_inner_s_108) {
        int32_t cse_var_328 = (j_outer_3 * 128);
        int32_t cse_var_327 = ((i_outer_2 * 128) + 108);
        int32_t cse_var_326 = (cse_var_328 + j_inner_s_108);
        ((float*)outputData_1)[((cse_var_327 * stride_4) + (cse_var_326 * stride_3))] = (((cse_var_326 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_326)) ? 0.000000e+00f : (((j_inner_s_108 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_327 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_108 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_328 + ((cse_var_327 * width) * 4)) + j_inner_s_108)]));
      }
      for (int32_t j_inner_s_109 = 0; j_inner_s_109 < 128; ++j_inner_s_109) {
        int32_t cse_var_331 = (j_outer_3 * 128);
        int32_t cse_var_330 = ((i_outer_2 * 128) + 109);
        int32_t cse_var_329 = (cse_var_331 + j_inner_s_109);
        ((float*)outputData_1)[((cse_var_330 * stride_4) + (cse_var_329 * stride_3))] = (((cse_var_329 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_329)) ? 0.000000e+00f : (((j_inner_s_109 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_330 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_109 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_331 + ((cse_var_330 * width) * 4)) + j_inner_s_109)]));
      }
      for (int32_t j_inner_s_110 = 0; j_inner_s_110 < 128; ++j_inner_s_110) {
        int32_t cse_var_334 = (j_outer_3 * 128);
        int32_t cse_var_333 = ((i_outer_2 * 128) + 110);
        int32_t cse_var_332 = (cse_var_334 + j_inner_s_110);
        ((float*)outputData_1)[((cse_var_333 * stride_4) + (cse_var_332 * stride_3))] = (((cse_var_332 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_332)) ? 0.000000e+00f : (((j_inner_s_110 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_333 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_110 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_334 + ((cse_var_333 * width) * 4)) + j_inner_s_110)]));
      }
      for (int32_t j_inner_s_111 = 0; j_inner_s_111 < 128; ++j_inner_s_111) {
        int32_t cse_var_337 = (j_outer_3 * 128);
        int32_t cse_var_336 = ((i_outer_2 * 128) + 111);
        int32_t cse_var_335 = (cse_var_337 + j_inner_s_111);
        ((float*)outputData_1)[((cse_var_336 * stride_4) + (cse_var_335 * stride_3))] = (((cse_var_335 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_335)) ? 0.000000e+00f : (((j_inner_s_111 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_336 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_111 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_337 + ((cse_var_336 * width) * 4)) + j_inner_s_111)]));
      }
      for (int32_t j_inner_s_112 = 0; j_inner_s_112 < 128; ++j_inner_s_112) {
        int32_t cse_var_340 = (j_outer_3 * 128);
        int32_t cse_var_339 = ((i_outer_2 * 128) + 112);
        int32_t cse_var_338 = (cse_var_340 + j_inner_s_112);
        ((float*)outputData_1)[((cse_var_339 * stride_4) + (cse_var_338 * stride_3))] = (((cse_var_338 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_338)) ? 0.000000e+00f : (((j_inner_s_112 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_339 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_112 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_340 + ((cse_var_339 * width) * 4)) + j_inner_s_112)]));
      }
      for (int32_t j_inner_s_113 = 0; j_inner_s_113 < 128; ++j_inner_s_113) {
        int32_t cse_var_343 = (j_outer_3 * 128);
        int32_t cse_var_342 = ((i_outer_2 * 128) + 113);
        int32_t cse_var_341 = (cse_var_343 + j_inner_s_113);
        ((float*)outputData_1)[((cse_var_342 * stride_4) + (cse_var_341 * stride_3))] = (((cse_var_341 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_341)) ? 0.000000e+00f : (((j_inner_s_113 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_342 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_113 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_343 + ((cse_var_342 * width) * 4)) + j_inner_s_113)]));
      }
      for (int32_t j_inner_s_114 = 0; j_inner_s_114 < 128; ++j_inner_s_114) {
        int32_t cse_var_346 = (j_outer_3 * 128);
        int32_t cse_var_345 = ((i_outer_2 * 128) + 114);
        int32_t cse_var_344 = (cse_var_346 + j_inner_s_114);
        ((float*)outputData_1)[((cse_var_345 * stride_4) + (cse_var_344 * stride_3))] = (((cse_var_344 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_344)) ? 0.000000e+00f : (((j_inner_s_114 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_345 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_114 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_346 + ((cse_var_345 * width) * 4)) + j_inner_s_114)]));
      }
      for (int32_t j_inner_s_115 = 0; j_inner_s_115 < 128; ++j_inner_s_115) {
        int32_t cse_var_349 = (j_outer_3 * 128);
        int32_t cse_var_348 = ((i_outer_2 * 128) + 115);
        int32_t cse_var_347 = (cse_var_349 + j_inner_s_115);
        ((float*)outputData_1)[((cse_var_348 * stride_4) + (cse_var_347 * stride_3))] = (((cse_var_347 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_347)) ? 0.000000e+00f : (((j_inner_s_115 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_348 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_115 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_349 + ((cse_var_348 * width) * 4)) + j_inner_s_115)]));
      }
      for (int32_t j_inner_s_116 = 0; j_inner_s_116 < 128; ++j_inner_s_116) {
        int32_t cse_var_352 = (j_outer_3 * 128);
        int32_t cse_var_351 = ((i_outer_2 * 128) + 116);
        int32_t cse_var_350 = (cse_var_352 + j_inner_s_116);
        ((float*)outputData_1)[((cse_var_351 * stride_4) + (cse_var_350 * stride_3))] = (((cse_var_350 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_350)) ? 0.000000e+00f : (((j_inner_s_116 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_351 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_116 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_352 + ((cse_var_351 * width) * 4)) + j_inner_s_116)]));
      }
      for (int32_t j_inner_s_117 = 0; j_inner_s_117 < 128; ++j_inner_s_117) {
        int32_t cse_var_355 = (j_outer_3 * 128);
        int32_t cse_var_354 = ((i_outer_2 * 128) + 117);
        int32_t cse_var_353 = (cse_var_355 + j_inner_s_117);
        ((float*)outputData_1)[((cse_var_354 * stride_4) + (cse_var_353 * stride_3))] = (((cse_var_353 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_353)) ? 0.000000e+00f : (((j_inner_s_117 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_354 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_117 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_355 + ((cse_var_354 * width) * 4)) + j_inner_s_117)]));
      }
      for (int32_t j_inner_s_118 = 0; j_inner_s_118 < 128; ++j_inner_s_118) {
        int32_t cse_var_358 = (j_outer_3 * 128);
        int32_t cse_var_357 = ((i_outer_2 * 128) + 118);
        int32_t cse_var_356 = (cse_var_358 + j_inner_s_118);
        ((float*)outputData_1)[((cse_var_357 * stride_4) + (cse_var_356 * stride_3))] = (((cse_var_356 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_356)) ? 0.000000e+00f : (((j_inner_s_118 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_357 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_118 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_358 + ((cse_var_357 * width) * 4)) + j_inner_s_118)]));
      }
      for (int32_t j_inner_s_119 = 0; j_inner_s_119 < 128; ++j_inner_s_119) {
        int32_t cse_var_361 = (j_outer_3 * 128);
        int32_t cse_var_360 = ((i_outer_2 * 128) + 119);
        int32_t cse_var_359 = (cse_var_361 + j_inner_s_119);
        ((float*)outputData_1)[((cse_var_360 * stride_4) + (cse_var_359 * stride_3))] = (((cse_var_359 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_359)) ? 0.000000e+00f : (((j_inner_s_119 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_360 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_119 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_361 + ((cse_var_360 * width) * 4)) + j_inner_s_119)]));
      }
      for (int32_t j_inner_s_120 = 0; j_inner_s_120 < 128; ++j_inner_s_120) {
        int32_t cse_var_364 = (j_outer_3 * 128);
        int32_t cse_var_363 = ((i_outer_2 * 128) + 120);
        int32_t cse_var_362 = (cse_var_364 + j_inner_s_120);
        ((float*)outputData_1)[((cse_var_363 * stride_4) + (cse_var_362 * stride_3))] = (((cse_var_362 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_362)) ? 0.000000e+00f : (((j_inner_s_120 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_363 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_120 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_364 + ((cse_var_363 * width) * 4)) + j_inner_s_120)]));
      }
      for (int32_t j_inner_s_121 = 0; j_inner_s_121 < 128; ++j_inner_s_121) {
        int32_t cse_var_367 = (j_outer_3 * 128);
        int32_t cse_var_366 = ((i_outer_2 * 128) + 121);
        int32_t cse_var_365 = (cse_var_367 + j_inner_s_121);
        ((float*)outputData_1)[((cse_var_366 * stride_4) + (cse_var_365 * stride_3))] = (((cse_var_365 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_365)) ? 0.000000e+00f : (((j_inner_s_121 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_366 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_121 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_367 + ((cse_var_366 * width) * 4)) + j_inner_s_121)]));
      }
      for (int32_t j_inner_s_122 = 0; j_inner_s_122 < 128; ++j_inner_s_122) {
        int32_t cse_var_370 = (j_outer_3 * 128);
        int32_t cse_var_369 = ((i_outer_2 * 128) + 122);
        int32_t cse_var_368 = (cse_var_370 + j_inner_s_122);
        ((float*)outputData_1)[((cse_var_369 * stride_4) + (cse_var_368 * stride_3))] = (((cse_var_368 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_368)) ? 0.000000e+00f : (((j_inner_s_122 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_369 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_122 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_370 + ((cse_var_369 * width) * 4)) + j_inner_s_122)]));
      }
      for (int32_t j_inner_s_123 = 0; j_inner_s_123 < 128; ++j_inner_s_123) {
        int32_t cse_var_373 = (j_outer_3 * 128);
        int32_t cse_var_372 = ((i_outer_2 * 128) + 123);
        int32_t cse_var_371 = (cse_var_373 + j_inner_s_123);
        ((float*)outputData_1)[((cse_var_372 * stride_4) + (cse_var_371 * stride_3))] = (((cse_var_371 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_371)) ? 0.000000e+00f : (((j_inner_s_123 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_372 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_123 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_373 + ((cse_var_372 * width) * 4)) + j_inner_s_123)]));
      }
      for (int32_t j_inner_s_124 = 0; j_inner_s_124 < 128; ++j_inner_s_124) {
        int32_t cse_var_376 = (j_outer_3 * 128);
        int32_t cse_var_375 = ((i_outer_2 * 128) + 124);
        int32_t cse_var_374 = (cse_var_376 + j_inner_s_124);
        ((float*)outputData_1)[((cse_var_375 * stride_4) + (cse_var_374 * stride_3))] = (((cse_var_374 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_374)) ? 0.000000e+00f : (((j_inner_s_124 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_375 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_124 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_376 + ((cse_var_375 * width) * 4)) + j_inner_s_124)]));
      }
      for (int32_t j_inner_s_125 = 0; j_inner_s_125 < 128; ++j_inner_s_125) {
        int32_t cse_var_379 = (j_outer_3 * 128);
        int32_t cse_var_378 = ((i_outer_2 * 128) + 125);
        int32_t cse_var_377 = (cse_var_379 + j_inner_s_125);
        ((float*)outputData_1)[((cse_var_378 * stride_4) + (cse_var_377 * stride_3))] = (((cse_var_377 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_377)) ? 0.000000e+00f : (((j_inner_s_125 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_378 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_125 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_379 + ((cse_var_378 * width) * 4)) + j_inner_s_125)]));
      }
      for (int32_t j_inner_s_126 = 0; j_inner_s_126 < 128; ++j_inner_s_126) {
        int32_t cse_var_382 = (j_outer_3 * 128);
        int32_t cse_var_381 = ((i_outer_2 * 128) + 126);
        int32_t cse_var_380 = (cse_var_382 + j_inner_s_126);
        ((float*)outputData_1)[((cse_var_381 * stride_4) + (cse_var_380 * stride_3))] = (((cse_var_380 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_380)) ? 0.000000e+00f : (((j_inner_s_126 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_381 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_126 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_382 + ((cse_var_381 * width) * 4)) + j_inner_s_126)]));
      }
      for (int32_t j_inner_s_127 = 0; j_inner_s_127 < 128; ++j_inner_s_127) {
        int32_t cse_var_385 = (j_outer_3 * 128);
        int32_t cse_var_384 = ((i_outer_2 * 128) + 127);
        int32_t cse_var_383 = (cse_var_385 + j_inner_s_127);
        ((float*)outputData_1)[((cse_var_384 * stride_4) + (cse_var_383 * stride_3))] = (((cse_var_383 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_383)) ? 0.000000e+00f : (((j_inner_s_127 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_384 * stride_1) + (((j_outer_3 * 32) + (j_inner_s_127 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_385 + ((cse_var_384 * width) * 4)) + j_inner_s_127)]));
      }
    }
    for (int32_t j_outer_4 = 0; j_outer_4 < (((width & 31) + 31) >> 5); ++j_outer_4) {
      for (int32_t j_inner_s_128 = 0; j_inner_s_128 < 128; ++j_inner_s_128) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_128) < (width * 4)) {
          int32_t cse_var_386 = (j_outer_4 * 128);
          ((float*)outputData_1)[(((i_outer_2 * stride_4) * 128) + (((((width >> 5) * 128) + cse_var_386) + j_inner_s_128) * stride_3))] = (((((((width >> 5) * 128) + cse_var_386) + j_inner_s_128) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + cse_var_386) + j_inner_s_128))) ? 0.000000e+00f : (((j_inner_s_128 % 4) == 0) ? ((float*)derivativeData_1)[(((i_outer_2 * stride_1) * 128) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_128 >> 2)) * stride))] : ((float*)upsamplingData)[(((((i_outer_2 * width) * 512) + ((width >> 5) * 128)) + cse_var_386) + j_inner_s_128)]));
        }
      }
      for (int32_t j_inner_s_129 = 0; j_inner_s_129 < 128; ++j_inner_s_129) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_129) < (width * 4)) {
          int32_t cse_var_387 = ((i_outer_2 * 128) + 1);
          ((float*)outputData_1)[((cse_var_387 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_129) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_129) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_129))) ? 0.000000e+00f : (((j_inner_s_129 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_387 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_129 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_387 * width) * 4)) + j_inner_s_129)]));
        }
      }
      for (int32_t j_inner_s_130 = 0; j_inner_s_130 < 128; ++j_inner_s_130) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_130) < (width * 4)) {
          int32_t cse_var_388 = ((i_outer_2 * 128) + 2);
          ((float*)outputData_1)[((cse_var_388 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_130) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_130) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_130))) ? 0.000000e+00f : (((j_inner_s_130 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_388 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_130 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_388 * width) * 4)) + j_inner_s_130)]));
        }
      }
      for (int32_t j_inner_s_131 = 0; j_inner_s_131 < 128; ++j_inner_s_131) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_131) < (width * 4)) {
          int32_t cse_var_389 = ((i_outer_2 * 128) + 3);
          ((float*)outputData_1)[((cse_var_389 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_131) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_131) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_131))) ? 0.000000e+00f : (((j_inner_s_131 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_389 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_131 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_389 * width) * 4)) + j_inner_s_131)]));
        }
      }
      for (int32_t j_inner_s_132 = 0; j_inner_s_132 < 128; ++j_inner_s_132) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_132) < (width * 4)) {
          int32_t cse_var_390 = ((i_outer_2 * 128) + 4);
          ((float*)outputData_1)[((cse_var_390 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_132) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_132) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_132))) ? 0.000000e+00f : (((j_inner_s_132 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_390 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_132 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_390 * width) * 4)) + j_inner_s_132)]));
        }
      }
      for (int32_t j_inner_s_133 = 0; j_inner_s_133 < 128; ++j_inner_s_133) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_133) < (width * 4)) {
          int32_t cse_var_391 = ((i_outer_2 * 128) + 5);
          ((float*)outputData_1)[((cse_var_391 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_133) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_133) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_133))) ? 0.000000e+00f : (((j_inner_s_133 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_391 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_133 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_391 * width) * 4)) + j_inner_s_133)]));
        }
      }
      for (int32_t j_inner_s_134 = 0; j_inner_s_134 < 128; ++j_inner_s_134) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_134) < (width * 4)) {
          int32_t cse_var_392 = ((i_outer_2 * 128) + 6);
          ((float*)outputData_1)[((cse_var_392 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_134) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_134) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_134))) ? 0.000000e+00f : (((j_inner_s_134 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_392 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_134 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_392 * width) * 4)) + j_inner_s_134)]));
        }
      }
      for (int32_t j_inner_s_135 = 0; j_inner_s_135 < 128; ++j_inner_s_135) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_135) < (width * 4)) {
          int32_t cse_var_393 = ((i_outer_2 * 128) + 7);
          ((float*)outputData_1)[((cse_var_393 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_135) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_135) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_135))) ? 0.000000e+00f : (((j_inner_s_135 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_393 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_135 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_393 * width) * 4)) + j_inner_s_135)]));
        }
      }
      for (int32_t j_inner_s_136 = 0; j_inner_s_136 < 128; ++j_inner_s_136) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_136) < (width * 4)) {
          int32_t cse_var_394 = ((i_outer_2 * 128) + 8);
          ((float*)outputData_1)[((cse_var_394 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_136) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_136) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_136))) ? 0.000000e+00f : (((j_inner_s_136 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_394 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_136 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_394 * width) * 4)) + j_inner_s_136)]));
        }
      }
      for (int32_t j_inner_s_137 = 0; j_inner_s_137 < 128; ++j_inner_s_137) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_137) < (width * 4)) {
          int32_t cse_var_395 = ((i_outer_2 * 128) + 9);
          ((float*)outputData_1)[((cse_var_395 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_137) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_137) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_137))) ? 0.000000e+00f : (((j_inner_s_137 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_395 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_137 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_395 * width) * 4)) + j_inner_s_137)]));
        }
      }
      for (int32_t j_inner_s_138 = 0; j_inner_s_138 < 128; ++j_inner_s_138) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_138) < (width * 4)) {
          int32_t cse_var_396 = ((i_outer_2 * 128) + 10);
          ((float*)outputData_1)[((cse_var_396 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_138) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_138) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_138))) ? 0.000000e+00f : (((j_inner_s_138 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_396 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_138 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_396 * width) * 4)) + j_inner_s_138)]));
        }
      }
      for (int32_t j_inner_s_139 = 0; j_inner_s_139 < 128; ++j_inner_s_139) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_139) < (width * 4)) {
          int32_t cse_var_397 = ((i_outer_2 * 128) + 11);
          ((float*)outputData_1)[((cse_var_397 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_139) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_139) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_139))) ? 0.000000e+00f : (((j_inner_s_139 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_397 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_139 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_397 * width) * 4)) + j_inner_s_139)]));
        }
      }
      for (int32_t j_inner_s_140 = 0; j_inner_s_140 < 128; ++j_inner_s_140) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_140) < (width * 4)) {
          int32_t cse_var_398 = ((i_outer_2 * 128) + 12);
          ((float*)outputData_1)[((cse_var_398 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_140) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_140) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_140))) ? 0.000000e+00f : (((j_inner_s_140 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_398 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_140 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_398 * width) * 4)) + j_inner_s_140)]));
        }
      }
      for (int32_t j_inner_s_141 = 0; j_inner_s_141 < 128; ++j_inner_s_141) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_141) < (width * 4)) {
          int32_t cse_var_399 = ((i_outer_2 * 128) + 13);
          ((float*)outputData_1)[((cse_var_399 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_141) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_141) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_141))) ? 0.000000e+00f : (((j_inner_s_141 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_399 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_141 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_399 * width) * 4)) + j_inner_s_141)]));
        }
      }
      for (int32_t j_inner_s_142 = 0; j_inner_s_142 < 128; ++j_inner_s_142) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_142) < (width * 4)) {
          int32_t cse_var_400 = ((i_outer_2 * 128) + 14);
          ((float*)outputData_1)[((cse_var_400 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_142) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_142) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_142))) ? 0.000000e+00f : (((j_inner_s_142 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_400 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_142 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_400 * width) * 4)) + j_inner_s_142)]));
        }
      }
      for (int32_t j_inner_s_143 = 0; j_inner_s_143 < 128; ++j_inner_s_143) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_143) < (width * 4)) {
          int32_t cse_var_401 = ((i_outer_2 * 128) + 15);
          ((float*)outputData_1)[((cse_var_401 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_143) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_143) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_143))) ? 0.000000e+00f : (((j_inner_s_143 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_401 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_143 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_401 * width) * 4)) + j_inner_s_143)]));
        }
      }
      for (int32_t j_inner_s_144 = 0; j_inner_s_144 < 128; ++j_inner_s_144) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_144) < (width * 4)) {
          int32_t cse_var_402 = ((i_outer_2 * 128) + 16);
          ((float*)outputData_1)[((cse_var_402 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_144) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_144) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_144))) ? 0.000000e+00f : (((j_inner_s_144 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_402 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_144 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_402 * width) * 4)) + j_inner_s_144)]));
        }
      }
      for (int32_t j_inner_s_145 = 0; j_inner_s_145 < 128; ++j_inner_s_145) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_145) < (width * 4)) {
          int32_t cse_var_403 = ((i_outer_2 * 128) + 17);
          ((float*)outputData_1)[((cse_var_403 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_145) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_145) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_145))) ? 0.000000e+00f : (((j_inner_s_145 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_403 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_145 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_403 * width) * 4)) + j_inner_s_145)]));
        }
      }
      for (int32_t j_inner_s_146 = 0; j_inner_s_146 < 128; ++j_inner_s_146) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_146) < (width * 4)) {
          int32_t cse_var_404 = ((i_outer_2 * 128) + 18);
          ((float*)outputData_1)[((cse_var_404 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_146) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_146) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_146))) ? 0.000000e+00f : (((j_inner_s_146 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_404 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_146 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_404 * width) * 4)) + j_inner_s_146)]));
        }
      }
      for (int32_t j_inner_s_147 = 0; j_inner_s_147 < 128; ++j_inner_s_147) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_147) < (width * 4)) {
          int32_t cse_var_405 = ((i_outer_2 * 128) + 19);
          ((float*)outputData_1)[((cse_var_405 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_147) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_147) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_147))) ? 0.000000e+00f : (((j_inner_s_147 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_405 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_147 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_405 * width) * 4)) + j_inner_s_147)]));
        }
      }
      for (int32_t j_inner_s_148 = 0; j_inner_s_148 < 128; ++j_inner_s_148) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_148) < (width * 4)) {
          int32_t cse_var_406 = ((i_outer_2 * 128) + 20);
          ((float*)outputData_1)[((cse_var_406 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_148) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_148) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_148))) ? 0.000000e+00f : (((j_inner_s_148 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_406 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_148 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_406 * width) * 4)) + j_inner_s_148)]));
        }
      }
      for (int32_t j_inner_s_149 = 0; j_inner_s_149 < 128; ++j_inner_s_149) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_149) < (width * 4)) {
          int32_t cse_var_407 = ((i_outer_2 * 128) + 21);
          ((float*)outputData_1)[((cse_var_407 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_149) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_149) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_149))) ? 0.000000e+00f : (((j_inner_s_149 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_407 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_149 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_407 * width) * 4)) + j_inner_s_149)]));
        }
      }
      for (int32_t j_inner_s_150 = 0; j_inner_s_150 < 128; ++j_inner_s_150) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_150) < (width * 4)) {
          int32_t cse_var_408 = ((i_outer_2 * 128) + 22);
          ((float*)outputData_1)[((cse_var_408 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_150) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_150) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_150))) ? 0.000000e+00f : (((j_inner_s_150 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_408 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_150 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_408 * width) * 4)) + j_inner_s_150)]));
        }
      }
      for (int32_t j_inner_s_151 = 0; j_inner_s_151 < 128; ++j_inner_s_151) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_151) < (width * 4)) {
          int32_t cse_var_409 = ((i_outer_2 * 128) + 23);
          ((float*)outputData_1)[((cse_var_409 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_151) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_151) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_151))) ? 0.000000e+00f : (((j_inner_s_151 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_409 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_151 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_409 * width) * 4)) + j_inner_s_151)]));
        }
      }
      for (int32_t j_inner_s_152 = 0; j_inner_s_152 < 128; ++j_inner_s_152) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_152) < (width * 4)) {
          int32_t cse_var_410 = ((i_outer_2 * 128) + 24);
          ((float*)outputData_1)[((cse_var_410 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_152) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_152) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_152))) ? 0.000000e+00f : (((j_inner_s_152 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_410 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_152 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_410 * width) * 4)) + j_inner_s_152)]));
        }
      }
      for (int32_t j_inner_s_153 = 0; j_inner_s_153 < 128; ++j_inner_s_153) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_153) < (width * 4)) {
          int32_t cse_var_411 = ((i_outer_2 * 128) + 25);
          ((float*)outputData_1)[((cse_var_411 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_153) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_153) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_153))) ? 0.000000e+00f : (((j_inner_s_153 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_411 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_153 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_411 * width) * 4)) + j_inner_s_153)]));
        }
      }
      for (int32_t j_inner_s_154 = 0; j_inner_s_154 < 128; ++j_inner_s_154) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_154) < (width * 4)) {
          int32_t cse_var_412 = ((i_outer_2 * 128) + 26);
          ((float*)outputData_1)[((cse_var_412 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_154) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_154) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_154))) ? 0.000000e+00f : (((j_inner_s_154 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_412 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_154 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_412 * width) * 4)) + j_inner_s_154)]));
        }
      }
      for (int32_t j_inner_s_155 = 0; j_inner_s_155 < 128; ++j_inner_s_155) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_155) < (width * 4)) {
          int32_t cse_var_413 = ((i_outer_2 * 128) + 27);
          ((float*)outputData_1)[((cse_var_413 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_155) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_155) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_155))) ? 0.000000e+00f : (((j_inner_s_155 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_413 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_155 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_413 * width) * 4)) + j_inner_s_155)]));
        }
      }
      for (int32_t j_inner_s_156 = 0; j_inner_s_156 < 128; ++j_inner_s_156) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_156) < (width * 4)) {
          int32_t cse_var_414 = ((i_outer_2 * 128) + 28);
          ((float*)outputData_1)[((cse_var_414 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_156) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_156) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_156))) ? 0.000000e+00f : (((j_inner_s_156 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_414 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_156 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_414 * width) * 4)) + j_inner_s_156)]));
        }
      }
      for (int32_t j_inner_s_157 = 0; j_inner_s_157 < 128; ++j_inner_s_157) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_157) < (width * 4)) {
          int32_t cse_var_415 = ((i_outer_2 * 128) + 29);
          ((float*)outputData_1)[((cse_var_415 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_157) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_157) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_157))) ? 0.000000e+00f : (((j_inner_s_157 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_415 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_157 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_415 * width) * 4)) + j_inner_s_157)]));
        }
      }
      for (int32_t j_inner_s_158 = 0; j_inner_s_158 < 128; ++j_inner_s_158) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_158) < (width * 4)) {
          int32_t cse_var_416 = ((i_outer_2 * 128) + 30);
          ((float*)outputData_1)[((cse_var_416 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_158) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_158) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_158))) ? 0.000000e+00f : (((j_inner_s_158 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_416 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_158 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_416 * width) * 4)) + j_inner_s_158)]));
        }
      }
      for (int32_t j_inner_s_159 = 0; j_inner_s_159 < 128; ++j_inner_s_159) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_159) < (width * 4)) {
          int32_t cse_var_417 = ((i_outer_2 * 128) + 31);
          ((float*)outputData_1)[((cse_var_417 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_159) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_159) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_159))) ? 0.000000e+00f : (((j_inner_s_159 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_417 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_159 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_417 * width) * 4)) + j_inner_s_159)]));
        }
      }
      for (int32_t j_inner_s_160 = 0; j_inner_s_160 < 128; ++j_inner_s_160) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_160) < (width * 4)) {
          int32_t cse_var_418 = ((i_outer_2 * 128) + 32);
          ((float*)outputData_1)[((cse_var_418 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_160) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_160) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_160))) ? 0.000000e+00f : (((j_inner_s_160 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_418 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_160 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_418 * width) * 4)) + j_inner_s_160)]));
        }
      }
      for (int32_t j_inner_s_161 = 0; j_inner_s_161 < 128; ++j_inner_s_161) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_161) < (width * 4)) {
          int32_t cse_var_419 = ((i_outer_2 * 128) + 33);
          ((float*)outputData_1)[((cse_var_419 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_161) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_161) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_161))) ? 0.000000e+00f : (((j_inner_s_161 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_419 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_161 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_419 * width) * 4)) + j_inner_s_161)]));
        }
      }
      for (int32_t j_inner_s_162 = 0; j_inner_s_162 < 128; ++j_inner_s_162) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_162) < (width * 4)) {
          int32_t cse_var_420 = ((i_outer_2 * 128) + 34);
          ((float*)outputData_1)[((cse_var_420 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_162) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_162) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_162))) ? 0.000000e+00f : (((j_inner_s_162 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_420 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_162 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_420 * width) * 4)) + j_inner_s_162)]));
        }
      }
      for (int32_t j_inner_s_163 = 0; j_inner_s_163 < 128; ++j_inner_s_163) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_163) < (width * 4)) {
          int32_t cse_var_421 = ((i_outer_2 * 128) + 35);
          ((float*)outputData_1)[((cse_var_421 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_163) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_163) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_163))) ? 0.000000e+00f : (((j_inner_s_163 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_421 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_163 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_421 * width) * 4)) + j_inner_s_163)]));
        }
      }
      for (int32_t j_inner_s_164 = 0; j_inner_s_164 < 128; ++j_inner_s_164) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_164) < (width * 4)) {
          int32_t cse_var_422 = ((i_outer_2 * 128) + 36);
          ((float*)outputData_1)[((cse_var_422 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_164) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_164) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_164))) ? 0.000000e+00f : (((j_inner_s_164 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_422 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_164 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_422 * width) * 4)) + j_inner_s_164)]));
        }
      }
      for (int32_t j_inner_s_165 = 0; j_inner_s_165 < 128; ++j_inner_s_165) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_165) < (width * 4)) {
          int32_t cse_var_423 = ((i_outer_2 * 128) + 37);
          ((float*)outputData_1)[((cse_var_423 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_165) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_165) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_165))) ? 0.000000e+00f : (((j_inner_s_165 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_423 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_165 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_423 * width) * 4)) + j_inner_s_165)]));
        }
      }
      for (int32_t j_inner_s_166 = 0; j_inner_s_166 < 128; ++j_inner_s_166) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_166) < (width * 4)) {
          int32_t cse_var_424 = ((i_outer_2 * 128) + 38);
          ((float*)outputData_1)[((cse_var_424 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_166) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_166) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_166))) ? 0.000000e+00f : (((j_inner_s_166 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_424 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_166 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_424 * width) * 4)) + j_inner_s_166)]));
        }
      }
      for (int32_t j_inner_s_167 = 0; j_inner_s_167 < 128; ++j_inner_s_167) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_167) < (width * 4)) {
          int32_t cse_var_425 = ((i_outer_2 * 128) + 39);
          ((float*)outputData_1)[((cse_var_425 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_167) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_167) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_167))) ? 0.000000e+00f : (((j_inner_s_167 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_425 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_167 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_425 * width) * 4)) + j_inner_s_167)]));
        }
      }
      for (int32_t j_inner_s_168 = 0; j_inner_s_168 < 128; ++j_inner_s_168) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_168) < (width * 4)) {
          int32_t cse_var_426 = ((i_outer_2 * 128) + 40);
          ((float*)outputData_1)[((cse_var_426 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_168) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_168) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_168))) ? 0.000000e+00f : (((j_inner_s_168 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_426 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_168 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_426 * width) * 4)) + j_inner_s_168)]));
        }
      }
      for (int32_t j_inner_s_169 = 0; j_inner_s_169 < 128; ++j_inner_s_169) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_169) < (width * 4)) {
          int32_t cse_var_427 = ((i_outer_2 * 128) + 41);
          ((float*)outputData_1)[((cse_var_427 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_169) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_169) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_169))) ? 0.000000e+00f : (((j_inner_s_169 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_427 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_169 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_427 * width) * 4)) + j_inner_s_169)]));
        }
      }
      for (int32_t j_inner_s_170 = 0; j_inner_s_170 < 128; ++j_inner_s_170) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_170) < (width * 4)) {
          int32_t cse_var_428 = ((i_outer_2 * 128) + 42);
          ((float*)outputData_1)[((cse_var_428 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_170) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_170) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_170))) ? 0.000000e+00f : (((j_inner_s_170 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_428 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_170 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_428 * width) * 4)) + j_inner_s_170)]));
        }
      }
      for (int32_t j_inner_s_171 = 0; j_inner_s_171 < 128; ++j_inner_s_171) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_171) < (width * 4)) {
          int32_t cse_var_429 = ((i_outer_2 * 128) + 43);
          ((float*)outputData_1)[((cse_var_429 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_171) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_171) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_171))) ? 0.000000e+00f : (((j_inner_s_171 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_429 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_171 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_429 * width) * 4)) + j_inner_s_171)]));
        }
      }
      for (int32_t j_inner_s_172 = 0; j_inner_s_172 < 128; ++j_inner_s_172) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_172) < (width * 4)) {
          int32_t cse_var_430 = ((i_outer_2 * 128) + 44);
          ((float*)outputData_1)[((cse_var_430 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_172) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_172) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_172))) ? 0.000000e+00f : (((j_inner_s_172 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_430 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_172 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_430 * width) * 4)) + j_inner_s_172)]));
        }
      }
      for (int32_t j_inner_s_173 = 0; j_inner_s_173 < 128; ++j_inner_s_173) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_173) < (width * 4)) {
          int32_t cse_var_431 = ((i_outer_2 * 128) + 45);
          ((float*)outputData_1)[((cse_var_431 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_173) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_173) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_173))) ? 0.000000e+00f : (((j_inner_s_173 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_431 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_173 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_431 * width) * 4)) + j_inner_s_173)]));
        }
      }
      for (int32_t j_inner_s_174 = 0; j_inner_s_174 < 128; ++j_inner_s_174) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_174) < (width * 4)) {
          int32_t cse_var_432 = ((i_outer_2 * 128) + 46);
          ((float*)outputData_1)[((cse_var_432 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_174) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_174) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_174))) ? 0.000000e+00f : (((j_inner_s_174 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_432 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_174 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_432 * width) * 4)) + j_inner_s_174)]));
        }
      }
      for (int32_t j_inner_s_175 = 0; j_inner_s_175 < 128; ++j_inner_s_175) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_175) < (width * 4)) {
          int32_t cse_var_433 = ((i_outer_2 * 128) + 47);
          ((float*)outputData_1)[((cse_var_433 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_175) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_175) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_175))) ? 0.000000e+00f : (((j_inner_s_175 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_433 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_175 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_433 * width) * 4)) + j_inner_s_175)]));
        }
      }
      for (int32_t j_inner_s_176 = 0; j_inner_s_176 < 128; ++j_inner_s_176) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_176) < (width * 4)) {
          int32_t cse_var_434 = ((i_outer_2 * 128) + 48);
          ((float*)outputData_1)[((cse_var_434 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_176) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_176) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_176))) ? 0.000000e+00f : (((j_inner_s_176 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_434 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_176 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_434 * width) * 4)) + j_inner_s_176)]));
        }
      }
      for (int32_t j_inner_s_177 = 0; j_inner_s_177 < 128; ++j_inner_s_177) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_177) < (width * 4)) {
          int32_t cse_var_435 = ((i_outer_2 * 128) + 49);
          ((float*)outputData_1)[((cse_var_435 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_177) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_177) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_177))) ? 0.000000e+00f : (((j_inner_s_177 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_435 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_177 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_435 * width) * 4)) + j_inner_s_177)]));
        }
      }
      for (int32_t j_inner_s_178 = 0; j_inner_s_178 < 128; ++j_inner_s_178) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_178) < (width * 4)) {
          int32_t cse_var_436 = ((i_outer_2 * 128) + 50);
          ((float*)outputData_1)[((cse_var_436 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_178) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_178) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_178))) ? 0.000000e+00f : (((j_inner_s_178 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_436 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_178 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_436 * width) * 4)) + j_inner_s_178)]));
        }
      }
      for (int32_t j_inner_s_179 = 0; j_inner_s_179 < 128; ++j_inner_s_179) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_179) < (width * 4)) {
          int32_t cse_var_437 = ((i_outer_2 * 128) + 51);
          ((float*)outputData_1)[((cse_var_437 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_179) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_179) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_179))) ? 0.000000e+00f : (((j_inner_s_179 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_437 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_179 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_437 * width) * 4)) + j_inner_s_179)]));
        }
      }
      for (int32_t j_inner_s_180 = 0; j_inner_s_180 < 128; ++j_inner_s_180) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_180) < (width * 4)) {
          int32_t cse_var_438 = ((i_outer_2 * 128) + 52);
          ((float*)outputData_1)[((cse_var_438 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_180) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_180) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_180))) ? 0.000000e+00f : (((j_inner_s_180 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_438 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_180 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_438 * width) * 4)) + j_inner_s_180)]));
        }
      }
      for (int32_t j_inner_s_181 = 0; j_inner_s_181 < 128; ++j_inner_s_181) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_181) < (width * 4)) {
          int32_t cse_var_439 = ((i_outer_2 * 128) + 53);
          ((float*)outputData_1)[((cse_var_439 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_181) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_181) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_181))) ? 0.000000e+00f : (((j_inner_s_181 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_439 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_181 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_439 * width) * 4)) + j_inner_s_181)]));
        }
      }
      for (int32_t j_inner_s_182 = 0; j_inner_s_182 < 128; ++j_inner_s_182) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_182) < (width * 4)) {
          int32_t cse_var_440 = ((i_outer_2 * 128) + 54);
          ((float*)outputData_1)[((cse_var_440 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_182) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_182) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_182))) ? 0.000000e+00f : (((j_inner_s_182 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_440 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_182 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_440 * width) * 4)) + j_inner_s_182)]));
        }
      }
      for (int32_t j_inner_s_183 = 0; j_inner_s_183 < 128; ++j_inner_s_183) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_183) < (width * 4)) {
          int32_t cse_var_441 = ((i_outer_2 * 128) + 55);
          ((float*)outputData_1)[((cse_var_441 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_183) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_183) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_183))) ? 0.000000e+00f : (((j_inner_s_183 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_441 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_183 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_441 * width) * 4)) + j_inner_s_183)]));
        }
      }
      for (int32_t j_inner_s_184 = 0; j_inner_s_184 < 128; ++j_inner_s_184) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_184) < (width * 4)) {
          int32_t cse_var_442 = ((i_outer_2 * 128) + 56);
          ((float*)outputData_1)[((cse_var_442 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_184) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_184) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_184))) ? 0.000000e+00f : (((j_inner_s_184 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_442 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_184 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_442 * width) * 4)) + j_inner_s_184)]));
        }
      }
      for (int32_t j_inner_s_185 = 0; j_inner_s_185 < 128; ++j_inner_s_185) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_185) < (width * 4)) {
          int32_t cse_var_443 = ((i_outer_2 * 128) + 57);
          ((float*)outputData_1)[((cse_var_443 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_185) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_185) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_185))) ? 0.000000e+00f : (((j_inner_s_185 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_443 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_185 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_443 * width) * 4)) + j_inner_s_185)]));
        }
      }
      for (int32_t j_inner_s_186 = 0; j_inner_s_186 < 128; ++j_inner_s_186) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_186) < (width * 4)) {
          int32_t cse_var_444 = ((i_outer_2 * 128) + 58);
          ((float*)outputData_1)[((cse_var_444 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_186) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_186) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_186))) ? 0.000000e+00f : (((j_inner_s_186 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_444 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_186 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_444 * width) * 4)) + j_inner_s_186)]));
        }
      }
      for (int32_t j_inner_s_187 = 0; j_inner_s_187 < 128; ++j_inner_s_187) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_187) < (width * 4)) {
          int32_t cse_var_445 = ((i_outer_2 * 128) + 59);
          ((float*)outputData_1)[((cse_var_445 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_187) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_187) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_187))) ? 0.000000e+00f : (((j_inner_s_187 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_445 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_187 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_445 * width) * 4)) + j_inner_s_187)]));
        }
      }
      for (int32_t j_inner_s_188 = 0; j_inner_s_188 < 128; ++j_inner_s_188) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_188) < (width * 4)) {
          int32_t cse_var_446 = ((i_outer_2 * 128) + 60);
          ((float*)outputData_1)[((cse_var_446 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_188) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_188) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_188))) ? 0.000000e+00f : (((j_inner_s_188 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_446 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_188 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_446 * width) * 4)) + j_inner_s_188)]));
        }
      }
      for (int32_t j_inner_s_189 = 0; j_inner_s_189 < 128; ++j_inner_s_189) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_189) < (width * 4)) {
          int32_t cse_var_447 = ((i_outer_2 * 128) + 61);
          ((float*)outputData_1)[((cse_var_447 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_189) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_189) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_189))) ? 0.000000e+00f : (((j_inner_s_189 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_447 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_189 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_447 * width) * 4)) + j_inner_s_189)]));
        }
      }
      for (int32_t j_inner_s_190 = 0; j_inner_s_190 < 128; ++j_inner_s_190) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_190) < (width * 4)) {
          int32_t cse_var_448 = ((i_outer_2 * 128) + 62);
          ((float*)outputData_1)[((cse_var_448 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_190) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_190) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_190))) ? 0.000000e+00f : (((j_inner_s_190 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_448 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_190 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_448 * width) * 4)) + j_inner_s_190)]));
        }
      }
      for (int32_t j_inner_s_191 = 0; j_inner_s_191 < 128; ++j_inner_s_191) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_191) < (width * 4)) {
          int32_t cse_var_449 = ((i_outer_2 * 128) + 63);
          ((float*)outputData_1)[((cse_var_449 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_191) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_191) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_191))) ? 0.000000e+00f : (((j_inner_s_191 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_449 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_191 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_449 * width) * 4)) + j_inner_s_191)]));
        }
      }
      for (int32_t j_inner_s_192 = 0; j_inner_s_192 < 128; ++j_inner_s_192) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_192) < (width * 4)) {
          int32_t cse_var_450 = ((i_outer_2 * 128) + 64);
          ((float*)outputData_1)[((cse_var_450 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_192) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_192) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_192))) ? 0.000000e+00f : (((j_inner_s_192 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_450 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_192 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_450 * width) * 4)) + j_inner_s_192)]));
        }
      }
      for (int32_t j_inner_s_193 = 0; j_inner_s_193 < 128; ++j_inner_s_193) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_193) < (width * 4)) {
          int32_t cse_var_451 = ((i_outer_2 * 128) + 65);
          ((float*)outputData_1)[((cse_var_451 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_193) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_193) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_193))) ? 0.000000e+00f : (((j_inner_s_193 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_451 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_193 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_451 * width) * 4)) + j_inner_s_193)]));
        }
      }
      for (int32_t j_inner_s_194 = 0; j_inner_s_194 < 128; ++j_inner_s_194) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_194) < (width * 4)) {
          int32_t cse_var_452 = ((i_outer_2 * 128) + 66);
          ((float*)outputData_1)[((cse_var_452 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_194) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_194) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_194))) ? 0.000000e+00f : (((j_inner_s_194 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_452 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_194 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_452 * width) * 4)) + j_inner_s_194)]));
        }
      }
      for (int32_t j_inner_s_195 = 0; j_inner_s_195 < 128; ++j_inner_s_195) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_195) < (width * 4)) {
          int32_t cse_var_453 = ((i_outer_2 * 128) + 67);
          ((float*)outputData_1)[((cse_var_453 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_195) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_195) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_195))) ? 0.000000e+00f : (((j_inner_s_195 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_453 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_195 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_453 * width) * 4)) + j_inner_s_195)]));
        }
      }
      for (int32_t j_inner_s_196 = 0; j_inner_s_196 < 128; ++j_inner_s_196) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_196) < (width * 4)) {
          int32_t cse_var_454 = ((i_outer_2 * 128) + 68);
          ((float*)outputData_1)[((cse_var_454 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_196) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_196) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_196))) ? 0.000000e+00f : (((j_inner_s_196 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_454 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_196 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_454 * width) * 4)) + j_inner_s_196)]));
        }
      }
      for (int32_t j_inner_s_197 = 0; j_inner_s_197 < 128; ++j_inner_s_197) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_197) < (width * 4)) {
          int32_t cse_var_455 = ((i_outer_2 * 128) + 69);
          ((float*)outputData_1)[((cse_var_455 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_197) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_197) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_197))) ? 0.000000e+00f : (((j_inner_s_197 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_455 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_197 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_455 * width) * 4)) + j_inner_s_197)]));
        }
      }
      for (int32_t j_inner_s_198 = 0; j_inner_s_198 < 128; ++j_inner_s_198) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_198) < (width * 4)) {
          int32_t cse_var_456 = ((i_outer_2 * 128) + 70);
          ((float*)outputData_1)[((cse_var_456 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_198) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_198) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_198))) ? 0.000000e+00f : (((j_inner_s_198 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_456 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_198 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_456 * width) * 4)) + j_inner_s_198)]));
        }
      }
      for (int32_t j_inner_s_199 = 0; j_inner_s_199 < 128; ++j_inner_s_199) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_199) < (width * 4)) {
          int32_t cse_var_457 = ((i_outer_2 * 128) + 71);
          ((float*)outputData_1)[((cse_var_457 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_199) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_199) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_199))) ? 0.000000e+00f : (((j_inner_s_199 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_457 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_199 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_457 * width) * 4)) + j_inner_s_199)]));
        }
      }
      for (int32_t j_inner_s_200 = 0; j_inner_s_200 < 128; ++j_inner_s_200) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_200) < (width * 4)) {
          int32_t cse_var_458 = ((i_outer_2 * 128) + 72);
          ((float*)outputData_1)[((cse_var_458 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_200) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_200) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_200))) ? 0.000000e+00f : (((j_inner_s_200 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_458 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_200 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_458 * width) * 4)) + j_inner_s_200)]));
        }
      }
      for (int32_t j_inner_s_201 = 0; j_inner_s_201 < 128; ++j_inner_s_201) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_201) < (width * 4)) {
          int32_t cse_var_459 = ((i_outer_2 * 128) + 73);
          ((float*)outputData_1)[((cse_var_459 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_201) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_201) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_201))) ? 0.000000e+00f : (((j_inner_s_201 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_459 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_201 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_459 * width) * 4)) + j_inner_s_201)]));
        }
      }
      for (int32_t j_inner_s_202 = 0; j_inner_s_202 < 128; ++j_inner_s_202) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_202) < (width * 4)) {
          int32_t cse_var_460 = ((i_outer_2 * 128) + 74);
          ((float*)outputData_1)[((cse_var_460 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_202) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_202) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_202))) ? 0.000000e+00f : (((j_inner_s_202 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_460 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_202 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_460 * width) * 4)) + j_inner_s_202)]));
        }
      }
      for (int32_t j_inner_s_203 = 0; j_inner_s_203 < 128; ++j_inner_s_203) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_203) < (width * 4)) {
          int32_t cse_var_461 = ((i_outer_2 * 128) + 75);
          ((float*)outputData_1)[((cse_var_461 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_203) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_203) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_203))) ? 0.000000e+00f : (((j_inner_s_203 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_461 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_203 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_461 * width) * 4)) + j_inner_s_203)]));
        }
      }
      for (int32_t j_inner_s_204 = 0; j_inner_s_204 < 128; ++j_inner_s_204) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_204) < (width * 4)) {
          int32_t cse_var_462 = ((i_outer_2 * 128) + 76);
          ((float*)outputData_1)[((cse_var_462 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_204) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_204) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_204))) ? 0.000000e+00f : (((j_inner_s_204 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_462 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_204 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_462 * width) * 4)) + j_inner_s_204)]));
        }
      }
      for (int32_t j_inner_s_205 = 0; j_inner_s_205 < 128; ++j_inner_s_205) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_205) < (width * 4)) {
          int32_t cse_var_463 = ((i_outer_2 * 128) + 77);
          ((float*)outputData_1)[((cse_var_463 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_205) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_205) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_205))) ? 0.000000e+00f : (((j_inner_s_205 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_463 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_205 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_463 * width) * 4)) + j_inner_s_205)]));
        }
      }
      for (int32_t j_inner_s_206 = 0; j_inner_s_206 < 128; ++j_inner_s_206) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_206) < (width * 4)) {
          int32_t cse_var_464 = ((i_outer_2 * 128) + 78);
          ((float*)outputData_1)[((cse_var_464 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_206) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_206) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_206))) ? 0.000000e+00f : (((j_inner_s_206 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_464 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_206 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_464 * width) * 4)) + j_inner_s_206)]));
        }
      }
      for (int32_t j_inner_s_207 = 0; j_inner_s_207 < 128; ++j_inner_s_207) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_207) < (width * 4)) {
          int32_t cse_var_465 = ((i_outer_2 * 128) + 79);
          ((float*)outputData_1)[((cse_var_465 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_207) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_207) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_207))) ? 0.000000e+00f : (((j_inner_s_207 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_465 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_207 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_465 * width) * 4)) + j_inner_s_207)]));
        }
      }
      for (int32_t j_inner_s_208 = 0; j_inner_s_208 < 128; ++j_inner_s_208) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_208) < (width * 4)) {
          int32_t cse_var_466 = ((i_outer_2 * 128) + 80);
          ((float*)outputData_1)[((cse_var_466 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_208) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_208) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_208))) ? 0.000000e+00f : (((j_inner_s_208 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_466 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_208 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_466 * width) * 4)) + j_inner_s_208)]));
        }
      }
      for (int32_t j_inner_s_209 = 0; j_inner_s_209 < 128; ++j_inner_s_209) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_209) < (width * 4)) {
          int32_t cse_var_467 = ((i_outer_2 * 128) + 81);
          ((float*)outputData_1)[((cse_var_467 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_209) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_209) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_209))) ? 0.000000e+00f : (((j_inner_s_209 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_467 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_209 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_467 * width) * 4)) + j_inner_s_209)]));
        }
      }
      for (int32_t j_inner_s_210 = 0; j_inner_s_210 < 128; ++j_inner_s_210) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_210) < (width * 4)) {
          int32_t cse_var_468 = ((i_outer_2 * 128) + 82);
          ((float*)outputData_1)[((cse_var_468 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_210) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_210) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_210))) ? 0.000000e+00f : (((j_inner_s_210 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_468 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_210 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_468 * width) * 4)) + j_inner_s_210)]));
        }
      }
      for (int32_t j_inner_s_211 = 0; j_inner_s_211 < 128; ++j_inner_s_211) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_211) < (width * 4)) {
          int32_t cse_var_469 = ((i_outer_2 * 128) + 83);
          ((float*)outputData_1)[((cse_var_469 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_211) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_211) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_211))) ? 0.000000e+00f : (((j_inner_s_211 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_469 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_211 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_469 * width) * 4)) + j_inner_s_211)]));
        }
      }
      for (int32_t j_inner_s_212 = 0; j_inner_s_212 < 128; ++j_inner_s_212) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_212) < (width * 4)) {
          int32_t cse_var_470 = ((i_outer_2 * 128) + 84);
          ((float*)outputData_1)[((cse_var_470 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_212) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_212) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_212))) ? 0.000000e+00f : (((j_inner_s_212 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_470 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_212 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_470 * width) * 4)) + j_inner_s_212)]));
        }
      }
      for (int32_t j_inner_s_213 = 0; j_inner_s_213 < 128; ++j_inner_s_213) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_213) < (width * 4)) {
          int32_t cse_var_471 = ((i_outer_2 * 128) + 85);
          ((float*)outputData_1)[((cse_var_471 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_213) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_213) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_213))) ? 0.000000e+00f : (((j_inner_s_213 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_471 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_213 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_471 * width) * 4)) + j_inner_s_213)]));
        }
      }
      for (int32_t j_inner_s_214 = 0; j_inner_s_214 < 128; ++j_inner_s_214) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_214) < (width * 4)) {
          int32_t cse_var_472 = ((i_outer_2 * 128) + 86);
          ((float*)outputData_1)[((cse_var_472 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_214) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_214) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_214))) ? 0.000000e+00f : (((j_inner_s_214 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_472 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_214 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_472 * width) * 4)) + j_inner_s_214)]));
        }
      }
      for (int32_t j_inner_s_215 = 0; j_inner_s_215 < 128; ++j_inner_s_215) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_215) < (width * 4)) {
          int32_t cse_var_473 = ((i_outer_2 * 128) + 87);
          ((float*)outputData_1)[((cse_var_473 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_215) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_215) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_215))) ? 0.000000e+00f : (((j_inner_s_215 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_473 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_215 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_473 * width) * 4)) + j_inner_s_215)]));
        }
      }
      for (int32_t j_inner_s_216 = 0; j_inner_s_216 < 128; ++j_inner_s_216) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_216) < (width * 4)) {
          int32_t cse_var_474 = ((i_outer_2 * 128) + 88);
          ((float*)outputData_1)[((cse_var_474 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_216) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_216) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_216))) ? 0.000000e+00f : (((j_inner_s_216 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_474 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_216 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_474 * width) * 4)) + j_inner_s_216)]));
        }
      }
      for (int32_t j_inner_s_217 = 0; j_inner_s_217 < 128; ++j_inner_s_217) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_217) < (width * 4)) {
          int32_t cse_var_475 = ((i_outer_2 * 128) + 89);
          ((float*)outputData_1)[((cse_var_475 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_217) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_217) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_217))) ? 0.000000e+00f : (((j_inner_s_217 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_475 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_217 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_475 * width) * 4)) + j_inner_s_217)]));
        }
      }
      for (int32_t j_inner_s_218 = 0; j_inner_s_218 < 128; ++j_inner_s_218) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_218) < (width * 4)) {
          int32_t cse_var_476 = ((i_outer_2 * 128) + 90);
          ((float*)outputData_1)[((cse_var_476 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_218) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_218) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_218))) ? 0.000000e+00f : (((j_inner_s_218 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_476 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_218 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_476 * width) * 4)) + j_inner_s_218)]));
        }
      }
      for (int32_t j_inner_s_219 = 0; j_inner_s_219 < 128; ++j_inner_s_219) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_219) < (width * 4)) {
          int32_t cse_var_477 = ((i_outer_2 * 128) + 91);
          ((float*)outputData_1)[((cse_var_477 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_219) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_219) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_219))) ? 0.000000e+00f : (((j_inner_s_219 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_477 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_219 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_477 * width) * 4)) + j_inner_s_219)]));
        }
      }
      for (int32_t j_inner_s_220 = 0; j_inner_s_220 < 128; ++j_inner_s_220) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_220) < (width * 4)) {
          int32_t cse_var_478 = ((i_outer_2 * 128) + 92);
          ((float*)outputData_1)[((cse_var_478 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_220) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_220) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_220))) ? 0.000000e+00f : (((j_inner_s_220 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_478 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_220 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_478 * width) * 4)) + j_inner_s_220)]));
        }
      }
      for (int32_t j_inner_s_221 = 0; j_inner_s_221 < 128; ++j_inner_s_221) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_221) < (width * 4)) {
          int32_t cse_var_479 = ((i_outer_2 * 128) + 93);
          ((float*)outputData_1)[((cse_var_479 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_221) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_221) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_221))) ? 0.000000e+00f : (((j_inner_s_221 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_479 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_221 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_479 * width) * 4)) + j_inner_s_221)]));
        }
      }
      for (int32_t j_inner_s_222 = 0; j_inner_s_222 < 128; ++j_inner_s_222) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_222) < (width * 4)) {
          int32_t cse_var_480 = ((i_outer_2 * 128) + 94);
          ((float*)outputData_1)[((cse_var_480 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_222) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_222) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_222))) ? 0.000000e+00f : (((j_inner_s_222 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_480 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_222 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_480 * width) * 4)) + j_inner_s_222)]));
        }
      }
      for (int32_t j_inner_s_223 = 0; j_inner_s_223 < 128; ++j_inner_s_223) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_223) < (width * 4)) {
          int32_t cse_var_481 = ((i_outer_2 * 128) + 95);
          ((float*)outputData_1)[((cse_var_481 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_223) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_223) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_223))) ? 0.000000e+00f : (((j_inner_s_223 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_481 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_223 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_481 * width) * 4)) + j_inner_s_223)]));
        }
      }
      for (int32_t j_inner_s_224 = 0; j_inner_s_224 < 128; ++j_inner_s_224) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_224) < (width * 4)) {
          int32_t cse_var_482 = ((i_outer_2 * 128) + 96);
          ((float*)outputData_1)[((cse_var_482 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_224) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_224) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_224))) ? 0.000000e+00f : (((j_inner_s_224 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_482 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_224 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_482 * width) * 4)) + j_inner_s_224)]));
        }
      }
      for (int32_t j_inner_s_225 = 0; j_inner_s_225 < 128; ++j_inner_s_225) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_225) < (width * 4)) {
          int32_t cse_var_483 = ((i_outer_2 * 128) + 97);
          ((float*)outputData_1)[((cse_var_483 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_225) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_225) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_225))) ? 0.000000e+00f : (((j_inner_s_225 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_483 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_225 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_483 * width) * 4)) + j_inner_s_225)]));
        }
      }
      for (int32_t j_inner_s_226 = 0; j_inner_s_226 < 128; ++j_inner_s_226) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_226) < (width * 4)) {
          int32_t cse_var_484 = ((i_outer_2 * 128) + 98);
          ((float*)outputData_1)[((cse_var_484 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_226) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_226) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_226))) ? 0.000000e+00f : (((j_inner_s_226 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_484 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_226 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_484 * width) * 4)) + j_inner_s_226)]));
        }
      }
      for (int32_t j_inner_s_227 = 0; j_inner_s_227 < 128; ++j_inner_s_227) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_227) < (width * 4)) {
          int32_t cse_var_485 = ((i_outer_2 * 128) + 99);
          ((float*)outputData_1)[((cse_var_485 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_227) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_227) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_227))) ? 0.000000e+00f : (((j_inner_s_227 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_485 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_227 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_485 * width) * 4)) + j_inner_s_227)]));
        }
      }
      for (int32_t j_inner_s_228 = 0; j_inner_s_228 < 128; ++j_inner_s_228) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_228) < (width * 4)) {
          int32_t cse_var_486 = ((i_outer_2 * 128) + 100);
          ((float*)outputData_1)[((cse_var_486 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_228) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_228) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_228))) ? 0.000000e+00f : (((j_inner_s_228 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_486 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_228 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_486 * width) * 4)) + j_inner_s_228)]));
        }
      }
      for (int32_t j_inner_s_229 = 0; j_inner_s_229 < 128; ++j_inner_s_229) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_229) < (width * 4)) {
          int32_t cse_var_487 = ((i_outer_2 * 128) + 101);
          ((float*)outputData_1)[((cse_var_487 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_229) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_229) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_229))) ? 0.000000e+00f : (((j_inner_s_229 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_487 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_229 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_487 * width) * 4)) + j_inner_s_229)]));
        }
      }
      for (int32_t j_inner_s_230 = 0; j_inner_s_230 < 128; ++j_inner_s_230) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_230) < (width * 4)) {
          int32_t cse_var_488 = ((i_outer_2 * 128) + 102);
          ((float*)outputData_1)[((cse_var_488 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_230) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_230) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_230))) ? 0.000000e+00f : (((j_inner_s_230 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_488 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_230 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_488 * width) * 4)) + j_inner_s_230)]));
        }
      }
      for (int32_t j_inner_s_231 = 0; j_inner_s_231 < 128; ++j_inner_s_231) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_231) < (width * 4)) {
          int32_t cse_var_489 = ((i_outer_2 * 128) + 103);
          ((float*)outputData_1)[((cse_var_489 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_231) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_231) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_231))) ? 0.000000e+00f : (((j_inner_s_231 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_489 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_231 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_489 * width) * 4)) + j_inner_s_231)]));
        }
      }
      for (int32_t j_inner_s_232 = 0; j_inner_s_232 < 128; ++j_inner_s_232) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_232) < (width * 4)) {
          int32_t cse_var_490 = ((i_outer_2 * 128) + 104);
          ((float*)outputData_1)[((cse_var_490 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_232) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_232) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_232))) ? 0.000000e+00f : (((j_inner_s_232 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_490 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_232 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_490 * width) * 4)) + j_inner_s_232)]));
        }
      }
      for (int32_t j_inner_s_233 = 0; j_inner_s_233 < 128; ++j_inner_s_233) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_233) < (width * 4)) {
          int32_t cse_var_491 = ((i_outer_2 * 128) + 105);
          ((float*)outputData_1)[((cse_var_491 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_233) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_233) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_233))) ? 0.000000e+00f : (((j_inner_s_233 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_491 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_233 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_491 * width) * 4)) + j_inner_s_233)]));
        }
      }
      for (int32_t j_inner_s_234 = 0; j_inner_s_234 < 128; ++j_inner_s_234) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_234) < (width * 4)) {
          int32_t cse_var_492 = ((i_outer_2 * 128) + 106);
          ((float*)outputData_1)[((cse_var_492 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_234) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_234) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_234))) ? 0.000000e+00f : (((j_inner_s_234 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_492 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_234 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_492 * width) * 4)) + j_inner_s_234)]));
        }
      }
      for (int32_t j_inner_s_235 = 0; j_inner_s_235 < 128; ++j_inner_s_235) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_235) < (width * 4)) {
          int32_t cse_var_493 = ((i_outer_2 * 128) + 107);
          ((float*)outputData_1)[((cse_var_493 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_235) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_235) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_235))) ? 0.000000e+00f : (((j_inner_s_235 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_493 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_235 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_493 * width) * 4)) + j_inner_s_235)]));
        }
      }
      for (int32_t j_inner_s_236 = 0; j_inner_s_236 < 128; ++j_inner_s_236) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_236) < (width * 4)) {
          int32_t cse_var_494 = ((i_outer_2 * 128) + 108);
          ((float*)outputData_1)[((cse_var_494 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_236) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_236) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_236))) ? 0.000000e+00f : (((j_inner_s_236 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_494 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_236 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_494 * width) * 4)) + j_inner_s_236)]));
        }
      }
      for (int32_t j_inner_s_237 = 0; j_inner_s_237 < 128; ++j_inner_s_237) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_237) < (width * 4)) {
          int32_t cse_var_495 = ((i_outer_2 * 128) + 109);
          ((float*)outputData_1)[((cse_var_495 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_237) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_237) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_237))) ? 0.000000e+00f : (((j_inner_s_237 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_495 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_237 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_495 * width) * 4)) + j_inner_s_237)]));
        }
      }
      for (int32_t j_inner_s_238 = 0; j_inner_s_238 < 128; ++j_inner_s_238) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_238) < (width * 4)) {
          int32_t cse_var_496 = ((i_outer_2 * 128) + 110);
          ((float*)outputData_1)[((cse_var_496 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_238) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_238) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_238))) ? 0.000000e+00f : (((j_inner_s_238 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_496 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_238 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_496 * width) * 4)) + j_inner_s_238)]));
        }
      }
      for (int32_t j_inner_s_239 = 0; j_inner_s_239 < 128; ++j_inner_s_239) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_239) < (width * 4)) {
          int32_t cse_var_497 = ((i_outer_2 * 128) + 111);
          ((float*)outputData_1)[((cse_var_497 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_239) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_239) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_239))) ? 0.000000e+00f : (((j_inner_s_239 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_497 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_239 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_497 * width) * 4)) + j_inner_s_239)]));
        }
      }
      for (int32_t j_inner_s_240 = 0; j_inner_s_240 < 128; ++j_inner_s_240) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_240) < (width * 4)) {
          int32_t cse_var_498 = ((i_outer_2 * 128) + 112);
          ((float*)outputData_1)[((cse_var_498 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_240) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_240) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_240))) ? 0.000000e+00f : (((j_inner_s_240 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_498 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_240 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_498 * width) * 4)) + j_inner_s_240)]));
        }
      }
      for (int32_t j_inner_s_241 = 0; j_inner_s_241 < 128; ++j_inner_s_241) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_241) < (width * 4)) {
          int32_t cse_var_499 = ((i_outer_2 * 128) + 113);
          ((float*)outputData_1)[((cse_var_499 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_241) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_241) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_241))) ? 0.000000e+00f : (((j_inner_s_241 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_499 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_241 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_499 * width) * 4)) + j_inner_s_241)]));
        }
      }
      for (int32_t j_inner_s_242 = 0; j_inner_s_242 < 128; ++j_inner_s_242) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_242) < (width * 4)) {
          int32_t cse_var_500 = ((i_outer_2 * 128) + 114);
          ((float*)outputData_1)[((cse_var_500 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_242) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_242) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_242))) ? 0.000000e+00f : (((j_inner_s_242 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_500 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_242 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_500 * width) * 4)) + j_inner_s_242)]));
        }
      }
      for (int32_t j_inner_s_243 = 0; j_inner_s_243 < 128; ++j_inner_s_243) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_243) < (width * 4)) {
          int32_t cse_var_501 = ((i_outer_2 * 128) + 115);
          ((float*)outputData_1)[((cse_var_501 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_243) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_243) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_243))) ? 0.000000e+00f : (((j_inner_s_243 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_501 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_243 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_501 * width) * 4)) + j_inner_s_243)]));
        }
      }
      for (int32_t j_inner_s_244 = 0; j_inner_s_244 < 128; ++j_inner_s_244) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_244) < (width * 4)) {
          int32_t cse_var_502 = ((i_outer_2 * 128) + 116);
          ((float*)outputData_1)[((cse_var_502 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_244) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_244) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_244))) ? 0.000000e+00f : (((j_inner_s_244 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_502 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_244 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_502 * width) * 4)) + j_inner_s_244)]));
        }
      }
      for (int32_t j_inner_s_245 = 0; j_inner_s_245 < 128; ++j_inner_s_245) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_245) < (width * 4)) {
          int32_t cse_var_503 = ((i_outer_2 * 128) + 117);
          ((float*)outputData_1)[((cse_var_503 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_245) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_245) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_245))) ? 0.000000e+00f : (((j_inner_s_245 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_503 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_245 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_503 * width) * 4)) + j_inner_s_245)]));
        }
      }
      for (int32_t j_inner_s_246 = 0; j_inner_s_246 < 128; ++j_inner_s_246) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_246) < (width * 4)) {
          int32_t cse_var_504 = ((i_outer_2 * 128) + 118);
          ((float*)outputData_1)[((cse_var_504 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_246) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_246) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_246))) ? 0.000000e+00f : (((j_inner_s_246 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_504 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_246 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_504 * width) * 4)) + j_inner_s_246)]));
        }
      }
      for (int32_t j_inner_s_247 = 0; j_inner_s_247 < 128; ++j_inner_s_247) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_247) < (width * 4)) {
          int32_t cse_var_505 = ((i_outer_2 * 128) + 119);
          ((float*)outputData_1)[((cse_var_505 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_247) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_247) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_247))) ? 0.000000e+00f : (((j_inner_s_247 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_505 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_247 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_505 * width) * 4)) + j_inner_s_247)]));
        }
      }
      for (int32_t j_inner_s_248 = 0; j_inner_s_248 < 128; ++j_inner_s_248) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_248) < (width * 4)) {
          int32_t cse_var_506 = ((i_outer_2 * 128) + 120);
          ((float*)outputData_1)[((cse_var_506 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_248) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_248) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_248))) ? 0.000000e+00f : (((j_inner_s_248 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_506 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_248 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_506 * width) * 4)) + j_inner_s_248)]));
        }
      }
      for (int32_t j_inner_s_249 = 0; j_inner_s_249 < 128; ++j_inner_s_249) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_249) < (width * 4)) {
          int32_t cse_var_507 = ((i_outer_2 * 128) + 121);
          ((float*)outputData_1)[((cse_var_507 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_249) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_249) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_249))) ? 0.000000e+00f : (((j_inner_s_249 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_507 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_249 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_507 * width) * 4)) + j_inner_s_249)]));
        }
      }
      for (int32_t j_inner_s_250 = 0; j_inner_s_250 < 128; ++j_inner_s_250) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_250) < (width * 4)) {
          int32_t cse_var_508 = ((i_outer_2 * 128) + 122);
          ((float*)outputData_1)[((cse_var_508 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_250) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_250) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_250))) ? 0.000000e+00f : (((j_inner_s_250 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_508 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_250 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_508 * width) * 4)) + j_inner_s_250)]));
        }
      }
      for (int32_t j_inner_s_251 = 0; j_inner_s_251 < 128; ++j_inner_s_251) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_251) < (width * 4)) {
          int32_t cse_var_509 = ((i_outer_2 * 128) + 123);
          ((float*)outputData_1)[((cse_var_509 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_251) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_251) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_251))) ? 0.000000e+00f : (((j_inner_s_251 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_509 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_251 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_509 * width) * 4)) + j_inner_s_251)]));
        }
      }
      for (int32_t j_inner_s_252 = 0; j_inner_s_252 < 128; ++j_inner_s_252) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_252) < (width * 4)) {
          int32_t cse_var_510 = ((i_outer_2 * 128) + 124);
          ((float*)outputData_1)[((cse_var_510 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_252) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_252) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_252))) ? 0.000000e+00f : (((j_inner_s_252 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_510 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_252 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_510 * width) * 4)) + j_inner_s_252)]));
        }
      }
      for (int32_t j_inner_s_253 = 0; j_inner_s_253 < 128; ++j_inner_s_253) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_253) < (width * 4)) {
          int32_t cse_var_511 = ((i_outer_2 * 128) + 125);
          ((float*)outputData_1)[((cse_var_511 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_253) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_253) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_253))) ? 0.000000e+00f : (((j_inner_s_253 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_511 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_253 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_511 * width) * 4)) + j_inner_s_253)]));
        }
      }
      for (int32_t j_inner_s_254 = 0; j_inner_s_254 < 128; ++j_inner_s_254) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_254) < (width * 4)) {
          int32_t cse_var_512 = ((i_outer_2 * 128) + 126);
          ((float*)outputData_1)[((cse_var_512 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_254) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_254) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_254))) ? 0.000000e+00f : (((j_inner_s_254 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_512 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_254 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_512 * width) * 4)) + j_inner_s_254)]));
        }
      }
      for (int32_t j_inner_s_255 = 0; j_inner_s_255 < 128; ++j_inner_s_255) {
        if (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_255) < (width * 4)) {
          int32_t cse_var_513 = ((i_outer_2 * 128) + 127);
          ((float*)outputData_1)[((cse_var_513 * stride_4) + (((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_255) * stride_3))] = (((((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_255) < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= ((((width >> 5) * 128) + (j_outer_4 * 128)) + j_inner_s_255))) ? 0.000000e+00f : (((j_inner_s_255 % 4) == 0) ? ((float*)derivativeData_1)[((cse_var_513 * stride_1) + (((((width >> 5) * 32) + (j_outer_4 * 32)) + (j_inner_s_255 >> 2)) * stride))] : ((float*)upsamplingData)[(((((width >> 5) * 128) + (j_outer_4 * 128)) + ((cse_var_513 * width) * 4)) + j_inner_s_255)]));
        }
      }
    }
  }
  int32_t v__213 = (height - 127) >> 7;
  int32_t v__214 = (height >> 7) - 1;
  int32_t v__215 = (v__213) < (v__214) ? (v__213) : (v__214);
  int32_t v__216 = (height - 113) >> 7;
  int32_t v__217 = (v__215) < (v__216) ? (v__215) : (v__216);
  int32_t v__218 = (height - 95) >> 7;
  int32_t v__219 = (v__217) < (v__218) ? (v__217) : (v__218);
  int32_t v__220 = (height - 102) >> 7;
  int32_t v__221 = (v__219) < (v__220) ? (v__219) : (v__220);
  int32_t v__222 = (height - 97) >> 7;
  int32_t v__223 = (v__221) < (v__222) ? (v__221) : (v__222);
  int32_t v__224 = (height - 71) >> 7;
  int32_t v__225 = (v__223) < (v__224) ? (v__223) : (v__224);
  int32_t v__226 = (height - 69) >> 7;
  int32_t v__227 = (v__225) < (v__226) ? (v__225) : (v__226);
  int32_t v__228 = (height - 68) >> 7;
  int32_t v__229 = (v__227) < (v__228) ? (v__227) : (v__228);
  int32_t v__230 = (height - 67) >> 7;
  int32_t v__231 = (v__229) < (v__230) ? (v__229) : (v__230);
  int32_t v__232 = (height - 30) >> 7;
  int32_t v__233 = (v__231) < (v__232) ? (v__231) : (v__232);
  int32_t v__234 = (height - 6) >> 7;
  int32_t v__235 = (v__233) < (v__234) ? (v__233) : (v__234);
  int32_t v__236 = (height - 21) >> 7;
  int32_t v__237 = (v__235) < (v__236) ? (v__235) : (v__236);
  int32_t v__238 = (height - 44) >> 7;
  int32_t v__239 = (v__237) < (v__238) ? (v__237) : (v__238);
  int32_t v__240 = (height - 17) >> 7;
  int32_t v__241 = (v__239) < (v__240) ? (v__239) : (v__240);
  int32_t v__242 = (height - 20) >> 7;
  int32_t v__243 = (v__241) < (v__242) ? (v__241) : (v__242);
  int32_t v__244 = (height - 25) >> 7;
  int32_t v__245 = (v__243) < (v__244) ? (v__243) : (v__244);
  int32_t v__246 = (height - 66) >> 7;
  int32_t v__247 = (v__245) < (v__246) ? (v__245) : (v__246);
  int32_t v__248 = (height - 19) >> 7;
  int32_t v__249 = (v__247) < (v__248) ? (v__247) : (v__248);
  int32_t v__250 = (height - 56) >> 7;
  int32_t v__251 = (v__249) < (v__250) ? (v__249) : (v__250);
  int32_t v__252 = (height - 18) >> 7;
  int32_t v__253 = (v__251) < (v__252) ? (v__251) : (v__252);
  int32_t v__254 = (height - 75) >> 7;
  int32_t v__255 = (v__253) < (v__254) ? (v__253) : (v__254);
  int32_t v__256 = (height - 40) >> 7;
  int32_t v__257 = (v__255) < (v__256) ? (v__255) : (v__256);
  int32_t v__258 = (height - 96) >> 7;
  int32_t v__259 = (v__257) < (v__258) ? (v__257) : (v__258);
  int32_t v__260 = (height - 16) >> 7;
  int32_t v__261 = (v__259) < (v__260) ? (v__259) : (v__260);
  int32_t v__262 = (height - 117) >> 7;
  int32_t v__263 = (v__261) < (v__262) ? (v__261) : (v__262);
  int32_t v__264 = (height - 60) >> 7;
  int32_t v__265 = (v__263) < (v__264) ? (v__263) : (v__264);
  int32_t v__266 = (height - 24) >> 7;
  int32_t v__267 = (v__265) < (v__266) ? (v__265) : (v__266);
  int32_t v__268 = (height - 38) >> 7;
  int32_t v__269 = (v__267) < (v__268) ? (v__267) : (v__268);
  int32_t v__270 = (height - 90) >> 7;
  int32_t v__271 = (v__269) < (v__270) ? (v__269) : (v__270);
  int32_t v__272 = (height - 23) >> 7;
  int32_t v__273 = (v__271) < (v__272) ? (v__271) : (v__272);
  int32_t v__274 = (height - 53) >> 7;
  int32_t v__275 = (v__273) < (v__274) ? (v__273) : (v__274);
  int32_t v__276 = (height - 65) >> 7;
  int32_t v__277 = (v__275) < (v__276) ? (v__275) : (v__276);
  int32_t v__278 = (height - 1) >> 7;
  int32_t v__279 = (v__277) < (v__278) ? (v__277) : (v__278);
  int32_t v__280 = (height - 70) >> 7;
  int32_t v__281 = (v__279) < (v__280) ? (v__279) : (v__280);
  int32_t v__282 = (height - 34) >> 7;
  int32_t v__283 = (v__281) < (v__282) ? (v__281) : (v__282);
  int32_t v__284 = (height - 101) >> 7;
  int32_t v__285 = (v__283) < (v__284) ? (v__283) : (v__284);
  int32_t v__286 = (height - 55) >> 7;
  int32_t v__287 = (v__285) < (v__286) ? (v__285) : (v__286);
  int32_t v__288 = (height - 57) >> 7;
  int32_t v__289 = (v__287) < (v__288) ? (v__287) : (v__288);
  int32_t v__290 = (height - 27) >> 7;
  int32_t v__291 = (v__289) < (v__290) ? (v__289) : (v__290);
  int32_t v__292 = (height - 108) >> 7;
  int32_t v__293 = (v__291) < (v__292) ? (v__291) : (v__292);
  int32_t v__294 = (height - 85) >> 7;
  int32_t v__295 = (v__293) < (v__294) ? (v__293) : (v__294);
  int32_t v__296 = (height - 3) >> 7;
  int32_t v__297 = (v__295) < (v__296) ? (v__295) : (v__296);
  int32_t v__298 = (height - 14) >> 7;
  int32_t v__299 = (v__297) < (v__298) ? (v__297) : (v__298);
  int32_t v__300 = (height - 109) >> 7;
  int32_t v__301 = (v__299) < (v__300) ? (v__299) : (v__300);
  int32_t v__302 = (height - 63) >> 7;
  int32_t v__303 = (v__301) < (v__302) ? (v__301) : (v__302);
  int32_t v__304 = (height - 28) >> 7;
  int32_t v__305 = (v__303) < (v__304) ? (v__303) : (v__304);
  int32_t v__306 = (height - 54) >> 7;
  int32_t v__307 = (v__305) < (v__306) ? (v__305) : (v__306);
  int32_t v__308 = (height - 15) >> 7;
  int32_t v__309 = (v__307) < (v__308) ? (v__307) : (v__308);
  int32_t v__310 = (height - 29) >> 7;
  int32_t v__311 = (v__309) < (v__310) ? (v__309) : (v__310);
  int32_t v__312 = (height - 36) >> 7;
  int32_t v__313 = (v__311) < (v__312) ? (v__311) : (v__312);
  int32_t v__314 = (height - 12) >> 7;
  int32_t v__315 = (v__313) < (v__314) ? (v__313) : (v__314);
  int32_t v__316 = (height - 119) >> 7;
  int32_t v__317 = (v__315) < (v__316) ? (v__315) : (v__316);
  int32_t v__318 = (height - 13) >> 7;
  int32_t v__319 = (v__317) < (v__318) ? (v__317) : (v__318);
  int32_t v__320 = (height - 77) >> 7;
  int32_t v__321 = (v__319) < (v__320) ? (v__319) : (v__320);
  int32_t v__322 = (height - 7) >> 7;
  int32_t v__323 = (v__321) < (v__322) ? (v__321) : (v__322);
  int32_t v__324 = (height - 120) >> 7;
  int32_t v__325 = (v__323) < (v__324) ? (v__323) : (v__324);
  int32_t v__326 = (height - 118) >> 7;
  int32_t v__327 = (v__325) < (v__326) ? (v__325) : (v__326);
  int32_t v__328 = (height - 8) >> 7;
  int32_t v__329 = (v__327) < (v__328) ? (v__327) : (v__328);
  int32_t v__330 = (height - 64) >> 7;
  int32_t v__331 = (v__329) < (v__330) ? (v__329) : (v__330);
  int32_t v__332 = (height - 42) >> 7;
  int32_t v__333 = (v__331) < (v__332) ? (v__331) : (v__332);
  int32_t v__334 = (height - 37) >> 7;
  int32_t v__335 = (v__333) < (v__334) ? (v__333) : (v__334);
  int32_t v__336 = (height - 99) >> 7;
  int32_t v__337 = (v__335) < (v__336) ? (v__335) : (v__336);
  int32_t v__338 = (height - 5) >> 7;
  int32_t v__339 = (v__337) < (v__338) ? (v__337) : (v__338);
  int32_t v__340 = (height - 31) >> 7;
  int32_t v__341 = (v__339) < (v__340) ? (v__339) : (v__340);
  int32_t v__342 = (height - 92) >> 7;
  int32_t v__343 = (v__341) < (v__342) ? (v__341) : (v__342);
  int32_t v__344 = (height - 47) >> 7;
  int32_t v__345 = (v__343) < (v__344) ? (v__343) : (v__344);
  int32_t v__346 = (height - 32) >> 7;
  int32_t v__347 = (v__345) < (v__346) ? (v__345) : (v__346);
  int32_t v__348 = (height - 91) >> 7;
  int32_t v__349 = (v__347) < (v__348) ? (v__347) : (v__348);
  int32_t v__350 = (height - 80) >> 7;
  int32_t v__351 = (v__349) < (v__350) ? (v__349) : (v__350);
  int32_t v__352 = (height - 33) >> 7;
  int32_t v__353 = (v__351) < (v__352) ? (v__351) : (v__352);
  int32_t v__354 = (height - 39) >> 7;
  int32_t v__355 = (v__353) < (v__354) ? (v__353) : (v__354);
  int32_t v__356 = (height - 41) >> 7;
  int32_t v__357 = (v__355) < (v__356) ? (v__355) : (v__356);
  int32_t v__358 = (height - 26) >> 7;
  int32_t v__359 = (v__357) < (v__358) ? (v__357) : (v__358);
  int32_t v__360 = (height - 107) >> 7;
  int32_t v__361 = (v__359) < (v__360) ? (v__359) : (v__360);
  int32_t v__362 = (height - 4) >> 7;
  int32_t v__363 = (v__361) < (v__362) ? (v__361) : (v__362);
  int32_t v__364 = (height - 9) >> 7;
  int32_t v__365 = (v__363) < (v__364) ? (v__363) : (v__364);
  int32_t v__366 = (height - 43) >> 7;
  int32_t v__367 = (v__365) < (v__366) ? (v__365) : (v__366);
  int32_t v__368 = (height - 46) >> 7;
  int32_t v__369 = (v__367) < (v__368) ? (v__367) : (v__368);
  int32_t v__370 = (height - 45) >> 7;
  int32_t v__371 = (v__369) < (v__370) ? (v__369) : (v__370);
  int32_t v__372 = (height - 22) >> 7;
  int32_t v__373 = (v__371) < (v__372) ? (v__371) : (v__372);
  int32_t v__374 = (height - 123) >> 7;
  int32_t v__375 = (v__373) < (v__374) ? (v__373) : (v__374);
  int32_t v__376 = (height - 51) >> 7;
  int32_t v__377 = (v__375) < (v__376) ? (v__375) : (v__376);
  int32_t v__378 = (height - 98) >> 7;
  int32_t v__379 = (v__377) < (v__378) ? (v__377) : (v__378);
  int32_t v__380 = (height - 114) >> 7;
  int32_t v__381 = (v__379) < (v__380) ? (v__379) : (v__380);
  int32_t v__382 = (height - 48) >> 7;
  int32_t v__383 = (v__381) < (v__382) ? (v__381) : (v__382);
  int32_t v__384 = (height - 122) >> 7;
  int32_t v__385 = (v__383) < (v__384) ? (v__383) : (v__384);
  int32_t v__386 = (height - 62) >> 7;
  int32_t v__387 = (v__385) < (v__386) ? (v__385) : (v__386);
  int32_t v__388 = (height - 35) >> 7;
  int32_t v__389 = (v__387) < (v__388) ? (v__387) : (v__388);
  int32_t v__390 = (height - 49) >> 7;
  int32_t v__391 = (v__389) < (v__390) ? (v__389) : (v__390);
  int32_t v__392 = (height - 50) >> 7;
  int32_t v__393 = (v__391) < (v__392) ? (v__391) : (v__392);
  int32_t v__394 = (height - 2) >> 7;
  int32_t v__395 = (v__393) < (v__394) ? (v__393) : (v__394);
  int32_t v__396 = (height - 10) >> 7;
  int32_t v__397 = (v__395) < (v__396) ? (v__395) : (v__396);
  int32_t v__398 = (height - 52) >> 7;
  int32_t v__399 = (v__397) < (v__398) ? (v__397) : (v__398);
  int32_t v__400 = (height - 58) >> 7;
  int32_t v__401 = (v__399) < (v__400) ? (v__399) : (v__400);
  int32_t v__402 = (height - 121) >> 7;
  int32_t v__403 = (v__401) < (v__402) ? (v__401) : (v__402);
  int32_t v__404 = (height - 59) >> 7;
  int32_t v__405 = (v__403) < (v__404) ? (v__403) : (v__404);
  int32_t v__406 = (height - 11) >> 7;
  int32_t v__407 = (v__405) < (v__406) ? (v__405) : (v__406);
  int32_t v__408 = (height - 61) >> 7;
  for (int32_t i_outer_3 = 0; i_outer_3 < ((((height + 127) >> 7) - ((v__407) < (v__408) ? (v__407) : (v__408))) - 1); ++i_outer_3) {
    for (int32_t j_outer_5 = 0; j_outer_5 < ((width + 31) >> 5); ++j_outer_5) {
      int32_t v__409 = (height - 127) >> 7;
      int32_t v__410 = (height >> 7) - 1;
      int32_t v__411 = (v__409) < (v__410) ? (v__409) : (v__410);
      int32_t v__412 = (height - 113) >> 7;
      int32_t v__413 = (v__411) < (v__412) ? (v__411) : (v__412);
      int32_t v__414 = (height - 95) >> 7;
      int32_t v__415 = (v__413) < (v__414) ? (v__413) : (v__414);
      int32_t v__416 = (height - 102) >> 7;
      int32_t v__417 = (v__415) < (v__416) ? (v__415) : (v__416);
      int32_t v__418 = (height - 97) >> 7;
      int32_t v__419 = (v__417) < (v__418) ? (v__417) : (v__418);
      int32_t v__420 = (height - 71) >> 7;
      int32_t v__421 = (v__419) < (v__420) ? (v__419) : (v__420);
      int32_t v__422 = (height - 69) >> 7;
      int32_t v__423 = (v__421) < (v__422) ? (v__421) : (v__422);
      int32_t v__424 = (height - 68) >> 7;
      int32_t v__425 = (v__423) < (v__424) ? (v__423) : (v__424);
      int32_t v__426 = (height - 67) >> 7;
      int32_t v__427 = (v__425) < (v__426) ? (v__425) : (v__426);
      int32_t v__428 = (height - 30) >> 7;
      int32_t v__429 = (v__427) < (v__428) ? (v__427) : (v__428);
      int32_t v__430 = (height - 6) >> 7;
      int32_t v__431 = (v__429) < (v__430) ? (v__429) : (v__430);
      int32_t v__432 = (height - 21) >> 7;
      int32_t v__433 = (v__431) < (v__432) ? (v__431) : (v__432);
      int32_t v__434 = (height - 44) >> 7;
      int32_t v__435 = (v__433) < (v__434) ? (v__433) : (v__434);
      int32_t v__436 = (height - 17) >> 7;
      int32_t v__437 = (v__435) < (v__436) ? (v__435) : (v__436);
      int32_t v__438 = (height - 20) >> 7;
      int32_t v__439 = (v__437) < (v__438) ? (v__437) : (v__438);
      int32_t v__440 = (height - 25) >> 7;
      int32_t v__441 = (v__439) < (v__440) ? (v__439) : (v__440);
      int32_t v__442 = (height - 66) >> 7;
      int32_t v__443 = (v__441) < (v__442) ? (v__441) : (v__442);
      int32_t v__444 = (height - 19) >> 7;
      int32_t v__445 = (v__443) < (v__444) ? (v__443) : (v__444);
      int32_t v__446 = (height - 56) >> 7;
      int32_t v__447 = (v__445) < (v__446) ? (v__445) : (v__446);
      int32_t v__448 = (height - 18) >> 7;
      int32_t v__449 = (v__447) < (v__448) ? (v__447) : (v__448);
      int32_t v__450 = (height - 75) >> 7;
      int32_t v__451 = (v__449) < (v__450) ? (v__449) : (v__450);
      int32_t v__452 = (height - 40) >> 7;
      int32_t v__453 = (v__451) < (v__452) ? (v__451) : (v__452);
      int32_t v__454 = (height - 96) >> 7;
      int32_t v__455 = (v__453) < (v__454) ? (v__453) : (v__454);
      int32_t v__456 = (height - 16) >> 7;
      int32_t v__457 = (v__455) < (v__456) ? (v__455) : (v__456);
      int32_t v__458 = (height - 117) >> 7;
      int32_t v__459 = (v__457) < (v__458) ? (v__457) : (v__458);
      int32_t v__460 = (height - 60) >> 7;
      int32_t v__461 = (v__459) < (v__460) ? (v__459) : (v__460);
      int32_t v__462 = (height - 24) >> 7;
      int32_t v__463 = (v__461) < (v__462) ? (v__461) : (v__462);
      int32_t v__464 = (height - 38) >> 7;
      int32_t v__465 = (v__463) < (v__464) ? (v__463) : (v__464);
      int32_t v__466 = (height - 90) >> 7;
      int32_t v__467 = (v__465) < (v__466) ? (v__465) : (v__466);
      int32_t v__468 = (height - 23) >> 7;
      int32_t v__469 = (v__467) < (v__468) ? (v__467) : (v__468);
      int32_t v__470 = (height - 53) >> 7;
      int32_t v__471 = (v__469) < (v__470) ? (v__469) : (v__470);
      int32_t v__472 = (height - 65) >> 7;
      int32_t v__473 = (v__471) < (v__472) ? (v__471) : (v__472);
      int32_t v__474 = (height - 1) >> 7;
      int32_t v__475 = (v__473) < (v__474) ? (v__473) : (v__474);
      int32_t v__476 = (height - 70) >> 7;
      int32_t v__477 = (v__475) < (v__476) ? (v__475) : (v__476);
      int32_t v__478 = (height - 34) >> 7;
      int32_t v__479 = (v__477) < (v__478) ? (v__477) : (v__478);
      int32_t v__480 = (height - 101) >> 7;
      int32_t v__481 = (v__479) < (v__480) ? (v__479) : (v__480);
      int32_t v__482 = (height - 55) >> 7;
      int32_t v__483 = (v__481) < (v__482) ? (v__481) : (v__482);
      int32_t v__484 = (height - 57) >> 7;
      int32_t v__485 = (v__483) < (v__484) ? (v__483) : (v__484);
      int32_t v__486 = (height - 27) >> 7;
      int32_t v__487 = (v__485) < (v__486) ? (v__485) : (v__486);
      int32_t v__488 = (height - 108) >> 7;
      int32_t v__489 = (v__487) < (v__488) ? (v__487) : (v__488);
      int32_t v__490 = (height - 85) >> 7;
      int32_t v__491 = (v__489) < (v__490) ? (v__489) : (v__490);
      int32_t v__492 = (height - 3) >> 7;
      int32_t v__493 = (v__491) < (v__492) ? (v__491) : (v__492);
      int32_t v__494 = (height - 14) >> 7;
      int32_t v__495 = (v__493) < (v__494) ? (v__493) : (v__494);
      int32_t v__496 = (height - 109) >> 7;
      int32_t v__497 = (v__495) < (v__496) ? (v__495) : (v__496);
      int32_t v__498 = (height - 63) >> 7;
      int32_t v__499 = (v__497) < (v__498) ? (v__497) : (v__498);
      int32_t v__500 = (height - 28) >> 7;
      int32_t v__501 = (v__499) < (v__500) ? (v__499) : (v__500);
      int32_t v__502 = (height - 54) >> 7;
      int32_t v__503 = (v__501) < (v__502) ? (v__501) : (v__502);
      int32_t v__504 = (height - 15) >> 7;
      int32_t v__505 = (v__503) < (v__504) ? (v__503) : (v__504);
      int32_t v__506 = (height - 29) >> 7;
      int32_t v__507 = (v__505) < (v__506) ? (v__505) : (v__506);
      int32_t v__508 = (height - 36) >> 7;
      int32_t v__509 = (v__507) < (v__508) ? (v__507) : (v__508);
      int32_t v__510 = (height - 12) >> 7;
      int32_t v__511 = (v__509) < (v__510) ? (v__509) : (v__510);
      int32_t v__512 = (height - 119) >> 7;
      int32_t v__513 = (v__511) < (v__512) ? (v__511) : (v__512);
      int32_t v__514 = (height - 13) >> 7;
      int32_t v__515 = (v__513) < (v__514) ? (v__513) : (v__514);
      int32_t v__516 = (height - 77) >> 7;
      int32_t v__517 = (v__515) < (v__516) ? (v__515) : (v__516);
      int32_t v__518 = (height - 7) >> 7;
      int32_t v__519 = (v__517) < (v__518) ? (v__517) : (v__518);
      int32_t v__520 = (height - 120) >> 7;
      int32_t v__521 = (v__519) < (v__520) ? (v__519) : (v__520);
      int32_t v__522 = (height - 118) >> 7;
      int32_t v__523 = (v__521) < (v__522) ? (v__521) : (v__522);
      int32_t v__524 = (height - 8) >> 7;
      int32_t v__525 = (v__523) < (v__524) ? (v__523) : (v__524);
      int32_t v__526 = (height - 64) >> 7;
      int32_t v__527 = (v__525) < (v__526) ? (v__525) : (v__526);
      int32_t v__528 = (height - 42) >> 7;
      int32_t v__529 = (v__527) < (v__528) ? (v__527) : (v__528);
      int32_t v__530 = (height - 37) >> 7;
      int32_t v__531 = (v__529) < (v__530) ? (v__529) : (v__530);
      int32_t v__532 = (height - 99) >> 7;
      int32_t v__533 = (v__531) < (v__532) ? (v__531) : (v__532);
      int32_t v__534 = (height - 5) >> 7;
      int32_t v__535 = (v__533) < (v__534) ? (v__533) : (v__534);
      int32_t v__536 = (height - 31) >> 7;
      int32_t v__537 = (v__535) < (v__536) ? (v__535) : (v__536);
      int32_t v__538 = (height - 92) >> 7;
      int32_t v__539 = (v__537) < (v__538) ? (v__537) : (v__538);
      int32_t v__540 = (height - 47) >> 7;
      int32_t v__541 = (v__539) < (v__540) ? (v__539) : (v__540);
      int32_t v__542 = (height - 32) >> 7;
      int32_t v__543 = (v__541) < (v__542) ? (v__541) : (v__542);
      int32_t v__544 = (height - 91) >> 7;
      int32_t v__545 = (v__543) < (v__544) ? (v__543) : (v__544);
      int32_t v__546 = (height - 80) >> 7;
      int32_t v__547 = (v__545) < (v__546) ? (v__545) : (v__546);
      int32_t v__548 = (height - 33) >> 7;
      int32_t v__549 = (v__547) < (v__548) ? (v__547) : (v__548);
      int32_t v__550 = (height - 39) >> 7;
      int32_t v__551 = (v__549) < (v__550) ? (v__549) : (v__550);
      int32_t v__552 = (height - 41) >> 7;
      int32_t v__553 = (v__551) < (v__552) ? (v__551) : (v__552);
      int32_t v__554 = (height - 26) >> 7;
      int32_t v__555 = (v__553) < (v__554) ? (v__553) : (v__554);
      int32_t v__556 = (height - 107) >> 7;
      int32_t v__557 = (v__555) < (v__556) ? (v__555) : (v__556);
      int32_t v__558 = (height - 4) >> 7;
      int32_t v__559 = (v__557) < (v__558) ? (v__557) : (v__558);
      int32_t v__560 = (height - 9) >> 7;
      int32_t v__561 = (v__559) < (v__560) ? (v__559) : (v__560);
      int32_t v__562 = (height - 43) >> 7;
      int32_t v__563 = (v__561) < (v__562) ? (v__561) : (v__562);
      int32_t v__564 = (height - 46) >> 7;
      int32_t v__565 = (v__563) < (v__564) ? (v__563) : (v__564);
      int32_t v__566 = (height - 45) >> 7;
      int32_t v__567 = (v__565) < (v__566) ? (v__565) : (v__566);
      int32_t v__568 = (height - 22) >> 7;
      int32_t v__569 = (v__567) < (v__568) ? (v__567) : (v__568);
      int32_t v__570 = (height - 123) >> 7;
      int32_t v__571 = (v__569) < (v__570) ? (v__569) : (v__570);
      int32_t v__572 = (height - 51) >> 7;
      int32_t v__573 = (v__571) < (v__572) ? (v__571) : (v__572);
      int32_t v__574 = (height - 98) >> 7;
      int32_t v__575 = (v__573) < (v__574) ? (v__573) : (v__574);
      int32_t v__576 = (height - 114) >> 7;
      int32_t v__577 = (v__575) < (v__576) ? (v__575) : (v__576);
      int32_t v__578 = (height - 48) >> 7;
      int32_t v__579 = (v__577) < (v__578) ? (v__577) : (v__578);
      int32_t v__580 = (height - 122) >> 7;
      int32_t v__581 = (v__579) < (v__580) ? (v__579) : (v__580);
      int32_t v__582 = (height - 62) >> 7;
      int32_t v__583 = (v__581) < (v__582) ? (v__581) : (v__582);
      int32_t v__584 = (height - 35) >> 7;
      int32_t v__585 = (v__583) < (v__584) ? (v__583) : (v__584);
      int32_t v__586 = (height - 49) >> 7;
      int32_t v__587 = (v__585) < (v__586) ? (v__585) : (v__586);
      int32_t v__588 = (height - 50) >> 7;
      int32_t v__589 = (v__587) < (v__588) ? (v__587) : (v__588);
      int32_t v__590 = (height - 2) >> 7;
      int32_t v__591 = (v__589) < (v__590) ? (v__589) : (v__590);
      int32_t v__592 = (height - 10) >> 7;
      int32_t v__593 = (v__591) < (v__592) ? (v__591) : (v__592);
      int32_t v__594 = (height - 52) >> 7;
      int32_t v__595 = (v__593) < (v__594) ? (v__593) : (v__594);
      int32_t v__596 = (height - 58) >> 7;
      int32_t v__597 = (v__595) < (v__596) ? (v__595) : (v__596);
      int32_t v__598 = (height - 121) >> 7;
      int32_t v__599 = (v__597) < (v__598) ? (v__597) : (v__598);
      int32_t v__600 = (height - 59) >> 7;
      int32_t v__601 = (v__599) < (v__600) ? (v__599) : (v__600);
      int32_t v__602 = (height - 11) >> 7;
      int32_t v__603 = (v__601) < (v__602) ? (v__601) : (v__602);
      int32_t v__604 = (height - 61) >> 7;
      int32_t v__605 = ((v__603) < (v__604) ? (v__603) : (v__604)) + 1;
      int32_t v__606 = (height + 127) >> 7;
      if (((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) < height) {
        for (int32_t j_inner_s_256 = 0; j_inner_s_256 < 128; ++j_inner_s_256) {
          if (((j_outer_5 * 128) + j_inner_s_256) < (width * 4)) {
            int32_t cse_var_515 = (j_outer_5 * 128);
            int32_t cse_var_514 = (cse_var_515 + j_inner_s_256);
            ((float*)outputData_1)[((((((v__605) < (v__606) ? (v__605) : (v__606)) + i_outer_3) * stride_4) * 128) + (cse_var_514 * stride_3))] = (((cse_var_514 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_514)) ? 0.000000e+00f : (((j_inner_s_256 % 4) == 0) ? ((float*)derivativeData_1)[((((((v__605) < (v__606) ? (v__605) : (v__606)) + i_outer_3) * stride_1) * 128) + (((j_outer_5 * 32) + (j_inner_s_256 >> 2)) * stride))] : ((float*)upsamplingData)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) + i_outer_3) * width) * 512) + cse_var_515) + j_inner_s_256)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 1) < height) {
        for (int32_t j_inner_s_257 = 0; j_inner_s_257 < 128; ++j_inner_s_257) {
          if (((j_outer_5 * 128) + j_inner_s_257) < (width * 4)) {
            int32_t cse_var_517 = (j_outer_5 * 128);
            int32_t cse_var_516 = (cse_var_517 + j_inner_s_257);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 1) * stride_4) + (cse_var_516 * stride_3))] = (((cse_var_516 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_516)) ? 0.000000e+00f : (((j_inner_s_257 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 1) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_257 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_517 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 1) * width) * 4)) + j_inner_s_257)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 2) < height) {
        for (int32_t j_inner_s_258 = 0; j_inner_s_258 < 128; ++j_inner_s_258) {
          if (((j_outer_5 * 128) + j_inner_s_258) < (width * 4)) {
            int32_t cse_var_519 = (j_outer_5 * 128);
            int32_t cse_var_518 = (cse_var_519 + j_inner_s_258);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 2) * stride_4) + (cse_var_518 * stride_3))] = (((cse_var_518 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_518)) ? 0.000000e+00f : (((j_inner_s_258 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 2) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_258 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_519 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 2) * width) * 4)) + j_inner_s_258)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 3) < height) {
        for (int32_t j_inner_s_259 = 0; j_inner_s_259 < 128; ++j_inner_s_259) {
          if (((j_outer_5 * 128) + j_inner_s_259) < (width * 4)) {
            int32_t cse_var_521 = (j_outer_5 * 128);
            int32_t cse_var_520 = (cse_var_521 + j_inner_s_259);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 3) * stride_4) + (cse_var_520 * stride_3))] = (((cse_var_520 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_520)) ? 0.000000e+00f : (((j_inner_s_259 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 3) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_259 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_521 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 3) * width) * 4)) + j_inner_s_259)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 4) < height) {
        for (int32_t j_inner_s_260 = 0; j_inner_s_260 < 128; ++j_inner_s_260) {
          if (((j_outer_5 * 128) + j_inner_s_260) < (width * 4)) {
            int32_t cse_var_523 = (j_outer_5 * 128);
            int32_t cse_var_522 = (cse_var_523 + j_inner_s_260);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 4) * stride_4) + (cse_var_522 * stride_3))] = (((cse_var_522 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_522)) ? 0.000000e+00f : (((j_inner_s_260 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 4) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_260 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_523 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 4) * width) * 4)) + j_inner_s_260)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 5) < height) {
        for (int32_t j_inner_s_261 = 0; j_inner_s_261 < 128; ++j_inner_s_261) {
          if (((j_outer_5 * 128) + j_inner_s_261) < (width * 4)) {
            int32_t cse_var_525 = (j_outer_5 * 128);
            int32_t cse_var_524 = (cse_var_525 + j_inner_s_261);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 5) * stride_4) + (cse_var_524 * stride_3))] = (((cse_var_524 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_524)) ? 0.000000e+00f : (((j_inner_s_261 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 5) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_261 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_525 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 5) * width) * 4)) + j_inner_s_261)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 6) < height) {
        for (int32_t j_inner_s_262 = 0; j_inner_s_262 < 128; ++j_inner_s_262) {
          if (((j_outer_5 * 128) + j_inner_s_262) < (width * 4)) {
            int32_t cse_var_527 = (j_outer_5 * 128);
            int32_t cse_var_526 = (cse_var_527 + j_inner_s_262);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 6) * stride_4) + (cse_var_526 * stride_3))] = (((cse_var_526 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_526)) ? 0.000000e+00f : (((j_inner_s_262 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 6) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_262 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_527 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 6) * width) * 4)) + j_inner_s_262)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 7) < height) {
        for (int32_t j_inner_s_263 = 0; j_inner_s_263 < 128; ++j_inner_s_263) {
          if (((j_outer_5 * 128) + j_inner_s_263) < (width * 4)) {
            int32_t cse_var_529 = (j_outer_5 * 128);
            int32_t cse_var_528 = (cse_var_529 + j_inner_s_263);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 7) * stride_4) + (cse_var_528 * stride_3))] = (((cse_var_528 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_528)) ? 0.000000e+00f : (((j_inner_s_263 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 7) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_263 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_529 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 7) * width) * 4)) + j_inner_s_263)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 8) < height) {
        for (int32_t j_inner_s_264 = 0; j_inner_s_264 < 128; ++j_inner_s_264) {
          if (((j_outer_5 * 128) + j_inner_s_264) < (width * 4)) {
            int32_t cse_var_531 = (j_outer_5 * 128);
            int32_t cse_var_530 = (cse_var_531 + j_inner_s_264);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 8) * stride_4) + (cse_var_530 * stride_3))] = (((cse_var_530 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_530)) ? 0.000000e+00f : (((j_inner_s_264 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 8) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_264 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_531 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 8) * width) * 4)) + j_inner_s_264)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 9) < height) {
        for (int32_t j_inner_s_265 = 0; j_inner_s_265 < 128; ++j_inner_s_265) {
          if (((j_outer_5 * 128) + j_inner_s_265) < (width * 4)) {
            int32_t cse_var_533 = (j_outer_5 * 128);
            int32_t cse_var_532 = (cse_var_533 + j_inner_s_265);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 9) * stride_4) + (cse_var_532 * stride_3))] = (((cse_var_532 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_532)) ? 0.000000e+00f : (((j_inner_s_265 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 9) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_265 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_533 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 9) * width) * 4)) + j_inner_s_265)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 10) < height) {
        for (int32_t j_inner_s_266 = 0; j_inner_s_266 < 128; ++j_inner_s_266) {
          if (((j_outer_5 * 128) + j_inner_s_266) < (width * 4)) {
            int32_t cse_var_535 = (j_outer_5 * 128);
            int32_t cse_var_534 = (cse_var_535 + j_inner_s_266);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 10) * stride_4) + (cse_var_534 * stride_3))] = (((cse_var_534 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_534)) ? 0.000000e+00f : (((j_inner_s_266 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 10) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_266 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_535 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 10) * width) * 4)) + j_inner_s_266)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 11) < height) {
        for (int32_t j_inner_s_267 = 0; j_inner_s_267 < 128; ++j_inner_s_267) {
          if (((j_outer_5 * 128) + j_inner_s_267) < (width * 4)) {
            int32_t cse_var_537 = (j_outer_5 * 128);
            int32_t cse_var_536 = (cse_var_537 + j_inner_s_267);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 11) * stride_4) + (cse_var_536 * stride_3))] = (((cse_var_536 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_536)) ? 0.000000e+00f : (((j_inner_s_267 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 11) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_267 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_537 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 11) * width) * 4)) + j_inner_s_267)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 12) < height) {
        for (int32_t j_inner_s_268 = 0; j_inner_s_268 < 128; ++j_inner_s_268) {
          if (((j_outer_5 * 128) + j_inner_s_268) < (width * 4)) {
            int32_t cse_var_539 = (j_outer_5 * 128);
            int32_t cse_var_538 = (cse_var_539 + j_inner_s_268);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 12) * stride_4) + (cse_var_538 * stride_3))] = (((cse_var_538 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_538)) ? 0.000000e+00f : (((j_inner_s_268 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 12) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_268 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_539 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 12) * width) * 4)) + j_inner_s_268)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 13) < height) {
        for (int32_t j_inner_s_269 = 0; j_inner_s_269 < 128; ++j_inner_s_269) {
          if (((j_outer_5 * 128) + j_inner_s_269) < (width * 4)) {
            int32_t cse_var_541 = (j_outer_5 * 128);
            int32_t cse_var_540 = (cse_var_541 + j_inner_s_269);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 13) * stride_4) + (cse_var_540 * stride_3))] = (((cse_var_540 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_540)) ? 0.000000e+00f : (((j_inner_s_269 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 13) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_269 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_541 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 13) * width) * 4)) + j_inner_s_269)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 14) < height) {
        for (int32_t j_inner_s_270 = 0; j_inner_s_270 < 128; ++j_inner_s_270) {
          if (((j_outer_5 * 128) + j_inner_s_270) < (width * 4)) {
            int32_t cse_var_543 = (j_outer_5 * 128);
            int32_t cse_var_542 = (cse_var_543 + j_inner_s_270);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 14) * stride_4) + (cse_var_542 * stride_3))] = (((cse_var_542 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_542)) ? 0.000000e+00f : (((j_inner_s_270 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 14) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_270 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_543 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 14) * width) * 4)) + j_inner_s_270)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 15) < height) {
        for (int32_t j_inner_s_271 = 0; j_inner_s_271 < 128; ++j_inner_s_271) {
          if (((j_outer_5 * 128) + j_inner_s_271) < (width * 4)) {
            int32_t cse_var_545 = (j_outer_5 * 128);
            int32_t cse_var_544 = (cse_var_545 + j_inner_s_271);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 15) * stride_4) + (cse_var_544 * stride_3))] = (((cse_var_544 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_544)) ? 0.000000e+00f : (((j_inner_s_271 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 15) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_271 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_545 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 15) * width) * 4)) + j_inner_s_271)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 16) < height) {
        for (int32_t j_inner_s_272 = 0; j_inner_s_272 < 128; ++j_inner_s_272) {
          if (((j_outer_5 * 128) + j_inner_s_272) < (width * 4)) {
            int32_t cse_var_547 = (j_outer_5 * 128);
            int32_t cse_var_546 = (cse_var_547 + j_inner_s_272);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 16) * stride_4) + (cse_var_546 * stride_3))] = (((cse_var_546 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_546)) ? 0.000000e+00f : (((j_inner_s_272 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 16) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_272 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_547 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 16) * width) * 4)) + j_inner_s_272)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 17) < height) {
        for (int32_t j_inner_s_273 = 0; j_inner_s_273 < 128; ++j_inner_s_273) {
          if (((j_outer_5 * 128) + j_inner_s_273) < (width * 4)) {
            int32_t cse_var_549 = (j_outer_5 * 128);
            int32_t cse_var_548 = (cse_var_549 + j_inner_s_273);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 17) * stride_4) + (cse_var_548 * stride_3))] = (((cse_var_548 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_548)) ? 0.000000e+00f : (((j_inner_s_273 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 17) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_273 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_549 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 17) * width) * 4)) + j_inner_s_273)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 18) < height) {
        for (int32_t j_inner_s_274 = 0; j_inner_s_274 < 128; ++j_inner_s_274) {
          if (((j_outer_5 * 128) + j_inner_s_274) < (width * 4)) {
            int32_t cse_var_551 = (j_outer_5 * 128);
            int32_t cse_var_550 = (cse_var_551 + j_inner_s_274);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 18) * stride_4) + (cse_var_550 * stride_3))] = (((cse_var_550 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_550)) ? 0.000000e+00f : (((j_inner_s_274 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 18) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_274 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_551 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 18) * width) * 4)) + j_inner_s_274)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 19) < height) {
        for (int32_t j_inner_s_275 = 0; j_inner_s_275 < 128; ++j_inner_s_275) {
          if (((j_outer_5 * 128) + j_inner_s_275) < (width * 4)) {
            int32_t cse_var_553 = (j_outer_5 * 128);
            int32_t cse_var_552 = (cse_var_553 + j_inner_s_275);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 19) * stride_4) + (cse_var_552 * stride_3))] = (((cse_var_552 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_552)) ? 0.000000e+00f : (((j_inner_s_275 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 19) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_275 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_553 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 19) * width) * 4)) + j_inner_s_275)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 20) < height) {
        for (int32_t j_inner_s_276 = 0; j_inner_s_276 < 128; ++j_inner_s_276) {
          if (((j_outer_5 * 128) + j_inner_s_276) < (width * 4)) {
            int32_t cse_var_555 = (j_outer_5 * 128);
            int32_t cse_var_554 = (cse_var_555 + j_inner_s_276);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 20) * stride_4) + (cse_var_554 * stride_3))] = (((cse_var_554 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_554)) ? 0.000000e+00f : (((j_inner_s_276 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 20) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_276 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_555 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 20) * width) * 4)) + j_inner_s_276)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 21) < height) {
        for (int32_t j_inner_s_277 = 0; j_inner_s_277 < 128; ++j_inner_s_277) {
          if (((j_outer_5 * 128) + j_inner_s_277) < (width * 4)) {
            int32_t cse_var_557 = (j_outer_5 * 128);
            int32_t cse_var_556 = (cse_var_557 + j_inner_s_277);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 21) * stride_4) + (cse_var_556 * stride_3))] = (((cse_var_556 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_556)) ? 0.000000e+00f : (((j_inner_s_277 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 21) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_277 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_557 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 21) * width) * 4)) + j_inner_s_277)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 22) < height) {
        for (int32_t j_inner_s_278 = 0; j_inner_s_278 < 128; ++j_inner_s_278) {
          if (((j_outer_5 * 128) + j_inner_s_278) < (width * 4)) {
            int32_t cse_var_559 = (j_outer_5 * 128);
            int32_t cse_var_558 = (cse_var_559 + j_inner_s_278);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 22) * stride_4) + (cse_var_558 * stride_3))] = (((cse_var_558 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_558)) ? 0.000000e+00f : (((j_inner_s_278 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 22) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_278 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_559 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 22) * width) * 4)) + j_inner_s_278)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 23) < height) {
        for (int32_t j_inner_s_279 = 0; j_inner_s_279 < 128; ++j_inner_s_279) {
          if (((j_outer_5 * 128) + j_inner_s_279) < (width * 4)) {
            int32_t cse_var_561 = (j_outer_5 * 128);
            int32_t cse_var_560 = (cse_var_561 + j_inner_s_279);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 23) * stride_4) + (cse_var_560 * stride_3))] = (((cse_var_560 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_560)) ? 0.000000e+00f : (((j_inner_s_279 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 23) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_279 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_561 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 23) * width) * 4)) + j_inner_s_279)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 24) < height) {
        for (int32_t j_inner_s_280 = 0; j_inner_s_280 < 128; ++j_inner_s_280) {
          if (((j_outer_5 * 128) + j_inner_s_280) < (width * 4)) {
            int32_t cse_var_563 = (j_outer_5 * 128);
            int32_t cse_var_562 = (cse_var_563 + j_inner_s_280);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 24) * stride_4) + (cse_var_562 * stride_3))] = (((cse_var_562 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_562)) ? 0.000000e+00f : (((j_inner_s_280 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 24) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_280 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_563 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 24) * width) * 4)) + j_inner_s_280)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 25) < height) {
        for (int32_t j_inner_s_281 = 0; j_inner_s_281 < 128; ++j_inner_s_281) {
          if (((j_outer_5 * 128) + j_inner_s_281) < (width * 4)) {
            int32_t cse_var_565 = (j_outer_5 * 128);
            int32_t cse_var_564 = (cse_var_565 + j_inner_s_281);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 25) * stride_4) + (cse_var_564 * stride_3))] = (((cse_var_564 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_564)) ? 0.000000e+00f : (((j_inner_s_281 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 25) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_281 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_565 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 25) * width) * 4)) + j_inner_s_281)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 26) < height) {
        for (int32_t j_inner_s_282 = 0; j_inner_s_282 < 128; ++j_inner_s_282) {
          if (((j_outer_5 * 128) + j_inner_s_282) < (width * 4)) {
            int32_t cse_var_567 = (j_outer_5 * 128);
            int32_t cse_var_566 = (cse_var_567 + j_inner_s_282);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 26) * stride_4) + (cse_var_566 * stride_3))] = (((cse_var_566 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_566)) ? 0.000000e+00f : (((j_inner_s_282 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 26) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_282 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_567 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 26) * width) * 4)) + j_inner_s_282)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 27) < height) {
        for (int32_t j_inner_s_283 = 0; j_inner_s_283 < 128; ++j_inner_s_283) {
          if (((j_outer_5 * 128) + j_inner_s_283) < (width * 4)) {
            int32_t cse_var_569 = (j_outer_5 * 128);
            int32_t cse_var_568 = (cse_var_569 + j_inner_s_283);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 27) * stride_4) + (cse_var_568 * stride_3))] = (((cse_var_568 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_568)) ? 0.000000e+00f : (((j_inner_s_283 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 27) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_283 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_569 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 27) * width) * 4)) + j_inner_s_283)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 28) < height) {
        for (int32_t j_inner_s_284 = 0; j_inner_s_284 < 128; ++j_inner_s_284) {
          if (((j_outer_5 * 128) + j_inner_s_284) < (width * 4)) {
            int32_t cse_var_571 = (j_outer_5 * 128);
            int32_t cse_var_570 = (cse_var_571 + j_inner_s_284);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 28) * stride_4) + (cse_var_570 * stride_3))] = (((cse_var_570 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_570)) ? 0.000000e+00f : (((j_inner_s_284 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 28) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_284 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_571 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 28) * width) * 4)) + j_inner_s_284)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 29) < height) {
        for (int32_t j_inner_s_285 = 0; j_inner_s_285 < 128; ++j_inner_s_285) {
          if (((j_outer_5 * 128) + j_inner_s_285) < (width * 4)) {
            int32_t cse_var_573 = (j_outer_5 * 128);
            int32_t cse_var_572 = (cse_var_573 + j_inner_s_285);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 29) * stride_4) + (cse_var_572 * stride_3))] = (((cse_var_572 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_572)) ? 0.000000e+00f : (((j_inner_s_285 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 29) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_285 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_573 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 29) * width) * 4)) + j_inner_s_285)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 30) < height) {
        for (int32_t j_inner_s_286 = 0; j_inner_s_286 < 128; ++j_inner_s_286) {
          if (((j_outer_5 * 128) + j_inner_s_286) < (width * 4)) {
            int32_t cse_var_575 = (j_outer_5 * 128);
            int32_t cse_var_574 = (cse_var_575 + j_inner_s_286);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 30) * stride_4) + (cse_var_574 * stride_3))] = (((cse_var_574 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_574)) ? 0.000000e+00f : (((j_inner_s_286 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 30) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_286 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_575 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 30) * width) * 4)) + j_inner_s_286)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 31) < height) {
        for (int32_t j_inner_s_287 = 0; j_inner_s_287 < 128; ++j_inner_s_287) {
          if (((j_outer_5 * 128) + j_inner_s_287) < (width * 4)) {
            int32_t cse_var_577 = (j_outer_5 * 128);
            int32_t cse_var_576 = (cse_var_577 + j_inner_s_287);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 31) * stride_4) + (cse_var_576 * stride_3))] = (((cse_var_576 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_576)) ? 0.000000e+00f : (((j_inner_s_287 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 31) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_287 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_577 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 31) * width) * 4)) + j_inner_s_287)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 32) < height) {
        for (int32_t j_inner_s_288 = 0; j_inner_s_288 < 128; ++j_inner_s_288) {
          if (((j_outer_5 * 128) + j_inner_s_288) < (width * 4)) {
            int32_t cse_var_579 = (j_outer_5 * 128);
            int32_t cse_var_578 = (cse_var_579 + j_inner_s_288);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 32) * stride_4) + (cse_var_578 * stride_3))] = (((cse_var_578 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_578)) ? 0.000000e+00f : (((j_inner_s_288 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 32) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_288 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_579 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 32) * width) * 4)) + j_inner_s_288)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 33) < height) {
        for (int32_t j_inner_s_289 = 0; j_inner_s_289 < 128; ++j_inner_s_289) {
          if (((j_outer_5 * 128) + j_inner_s_289) < (width * 4)) {
            int32_t cse_var_581 = (j_outer_5 * 128);
            int32_t cse_var_580 = (cse_var_581 + j_inner_s_289);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 33) * stride_4) + (cse_var_580 * stride_3))] = (((cse_var_580 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_580)) ? 0.000000e+00f : (((j_inner_s_289 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 33) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_289 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_581 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 33) * width) * 4)) + j_inner_s_289)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 34) < height) {
        for (int32_t j_inner_s_290 = 0; j_inner_s_290 < 128; ++j_inner_s_290) {
          if (((j_outer_5 * 128) + j_inner_s_290) < (width * 4)) {
            int32_t cse_var_583 = (j_outer_5 * 128);
            int32_t cse_var_582 = (cse_var_583 + j_inner_s_290);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 34) * stride_4) + (cse_var_582 * stride_3))] = (((cse_var_582 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_582)) ? 0.000000e+00f : (((j_inner_s_290 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 34) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_290 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_583 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 34) * width) * 4)) + j_inner_s_290)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 35) < height) {
        for (int32_t j_inner_s_291 = 0; j_inner_s_291 < 128; ++j_inner_s_291) {
          if (((j_outer_5 * 128) + j_inner_s_291) < (width * 4)) {
            int32_t cse_var_585 = (j_outer_5 * 128);
            int32_t cse_var_584 = (cse_var_585 + j_inner_s_291);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 35) * stride_4) + (cse_var_584 * stride_3))] = (((cse_var_584 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_584)) ? 0.000000e+00f : (((j_inner_s_291 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 35) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_291 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_585 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 35) * width) * 4)) + j_inner_s_291)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 36) < height) {
        for (int32_t j_inner_s_292 = 0; j_inner_s_292 < 128; ++j_inner_s_292) {
          if (((j_outer_5 * 128) + j_inner_s_292) < (width * 4)) {
            int32_t cse_var_587 = (j_outer_5 * 128);
            int32_t cse_var_586 = (cse_var_587 + j_inner_s_292);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 36) * stride_4) + (cse_var_586 * stride_3))] = (((cse_var_586 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_586)) ? 0.000000e+00f : (((j_inner_s_292 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 36) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_292 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_587 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 36) * width) * 4)) + j_inner_s_292)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 37) < height) {
        for (int32_t j_inner_s_293 = 0; j_inner_s_293 < 128; ++j_inner_s_293) {
          if (((j_outer_5 * 128) + j_inner_s_293) < (width * 4)) {
            int32_t cse_var_589 = (j_outer_5 * 128);
            int32_t cse_var_588 = (cse_var_589 + j_inner_s_293);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 37) * stride_4) + (cse_var_588 * stride_3))] = (((cse_var_588 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_588)) ? 0.000000e+00f : (((j_inner_s_293 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 37) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_293 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_589 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 37) * width) * 4)) + j_inner_s_293)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 38) < height) {
        for (int32_t j_inner_s_294 = 0; j_inner_s_294 < 128; ++j_inner_s_294) {
          if (((j_outer_5 * 128) + j_inner_s_294) < (width * 4)) {
            int32_t cse_var_591 = (j_outer_5 * 128);
            int32_t cse_var_590 = (cse_var_591 + j_inner_s_294);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 38) * stride_4) + (cse_var_590 * stride_3))] = (((cse_var_590 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_590)) ? 0.000000e+00f : (((j_inner_s_294 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 38) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_294 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_591 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 38) * width) * 4)) + j_inner_s_294)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 39) < height) {
        for (int32_t j_inner_s_295 = 0; j_inner_s_295 < 128; ++j_inner_s_295) {
          if (((j_outer_5 * 128) + j_inner_s_295) < (width * 4)) {
            int32_t cse_var_593 = (j_outer_5 * 128);
            int32_t cse_var_592 = (cse_var_593 + j_inner_s_295);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 39) * stride_4) + (cse_var_592 * stride_3))] = (((cse_var_592 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_592)) ? 0.000000e+00f : (((j_inner_s_295 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 39) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_295 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_593 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 39) * width) * 4)) + j_inner_s_295)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 40) < height) {
        for (int32_t j_inner_s_296 = 0; j_inner_s_296 < 128; ++j_inner_s_296) {
          if (((j_outer_5 * 128) + j_inner_s_296) < (width * 4)) {
            int32_t cse_var_595 = (j_outer_5 * 128);
            int32_t cse_var_594 = (cse_var_595 + j_inner_s_296);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 40) * stride_4) + (cse_var_594 * stride_3))] = (((cse_var_594 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_594)) ? 0.000000e+00f : (((j_inner_s_296 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 40) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_296 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_595 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 40) * width) * 4)) + j_inner_s_296)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 41) < height) {
        for (int32_t j_inner_s_297 = 0; j_inner_s_297 < 128; ++j_inner_s_297) {
          if (((j_outer_5 * 128) + j_inner_s_297) < (width * 4)) {
            int32_t cse_var_597 = (j_outer_5 * 128);
            int32_t cse_var_596 = (cse_var_597 + j_inner_s_297);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 41) * stride_4) + (cse_var_596 * stride_3))] = (((cse_var_596 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_596)) ? 0.000000e+00f : (((j_inner_s_297 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 41) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_297 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_597 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 41) * width) * 4)) + j_inner_s_297)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 42) < height) {
        for (int32_t j_inner_s_298 = 0; j_inner_s_298 < 128; ++j_inner_s_298) {
          if (((j_outer_5 * 128) + j_inner_s_298) < (width * 4)) {
            int32_t cse_var_599 = (j_outer_5 * 128);
            int32_t cse_var_598 = (cse_var_599 + j_inner_s_298);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 42) * stride_4) + (cse_var_598 * stride_3))] = (((cse_var_598 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_598)) ? 0.000000e+00f : (((j_inner_s_298 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 42) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_298 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_599 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 42) * width) * 4)) + j_inner_s_298)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 43) < height) {
        for (int32_t j_inner_s_299 = 0; j_inner_s_299 < 128; ++j_inner_s_299) {
          if (((j_outer_5 * 128) + j_inner_s_299) < (width * 4)) {
            int32_t cse_var_601 = (j_outer_5 * 128);
            int32_t cse_var_600 = (cse_var_601 + j_inner_s_299);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 43) * stride_4) + (cse_var_600 * stride_3))] = (((cse_var_600 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_600)) ? 0.000000e+00f : (((j_inner_s_299 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 43) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_299 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_601 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 43) * width) * 4)) + j_inner_s_299)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 44) < height) {
        for (int32_t j_inner_s_300 = 0; j_inner_s_300 < 128; ++j_inner_s_300) {
          if (((j_outer_5 * 128) + j_inner_s_300) < (width * 4)) {
            int32_t cse_var_603 = (j_outer_5 * 128);
            int32_t cse_var_602 = (cse_var_603 + j_inner_s_300);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 44) * stride_4) + (cse_var_602 * stride_3))] = (((cse_var_602 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_602)) ? 0.000000e+00f : (((j_inner_s_300 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 44) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_300 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_603 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 44) * width) * 4)) + j_inner_s_300)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 45) < height) {
        for (int32_t j_inner_s_301 = 0; j_inner_s_301 < 128; ++j_inner_s_301) {
          if (((j_outer_5 * 128) + j_inner_s_301) < (width * 4)) {
            int32_t cse_var_605 = (j_outer_5 * 128);
            int32_t cse_var_604 = (cse_var_605 + j_inner_s_301);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 45) * stride_4) + (cse_var_604 * stride_3))] = (((cse_var_604 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_604)) ? 0.000000e+00f : (((j_inner_s_301 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 45) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_301 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_605 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 45) * width) * 4)) + j_inner_s_301)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 46) < height) {
        for (int32_t j_inner_s_302 = 0; j_inner_s_302 < 128; ++j_inner_s_302) {
          if (((j_outer_5 * 128) + j_inner_s_302) < (width * 4)) {
            int32_t cse_var_607 = (j_outer_5 * 128);
            int32_t cse_var_606 = (cse_var_607 + j_inner_s_302);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 46) * stride_4) + (cse_var_606 * stride_3))] = (((cse_var_606 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_606)) ? 0.000000e+00f : (((j_inner_s_302 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 46) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_302 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_607 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 46) * width) * 4)) + j_inner_s_302)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 47) < height) {
        for (int32_t j_inner_s_303 = 0; j_inner_s_303 < 128; ++j_inner_s_303) {
          if (((j_outer_5 * 128) + j_inner_s_303) < (width * 4)) {
            int32_t cse_var_609 = (j_outer_5 * 128);
            int32_t cse_var_608 = (cse_var_609 + j_inner_s_303);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 47) * stride_4) + (cse_var_608 * stride_3))] = (((cse_var_608 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_608)) ? 0.000000e+00f : (((j_inner_s_303 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 47) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_303 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_609 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 47) * width) * 4)) + j_inner_s_303)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 48) < height) {
        for (int32_t j_inner_s_304 = 0; j_inner_s_304 < 128; ++j_inner_s_304) {
          if (((j_outer_5 * 128) + j_inner_s_304) < (width * 4)) {
            int32_t cse_var_611 = (j_outer_5 * 128);
            int32_t cse_var_610 = (cse_var_611 + j_inner_s_304);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 48) * stride_4) + (cse_var_610 * stride_3))] = (((cse_var_610 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_610)) ? 0.000000e+00f : (((j_inner_s_304 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 48) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_304 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_611 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 48) * width) * 4)) + j_inner_s_304)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 49) < height) {
        for (int32_t j_inner_s_305 = 0; j_inner_s_305 < 128; ++j_inner_s_305) {
          if (((j_outer_5 * 128) + j_inner_s_305) < (width * 4)) {
            int32_t cse_var_613 = (j_outer_5 * 128);
            int32_t cse_var_612 = (cse_var_613 + j_inner_s_305);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 49) * stride_4) + (cse_var_612 * stride_3))] = (((cse_var_612 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_612)) ? 0.000000e+00f : (((j_inner_s_305 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 49) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_305 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_613 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 49) * width) * 4)) + j_inner_s_305)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 50) < height) {
        for (int32_t j_inner_s_306 = 0; j_inner_s_306 < 128; ++j_inner_s_306) {
          if (((j_outer_5 * 128) + j_inner_s_306) < (width * 4)) {
            int32_t cse_var_615 = (j_outer_5 * 128);
            int32_t cse_var_614 = (cse_var_615 + j_inner_s_306);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 50) * stride_4) + (cse_var_614 * stride_3))] = (((cse_var_614 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_614)) ? 0.000000e+00f : (((j_inner_s_306 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 50) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_306 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_615 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 50) * width) * 4)) + j_inner_s_306)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 51) < height) {
        for (int32_t j_inner_s_307 = 0; j_inner_s_307 < 128; ++j_inner_s_307) {
          if (((j_outer_5 * 128) + j_inner_s_307) < (width * 4)) {
            int32_t cse_var_617 = (j_outer_5 * 128);
            int32_t cse_var_616 = (cse_var_617 + j_inner_s_307);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 51) * stride_4) + (cse_var_616 * stride_3))] = (((cse_var_616 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_616)) ? 0.000000e+00f : (((j_inner_s_307 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 51) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_307 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_617 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 51) * width) * 4)) + j_inner_s_307)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 52) < height) {
        for (int32_t j_inner_s_308 = 0; j_inner_s_308 < 128; ++j_inner_s_308) {
          if (((j_outer_5 * 128) + j_inner_s_308) < (width * 4)) {
            int32_t cse_var_619 = (j_outer_5 * 128);
            int32_t cse_var_618 = (cse_var_619 + j_inner_s_308);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 52) * stride_4) + (cse_var_618 * stride_3))] = (((cse_var_618 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_618)) ? 0.000000e+00f : (((j_inner_s_308 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 52) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_308 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_619 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 52) * width) * 4)) + j_inner_s_308)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 53) < height) {
        for (int32_t j_inner_s_309 = 0; j_inner_s_309 < 128; ++j_inner_s_309) {
          if (((j_outer_5 * 128) + j_inner_s_309) < (width * 4)) {
            int32_t cse_var_621 = (j_outer_5 * 128);
            int32_t cse_var_620 = (cse_var_621 + j_inner_s_309);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 53) * stride_4) + (cse_var_620 * stride_3))] = (((cse_var_620 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_620)) ? 0.000000e+00f : (((j_inner_s_309 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 53) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_309 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_621 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 53) * width) * 4)) + j_inner_s_309)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 54) < height) {
        for (int32_t j_inner_s_310 = 0; j_inner_s_310 < 128; ++j_inner_s_310) {
          if (((j_outer_5 * 128) + j_inner_s_310) < (width * 4)) {
            int32_t cse_var_623 = (j_outer_5 * 128);
            int32_t cse_var_622 = (cse_var_623 + j_inner_s_310);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 54) * stride_4) + (cse_var_622 * stride_3))] = (((cse_var_622 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_622)) ? 0.000000e+00f : (((j_inner_s_310 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 54) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_310 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_623 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 54) * width) * 4)) + j_inner_s_310)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 55) < height) {
        for (int32_t j_inner_s_311 = 0; j_inner_s_311 < 128; ++j_inner_s_311) {
          if (((j_outer_5 * 128) + j_inner_s_311) < (width * 4)) {
            int32_t cse_var_625 = (j_outer_5 * 128);
            int32_t cse_var_624 = (cse_var_625 + j_inner_s_311);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 55) * stride_4) + (cse_var_624 * stride_3))] = (((cse_var_624 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_624)) ? 0.000000e+00f : (((j_inner_s_311 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 55) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_311 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_625 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 55) * width) * 4)) + j_inner_s_311)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 56) < height) {
        for (int32_t j_inner_s_312 = 0; j_inner_s_312 < 128; ++j_inner_s_312) {
          if (((j_outer_5 * 128) + j_inner_s_312) < (width * 4)) {
            int32_t cse_var_627 = (j_outer_5 * 128);
            int32_t cse_var_626 = (cse_var_627 + j_inner_s_312);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 56) * stride_4) + (cse_var_626 * stride_3))] = (((cse_var_626 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_626)) ? 0.000000e+00f : (((j_inner_s_312 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 56) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_312 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_627 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 56) * width) * 4)) + j_inner_s_312)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 57) < height) {
        for (int32_t j_inner_s_313 = 0; j_inner_s_313 < 128; ++j_inner_s_313) {
          if (((j_outer_5 * 128) + j_inner_s_313) < (width * 4)) {
            int32_t cse_var_629 = (j_outer_5 * 128);
            int32_t cse_var_628 = (cse_var_629 + j_inner_s_313);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 57) * stride_4) + (cse_var_628 * stride_3))] = (((cse_var_628 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_628)) ? 0.000000e+00f : (((j_inner_s_313 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 57) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_313 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_629 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 57) * width) * 4)) + j_inner_s_313)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 58) < height) {
        for (int32_t j_inner_s_314 = 0; j_inner_s_314 < 128; ++j_inner_s_314) {
          if (((j_outer_5 * 128) + j_inner_s_314) < (width * 4)) {
            int32_t cse_var_631 = (j_outer_5 * 128);
            int32_t cse_var_630 = (cse_var_631 + j_inner_s_314);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 58) * stride_4) + (cse_var_630 * stride_3))] = (((cse_var_630 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_630)) ? 0.000000e+00f : (((j_inner_s_314 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 58) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_314 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_631 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 58) * width) * 4)) + j_inner_s_314)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 59) < height) {
        for (int32_t j_inner_s_315 = 0; j_inner_s_315 < 128; ++j_inner_s_315) {
          if (((j_outer_5 * 128) + j_inner_s_315) < (width * 4)) {
            int32_t cse_var_633 = (j_outer_5 * 128);
            int32_t cse_var_632 = (cse_var_633 + j_inner_s_315);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 59) * stride_4) + (cse_var_632 * stride_3))] = (((cse_var_632 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_632)) ? 0.000000e+00f : (((j_inner_s_315 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 59) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_315 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_633 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 59) * width) * 4)) + j_inner_s_315)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 60) < height) {
        for (int32_t j_inner_s_316 = 0; j_inner_s_316 < 128; ++j_inner_s_316) {
          if (((j_outer_5 * 128) + j_inner_s_316) < (width * 4)) {
            int32_t cse_var_635 = (j_outer_5 * 128);
            int32_t cse_var_634 = (cse_var_635 + j_inner_s_316);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 60) * stride_4) + (cse_var_634 * stride_3))] = (((cse_var_634 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_634)) ? 0.000000e+00f : (((j_inner_s_316 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 60) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_316 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_635 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 60) * width) * 4)) + j_inner_s_316)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 61) < height) {
        for (int32_t j_inner_s_317 = 0; j_inner_s_317 < 128; ++j_inner_s_317) {
          if (((j_outer_5 * 128) + j_inner_s_317) < (width * 4)) {
            int32_t cse_var_637 = (j_outer_5 * 128);
            int32_t cse_var_636 = (cse_var_637 + j_inner_s_317);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 61) * stride_4) + (cse_var_636 * stride_3))] = (((cse_var_636 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_636)) ? 0.000000e+00f : (((j_inner_s_317 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 61) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_317 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_637 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 61) * width) * 4)) + j_inner_s_317)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 62) < height) {
        for (int32_t j_inner_s_318 = 0; j_inner_s_318 < 128; ++j_inner_s_318) {
          if (((j_outer_5 * 128) + j_inner_s_318) < (width * 4)) {
            int32_t cse_var_639 = (j_outer_5 * 128);
            int32_t cse_var_638 = (cse_var_639 + j_inner_s_318);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 62) * stride_4) + (cse_var_638 * stride_3))] = (((cse_var_638 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_638)) ? 0.000000e+00f : (((j_inner_s_318 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 62) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_318 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_639 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 62) * width) * 4)) + j_inner_s_318)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 63) < height) {
        for (int32_t j_inner_s_319 = 0; j_inner_s_319 < 128; ++j_inner_s_319) {
          if (((j_outer_5 * 128) + j_inner_s_319) < (width * 4)) {
            int32_t cse_var_641 = (j_outer_5 * 128);
            int32_t cse_var_640 = (cse_var_641 + j_inner_s_319);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 63) * stride_4) + (cse_var_640 * stride_3))] = (((cse_var_640 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_640)) ? 0.000000e+00f : (((j_inner_s_319 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 63) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_319 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_641 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 63) * width) * 4)) + j_inner_s_319)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 64) < height) {
        for (int32_t j_inner_s_320 = 0; j_inner_s_320 < 128; ++j_inner_s_320) {
          if (((j_outer_5 * 128) + j_inner_s_320) < (width * 4)) {
            int32_t cse_var_643 = (j_outer_5 * 128);
            int32_t cse_var_642 = (cse_var_643 + j_inner_s_320);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 64) * stride_4) + (cse_var_642 * stride_3))] = (((cse_var_642 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_642)) ? 0.000000e+00f : (((j_inner_s_320 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 64) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_320 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_643 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 64) * width) * 4)) + j_inner_s_320)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 65) < height) {
        for (int32_t j_inner_s_321 = 0; j_inner_s_321 < 128; ++j_inner_s_321) {
          if (((j_outer_5 * 128) + j_inner_s_321) < (width * 4)) {
            int32_t cse_var_645 = (j_outer_5 * 128);
            int32_t cse_var_644 = (cse_var_645 + j_inner_s_321);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 65) * stride_4) + (cse_var_644 * stride_3))] = (((cse_var_644 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_644)) ? 0.000000e+00f : (((j_inner_s_321 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 65) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_321 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_645 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 65) * width) * 4)) + j_inner_s_321)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 66) < height) {
        for (int32_t j_inner_s_322 = 0; j_inner_s_322 < 128; ++j_inner_s_322) {
          if (((j_outer_5 * 128) + j_inner_s_322) < (width * 4)) {
            int32_t cse_var_647 = (j_outer_5 * 128);
            int32_t cse_var_646 = (cse_var_647 + j_inner_s_322);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 66) * stride_4) + (cse_var_646 * stride_3))] = (((cse_var_646 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_646)) ? 0.000000e+00f : (((j_inner_s_322 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 66) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_322 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_647 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 66) * width) * 4)) + j_inner_s_322)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 67) < height) {
        for (int32_t j_inner_s_323 = 0; j_inner_s_323 < 128; ++j_inner_s_323) {
          if (((j_outer_5 * 128) + j_inner_s_323) < (width * 4)) {
            int32_t cse_var_649 = (j_outer_5 * 128);
            int32_t cse_var_648 = (cse_var_649 + j_inner_s_323);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 67) * stride_4) + (cse_var_648 * stride_3))] = (((cse_var_648 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_648)) ? 0.000000e+00f : (((j_inner_s_323 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 67) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_323 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_649 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 67) * width) * 4)) + j_inner_s_323)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 68) < height) {
        for (int32_t j_inner_s_324 = 0; j_inner_s_324 < 128; ++j_inner_s_324) {
          if (((j_outer_5 * 128) + j_inner_s_324) < (width * 4)) {
            int32_t cse_var_651 = (j_outer_5 * 128);
            int32_t cse_var_650 = (cse_var_651 + j_inner_s_324);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 68) * stride_4) + (cse_var_650 * stride_3))] = (((cse_var_650 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_650)) ? 0.000000e+00f : (((j_inner_s_324 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 68) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_324 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_651 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 68) * width) * 4)) + j_inner_s_324)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 69) < height) {
        for (int32_t j_inner_s_325 = 0; j_inner_s_325 < 128; ++j_inner_s_325) {
          if (((j_outer_5 * 128) + j_inner_s_325) < (width * 4)) {
            int32_t cse_var_653 = (j_outer_5 * 128);
            int32_t cse_var_652 = (cse_var_653 + j_inner_s_325);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 69) * stride_4) + (cse_var_652 * stride_3))] = (((cse_var_652 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_652)) ? 0.000000e+00f : (((j_inner_s_325 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 69) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_325 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_653 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 69) * width) * 4)) + j_inner_s_325)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 70) < height) {
        for (int32_t j_inner_s_326 = 0; j_inner_s_326 < 128; ++j_inner_s_326) {
          if (((j_outer_5 * 128) + j_inner_s_326) < (width * 4)) {
            int32_t cse_var_655 = (j_outer_5 * 128);
            int32_t cse_var_654 = (cse_var_655 + j_inner_s_326);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 70) * stride_4) + (cse_var_654 * stride_3))] = (((cse_var_654 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_654)) ? 0.000000e+00f : (((j_inner_s_326 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 70) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_326 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_655 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 70) * width) * 4)) + j_inner_s_326)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 71) < height) {
        for (int32_t j_inner_s_327 = 0; j_inner_s_327 < 128; ++j_inner_s_327) {
          if (((j_outer_5 * 128) + j_inner_s_327) < (width * 4)) {
            int32_t cse_var_657 = (j_outer_5 * 128);
            int32_t cse_var_656 = (cse_var_657 + j_inner_s_327);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 71) * stride_4) + (cse_var_656 * stride_3))] = (((cse_var_656 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_656)) ? 0.000000e+00f : (((j_inner_s_327 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 71) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_327 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_657 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 71) * width) * 4)) + j_inner_s_327)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 72) < height) {
        for (int32_t j_inner_s_328 = 0; j_inner_s_328 < 128; ++j_inner_s_328) {
          if (((j_outer_5 * 128) + j_inner_s_328) < (width * 4)) {
            int32_t cse_var_659 = (j_outer_5 * 128);
            int32_t cse_var_658 = (cse_var_659 + j_inner_s_328);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 72) * stride_4) + (cse_var_658 * stride_3))] = (((cse_var_658 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_658)) ? 0.000000e+00f : (((j_inner_s_328 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 72) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_328 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_659 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 72) * width) * 4)) + j_inner_s_328)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 73) < height) {
        for (int32_t j_inner_s_329 = 0; j_inner_s_329 < 128; ++j_inner_s_329) {
          if (((j_outer_5 * 128) + j_inner_s_329) < (width * 4)) {
            int32_t cse_var_661 = (j_outer_5 * 128);
            int32_t cse_var_660 = (cse_var_661 + j_inner_s_329);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 73) * stride_4) + (cse_var_660 * stride_3))] = (((cse_var_660 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_660)) ? 0.000000e+00f : (((j_inner_s_329 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 73) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_329 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_661 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 73) * width) * 4)) + j_inner_s_329)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 74) < height) {
        for (int32_t j_inner_s_330 = 0; j_inner_s_330 < 128; ++j_inner_s_330) {
          if (((j_outer_5 * 128) + j_inner_s_330) < (width * 4)) {
            int32_t cse_var_663 = (j_outer_5 * 128);
            int32_t cse_var_662 = (cse_var_663 + j_inner_s_330);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 74) * stride_4) + (cse_var_662 * stride_3))] = (((cse_var_662 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_662)) ? 0.000000e+00f : (((j_inner_s_330 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 74) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_330 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_663 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 74) * width) * 4)) + j_inner_s_330)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 75) < height) {
        for (int32_t j_inner_s_331 = 0; j_inner_s_331 < 128; ++j_inner_s_331) {
          if (((j_outer_5 * 128) + j_inner_s_331) < (width * 4)) {
            int32_t cse_var_665 = (j_outer_5 * 128);
            int32_t cse_var_664 = (cse_var_665 + j_inner_s_331);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 75) * stride_4) + (cse_var_664 * stride_3))] = (((cse_var_664 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_664)) ? 0.000000e+00f : (((j_inner_s_331 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 75) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_331 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_665 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 75) * width) * 4)) + j_inner_s_331)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 76) < height) {
        for (int32_t j_inner_s_332 = 0; j_inner_s_332 < 128; ++j_inner_s_332) {
          if (((j_outer_5 * 128) + j_inner_s_332) < (width * 4)) {
            int32_t cse_var_667 = (j_outer_5 * 128);
            int32_t cse_var_666 = (cse_var_667 + j_inner_s_332);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 76) * stride_4) + (cse_var_666 * stride_3))] = (((cse_var_666 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_666)) ? 0.000000e+00f : (((j_inner_s_332 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 76) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_332 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_667 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 76) * width) * 4)) + j_inner_s_332)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 77) < height) {
        for (int32_t j_inner_s_333 = 0; j_inner_s_333 < 128; ++j_inner_s_333) {
          if (((j_outer_5 * 128) + j_inner_s_333) < (width * 4)) {
            int32_t cse_var_669 = (j_outer_5 * 128);
            int32_t cse_var_668 = (cse_var_669 + j_inner_s_333);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 77) * stride_4) + (cse_var_668 * stride_3))] = (((cse_var_668 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_668)) ? 0.000000e+00f : (((j_inner_s_333 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 77) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_333 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_669 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 77) * width) * 4)) + j_inner_s_333)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 78) < height) {
        for (int32_t j_inner_s_334 = 0; j_inner_s_334 < 128; ++j_inner_s_334) {
          if (((j_outer_5 * 128) + j_inner_s_334) < (width * 4)) {
            int32_t cse_var_671 = (j_outer_5 * 128);
            int32_t cse_var_670 = (cse_var_671 + j_inner_s_334);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 78) * stride_4) + (cse_var_670 * stride_3))] = (((cse_var_670 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_670)) ? 0.000000e+00f : (((j_inner_s_334 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 78) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_334 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_671 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 78) * width) * 4)) + j_inner_s_334)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 79) < height) {
        for (int32_t j_inner_s_335 = 0; j_inner_s_335 < 128; ++j_inner_s_335) {
          if (((j_outer_5 * 128) + j_inner_s_335) < (width * 4)) {
            int32_t cse_var_673 = (j_outer_5 * 128);
            int32_t cse_var_672 = (cse_var_673 + j_inner_s_335);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 79) * stride_4) + (cse_var_672 * stride_3))] = (((cse_var_672 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_672)) ? 0.000000e+00f : (((j_inner_s_335 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 79) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_335 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_673 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 79) * width) * 4)) + j_inner_s_335)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 80) < height) {
        for (int32_t j_inner_s_336 = 0; j_inner_s_336 < 128; ++j_inner_s_336) {
          if (((j_outer_5 * 128) + j_inner_s_336) < (width * 4)) {
            int32_t cse_var_675 = (j_outer_5 * 128);
            int32_t cse_var_674 = (cse_var_675 + j_inner_s_336);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 80) * stride_4) + (cse_var_674 * stride_3))] = (((cse_var_674 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_674)) ? 0.000000e+00f : (((j_inner_s_336 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 80) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_336 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_675 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 80) * width) * 4)) + j_inner_s_336)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 81) < height) {
        for (int32_t j_inner_s_337 = 0; j_inner_s_337 < 128; ++j_inner_s_337) {
          if (((j_outer_5 * 128) + j_inner_s_337) < (width * 4)) {
            int32_t cse_var_677 = (j_outer_5 * 128);
            int32_t cse_var_676 = (cse_var_677 + j_inner_s_337);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 81) * stride_4) + (cse_var_676 * stride_3))] = (((cse_var_676 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_676)) ? 0.000000e+00f : (((j_inner_s_337 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 81) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_337 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_677 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 81) * width) * 4)) + j_inner_s_337)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 82) < height) {
        for (int32_t j_inner_s_338 = 0; j_inner_s_338 < 128; ++j_inner_s_338) {
          if (((j_outer_5 * 128) + j_inner_s_338) < (width * 4)) {
            int32_t cse_var_679 = (j_outer_5 * 128);
            int32_t cse_var_678 = (cse_var_679 + j_inner_s_338);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 82) * stride_4) + (cse_var_678 * stride_3))] = (((cse_var_678 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_678)) ? 0.000000e+00f : (((j_inner_s_338 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 82) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_338 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_679 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 82) * width) * 4)) + j_inner_s_338)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 83) < height) {
        for (int32_t j_inner_s_339 = 0; j_inner_s_339 < 128; ++j_inner_s_339) {
          if (((j_outer_5 * 128) + j_inner_s_339) < (width * 4)) {
            int32_t cse_var_681 = (j_outer_5 * 128);
            int32_t cse_var_680 = (cse_var_681 + j_inner_s_339);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 83) * stride_4) + (cse_var_680 * stride_3))] = (((cse_var_680 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_680)) ? 0.000000e+00f : (((j_inner_s_339 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 83) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_339 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_681 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 83) * width) * 4)) + j_inner_s_339)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 84) < height) {
        for (int32_t j_inner_s_340 = 0; j_inner_s_340 < 128; ++j_inner_s_340) {
          if (((j_outer_5 * 128) + j_inner_s_340) < (width * 4)) {
            int32_t cse_var_683 = (j_outer_5 * 128);
            int32_t cse_var_682 = (cse_var_683 + j_inner_s_340);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 84) * stride_4) + (cse_var_682 * stride_3))] = (((cse_var_682 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_682)) ? 0.000000e+00f : (((j_inner_s_340 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 84) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_340 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_683 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 84) * width) * 4)) + j_inner_s_340)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 85) < height) {
        for (int32_t j_inner_s_341 = 0; j_inner_s_341 < 128; ++j_inner_s_341) {
          if (((j_outer_5 * 128) + j_inner_s_341) < (width * 4)) {
            int32_t cse_var_685 = (j_outer_5 * 128);
            int32_t cse_var_684 = (cse_var_685 + j_inner_s_341);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 85) * stride_4) + (cse_var_684 * stride_3))] = (((cse_var_684 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_684)) ? 0.000000e+00f : (((j_inner_s_341 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 85) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_341 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_685 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 85) * width) * 4)) + j_inner_s_341)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 86) < height) {
        for (int32_t j_inner_s_342 = 0; j_inner_s_342 < 128; ++j_inner_s_342) {
          if (((j_outer_5 * 128) + j_inner_s_342) < (width * 4)) {
            int32_t cse_var_687 = (j_outer_5 * 128);
            int32_t cse_var_686 = (cse_var_687 + j_inner_s_342);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 86) * stride_4) + (cse_var_686 * stride_3))] = (((cse_var_686 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_686)) ? 0.000000e+00f : (((j_inner_s_342 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 86) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_342 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_687 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 86) * width) * 4)) + j_inner_s_342)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 87) < height) {
        for (int32_t j_inner_s_343 = 0; j_inner_s_343 < 128; ++j_inner_s_343) {
          if (((j_outer_5 * 128) + j_inner_s_343) < (width * 4)) {
            int32_t cse_var_689 = (j_outer_5 * 128);
            int32_t cse_var_688 = (cse_var_689 + j_inner_s_343);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 87) * stride_4) + (cse_var_688 * stride_3))] = (((cse_var_688 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_688)) ? 0.000000e+00f : (((j_inner_s_343 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 87) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_343 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_689 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 87) * width) * 4)) + j_inner_s_343)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 88) < height) {
        for (int32_t j_inner_s_344 = 0; j_inner_s_344 < 128; ++j_inner_s_344) {
          if (((j_outer_5 * 128) + j_inner_s_344) < (width * 4)) {
            int32_t cse_var_691 = (j_outer_5 * 128);
            int32_t cse_var_690 = (cse_var_691 + j_inner_s_344);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 88) * stride_4) + (cse_var_690 * stride_3))] = (((cse_var_690 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_690)) ? 0.000000e+00f : (((j_inner_s_344 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 88) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_344 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_691 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 88) * width) * 4)) + j_inner_s_344)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 89) < height) {
        for (int32_t j_inner_s_345 = 0; j_inner_s_345 < 128; ++j_inner_s_345) {
          if (((j_outer_5 * 128) + j_inner_s_345) < (width * 4)) {
            int32_t cse_var_693 = (j_outer_5 * 128);
            int32_t cse_var_692 = (cse_var_693 + j_inner_s_345);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 89) * stride_4) + (cse_var_692 * stride_3))] = (((cse_var_692 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_692)) ? 0.000000e+00f : (((j_inner_s_345 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 89) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_345 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_693 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 89) * width) * 4)) + j_inner_s_345)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 90) < height) {
        for (int32_t j_inner_s_346 = 0; j_inner_s_346 < 128; ++j_inner_s_346) {
          if (((j_outer_5 * 128) + j_inner_s_346) < (width * 4)) {
            int32_t cse_var_695 = (j_outer_5 * 128);
            int32_t cse_var_694 = (cse_var_695 + j_inner_s_346);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 90) * stride_4) + (cse_var_694 * stride_3))] = (((cse_var_694 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_694)) ? 0.000000e+00f : (((j_inner_s_346 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 90) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_346 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_695 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 90) * width) * 4)) + j_inner_s_346)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 91) < height) {
        for (int32_t j_inner_s_347 = 0; j_inner_s_347 < 128; ++j_inner_s_347) {
          if (((j_outer_5 * 128) + j_inner_s_347) < (width * 4)) {
            int32_t cse_var_697 = (j_outer_5 * 128);
            int32_t cse_var_696 = (cse_var_697 + j_inner_s_347);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 91) * stride_4) + (cse_var_696 * stride_3))] = (((cse_var_696 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_696)) ? 0.000000e+00f : (((j_inner_s_347 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 91) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_347 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_697 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 91) * width) * 4)) + j_inner_s_347)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 92) < height) {
        for (int32_t j_inner_s_348 = 0; j_inner_s_348 < 128; ++j_inner_s_348) {
          if (((j_outer_5 * 128) + j_inner_s_348) < (width * 4)) {
            int32_t cse_var_699 = (j_outer_5 * 128);
            int32_t cse_var_698 = (cse_var_699 + j_inner_s_348);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 92) * stride_4) + (cse_var_698 * stride_3))] = (((cse_var_698 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_698)) ? 0.000000e+00f : (((j_inner_s_348 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 92) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_348 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_699 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 92) * width) * 4)) + j_inner_s_348)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 93) < height) {
        for (int32_t j_inner_s_349 = 0; j_inner_s_349 < 128; ++j_inner_s_349) {
          if (((j_outer_5 * 128) + j_inner_s_349) < (width * 4)) {
            int32_t cse_var_701 = (j_outer_5 * 128);
            int32_t cse_var_700 = (cse_var_701 + j_inner_s_349);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 93) * stride_4) + (cse_var_700 * stride_3))] = (((cse_var_700 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_700)) ? 0.000000e+00f : (((j_inner_s_349 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 93) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_349 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_701 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 93) * width) * 4)) + j_inner_s_349)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 94) < height) {
        for (int32_t j_inner_s_350 = 0; j_inner_s_350 < 128; ++j_inner_s_350) {
          if (((j_outer_5 * 128) + j_inner_s_350) < (width * 4)) {
            int32_t cse_var_703 = (j_outer_5 * 128);
            int32_t cse_var_702 = (cse_var_703 + j_inner_s_350);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 94) * stride_4) + (cse_var_702 * stride_3))] = (((cse_var_702 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_702)) ? 0.000000e+00f : (((j_inner_s_350 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 94) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_350 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_703 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 94) * width) * 4)) + j_inner_s_350)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 95) < height) {
        for (int32_t j_inner_s_351 = 0; j_inner_s_351 < 128; ++j_inner_s_351) {
          if (((j_outer_5 * 128) + j_inner_s_351) < (width * 4)) {
            int32_t cse_var_705 = (j_outer_5 * 128);
            int32_t cse_var_704 = (cse_var_705 + j_inner_s_351);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 95) * stride_4) + (cse_var_704 * stride_3))] = (((cse_var_704 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_704)) ? 0.000000e+00f : (((j_inner_s_351 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 95) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_351 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_705 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 95) * width) * 4)) + j_inner_s_351)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 96) < height) {
        for (int32_t j_inner_s_352 = 0; j_inner_s_352 < 128; ++j_inner_s_352) {
          if (((j_outer_5 * 128) + j_inner_s_352) < (width * 4)) {
            int32_t cse_var_707 = (j_outer_5 * 128);
            int32_t cse_var_706 = (cse_var_707 + j_inner_s_352);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 96) * stride_4) + (cse_var_706 * stride_3))] = (((cse_var_706 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_706)) ? 0.000000e+00f : (((j_inner_s_352 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 96) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_352 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_707 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 96) * width) * 4)) + j_inner_s_352)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 97) < height) {
        for (int32_t j_inner_s_353 = 0; j_inner_s_353 < 128; ++j_inner_s_353) {
          if (((j_outer_5 * 128) + j_inner_s_353) < (width * 4)) {
            int32_t cse_var_709 = (j_outer_5 * 128);
            int32_t cse_var_708 = (cse_var_709 + j_inner_s_353);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 97) * stride_4) + (cse_var_708 * stride_3))] = (((cse_var_708 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_708)) ? 0.000000e+00f : (((j_inner_s_353 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 97) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_353 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_709 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 97) * width) * 4)) + j_inner_s_353)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 98) < height) {
        for (int32_t j_inner_s_354 = 0; j_inner_s_354 < 128; ++j_inner_s_354) {
          if (((j_outer_5 * 128) + j_inner_s_354) < (width * 4)) {
            int32_t cse_var_711 = (j_outer_5 * 128);
            int32_t cse_var_710 = (cse_var_711 + j_inner_s_354);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 98) * stride_4) + (cse_var_710 * stride_3))] = (((cse_var_710 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_710)) ? 0.000000e+00f : (((j_inner_s_354 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 98) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_354 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_711 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 98) * width) * 4)) + j_inner_s_354)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 99) < height) {
        for (int32_t j_inner_s_355 = 0; j_inner_s_355 < 128; ++j_inner_s_355) {
          if (((j_outer_5 * 128) + j_inner_s_355) < (width * 4)) {
            int32_t cse_var_713 = (j_outer_5 * 128);
            int32_t cse_var_712 = (cse_var_713 + j_inner_s_355);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 99) * stride_4) + (cse_var_712 * stride_3))] = (((cse_var_712 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_712)) ? 0.000000e+00f : (((j_inner_s_355 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 99) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_355 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_713 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 99) * width) * 4)) + j_inner_s_355)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 100) < height) {
        for (int32_t j_inner_s_356 = 0; j_inner_s_356 < 128; ++j_inner_s_356) {
          if (((j_outer_5 * 128) + j_inner_s_356) < (width * 4)) {
            int32_t cse_var_715 = (j_outer_5 * 128);
            int32_t cse_var_714 = (cse_var_715 + j_inner_s_356);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 100) * stride_4) + (cse_var_714 * stride_3))] = (((cse_var_714 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_714)) ? 0.000000e+00f : (((j_inner_s_356 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 100) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_356 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_715 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 100) * width) * 4)) + j_inner_s_356)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 101) < height) {
        for (int32_t j_inner_s_357 = 0; j_inner_s_357 < 128; ++j_inner_s_357) {
          if (((j_outer_5 * 128) + j_inner_s_357) < (width * 4)) {
            int32_t cse_var_717 = (j_outer_5 * 128);
            int32_t cse_var_716 = (cse_var_717 + j_inner_s_357);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 101) * stride_4) + (cse_var_716 * stride_3))] = (((cse_var_716 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_716)) ? 0.000000e+00f : (((j_inner_s_357 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 101) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_357 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_717 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 101) * width) * 4)) + j_inner_s_357)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 102) < height) {
        for (int32_t j_inner_s_358 = 0; j_inner_s_358 < 128; ++j_inner_s_358) {
          if (((j_outer_5 * 128) + j_inner_s_358) < (width * 4)) {
            int32_t cse_var_719 = (j_outer_5 * 128);
            int32_t cse_var_718 = (cse_var_719 + j_inner_s_358);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 102) * stride_4) + (cse_var_718 * stride_3))] = (((cse_var_718 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_718)) ? 0.000000e+00f : (((j_inner_s_358 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 102) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_358 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_719 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 102) * width) * 4)) + j_inner_s_358)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 103) < height) {
        for (int32_t j_inner_s_359 = 0; j_inner_s_359 < 128; ++j_inner_s_359) {
          if (((j_outer_5 * 128) + j_inner_s_359) < (width * 4)) {
            int32_t cse_var_721 = (j_outer_5 * 128);
            int32_t cse_var_720 = (cse_var_721 + j_inner_s_359);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 103) * stride_4) + (cse_var_720 * stride_3))] = (((cse_var_720 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_720)) ? 0.000000e+00f : (((j_inner_s_359 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 103) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_359 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_721 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 103) * width) * 4)) + j_inner_s_359)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 104) < height) {
        for (int32_t j_inner_s_360 = 0; j_inner_s_360 < 128; ++j_inner_s_360) {
          if (((j_outer_5 * 128) + j_inner_s_360) < (width * 4)) {
            int32_t cse_var_723 = (j_outer_5 * 128);
            int32_t cse_var_722 = (cse_var_723 + j_inner_s_360);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 104) * stride_4) + (cse_var_722 * stride_3))] = (((cse_var_722 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_722)) ? 0.000000e+00f : (((j_inner_s_360 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 104) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_360 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_723 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 104) * width) * 4)) + j_inner_s_360)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 105) < height) {
        for (int32_t j_inner_s_361 = 0; j_inner_s_361 < 128; ++j_inner_s_361) {
          if (((j_outer_5 * 128) + j_inner_s_361) < (width * 4)) {
            int32_t cse_var_725 = (j_outer_5 * 128);
            int32_t cse_var_724 = (cse_var_725 + j_inner_s_361);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 105) * stride_4) + (cse_var_724 * stride_3))] = (((cse_var_724 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_724)) ? 0.000000e+00f : (((j_inner_s_361 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 105) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_361 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_725 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 105) * width) * 4)) + j_inner_s_361)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 106) < height) {
        for (int32_t j_inner_s_362 = 0; j_inner_s_362 < 128; ++j_inner_s_362) {
          if (((j_outer_5 * 128) + j_inner_s_362) < (width * 4)) {
            int32_t cse_var_727 = (j_outer_5 * 128);
            int32_t cse_var_726 = (cse_var_727 + j_inner_s_362);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 106) * stride_4) + (cse_var_726 * stride_3))] = (((cse_var_726 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_726)) ? 0.000000e+00f : (((j_inner_s_362 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 106) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_362 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_727 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 106) * width) * 4)) + j_inner_s_362)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 107) < height) {
        for (int32_t j_inner_s_363 = 0; j_inner_s_363 < 128; ++j_inner_s_363) {
          if (((j_outer_5 * 128) + j_inner_s_363) < (width * 4)) {
            int32_t cse_var_729 = (j_outer_5 * 128);
            int32_t cse_var_728 = (cse_var_729 + j_inner_s_363);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 107) * stride_4) + (cse_var_728 * stride_3))] = (((cse_var_728 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_728)) ? 0.000000e+00f : (((j_inner_s_363 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 107) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_363 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_729 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 107) * width) * 4)) + j_inner_s_363)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 108) < height) {
        for (int32_t j_inner_s_364 = 0; j_inner_s_364 < 128; ++j_inner_s_364) {
          if (((j_outer_5 * 128) + j_inner_s_364) < (width * 4)) {
            int32_t cse_var_731 = (j_outer_5 * 128);
            int32_t cse_var_730 = (cse_var_731 + j_inner_s_364);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 108) * stride_4) + (cse_var_730 * stride_3))] = (((cse_var_730 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_730)) ? 0.000000e+00f : (((j_inner_s_364 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 108) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_364 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_731 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 108) * width) * 4)) + j_inner_s_364)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 109) < height) {
        for (int32_t j_inner_s_365 = 0; j_inner_s_365 < 128; ++j_inner_s_365) {
          if (((j_outer_5 * 128) + j_inner_s_365) < (width * 4)) {
            int32_t cse_var_733 = (j_outer_5 * 128);
            int32_t cse_var_732 = (cse_var_733 + j_inner_s_365);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 109) * stride_4) + (cse_var_732 * stride_3))] = (((cse_var_732 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_732)) ? 0.000000e+00f : (((j_inner_s_365 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 109) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_365 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_733 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 109) * width) * 4)) + j_inner_s_365)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 110) < height) {
        for (int32_t j_inner_s_366 = 0; j_inner_s_366 < 128; ++j_inner_s_366) {
          if (((j_outer_5 * 128) + j_inner_s_366) < (width * 4)) {
            int32_t cse_var_735 = (j_outer_5 * 128);
            int32_t cse_var_734 = (cse_var_735 + j_inner_s_366);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 110) * stride_4) + (cse_var_734 * stride_3))] = (((cse_var_734 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_734)) ? 0.000000e+00f : (((j_inner_s_366 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 110) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_366 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_735 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 110) * width) * 4)) + j_inner_s_366)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 111) < height) {
        for (int32_t j_inner_s_367 = 0; j_inner_s_367 < 128; ++j_inner_s_367) {
          if (((j_outer_5 * 128) + j_inner_s_367) < (width * 4)) {
            int32_t cse_var_737 = (j_outer_5 * 128);
            int32_t cse_var_736 = (cse_var_737 + j_inner_s_367);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 111) * stride_4) + (cse_var_736 * stride_3))] = (((cse_var_736 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_736)) ? 0.000000e+00f : (((j_inner_s_367 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 111) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_367 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_737 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 111) * width) * 4)) + j_inner_s_367)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 112) < height) {
        for (int32_t j_inner_s_368 = 0; j_inner_s_368 < 128; ++j_inner_s_368) {
          if (((j_outer_5 * 128) + j_inner_s_368) < (width * 4)) {
            int32_t cse_var_739 = (j_outer_5 * 128);
            int32_t cse_var_738 = (cse_var_739 + j_inner_s_368);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 112) * stride_4) + (cse_var_738 * stride_3))] = (((cse_var_738 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_738)) ? 0.000000e+00f : (((j_inner_s_368 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 112) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_368 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_739 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 112) * width) * 4)) + j_inner_s_368)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 113) < height) {
        for (int32_t j_inner_s_369 = 0; j_inner_s_369 < 128; ++j_inner_s_369) {
          if (((j_outer_5 * 128) + j_inner_s_369) < (width * 4)) {
            int32_t cse_var_741 = (j_outer_5 * 128);
            int32_t cse_var_740 = (cse_var_741 + j_inner_s_369);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 113) * stride_4) + (cse_var_740 * stride_3))] = (((cse_var_740 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_740)) ? 0.000000e+00f : (((j_inner_s_369 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 113) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_369 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_741 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 113) * width) * 4)) + j_inner_s_369)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 114) < height) {
        for (int32_t j_inner_s_370 = 0; j_inner_s_370 < 128; ++j_inner_s_370) {
          if (((j_outer_5 * 128) + j_inner_s_370) < (width * 4)) {
            int32_t cse_var_743 = (j_outer_5 * 128);
            int32_t cse_var_742 = (cse_var_743 + j_inner_s_370);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 114) * stride_4) + (cse_var_742 * stride_3))] = (((cse_var_742 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_742)) ? 0.000000e+00f : (((j_inner_s_370 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 114) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_370 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_743 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 114) * width) * 4)) + j_inner_s_370)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 115) < height) {
        for (int32_t j_inner_s_371 = 0; j_inner_s_371 < 128; ++j_inner_s_371) {
          if (((j_outer_5 * 128) + j_inner_s_371) < (width * 4)) {
            int32_t cse_var_745 = (j_outer_5 * 128);
            int32_t cse_var_744 = (cse_var_745 + j_inner_s_371);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 115) * stride_4) + (cse_var_744 * stride_3))] = (((cse_var_744 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_744)) ? 0.000000e+00f : (((j_inner_s_371 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 115) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_371 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_745 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 115) * width) * 4)) + j_inner_s_371)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 116) < height) {
        for (int32_t j_inner_s_372 = 0; j_inner_s_372 < 128; ++j_inner_s_372) {
          if (((j_outer_5 * 128) + j_inner_s_372) < (width * 4)) {
            int32_t cse_var_747 = (j_outer_5 * 128);
            int32_t cse_var_746 = (cse_var_747 + j_inner_s_372);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 116) * stride_4) + (cse_var_746 * stride_3))] = (((cse_var_746 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_746)) ? 0.000000e+00f : (((j_inner_s_372 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 116) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_372 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_747 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 116) * width) * 4)) + j_inner_s_372)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 117) < height) {
        for (int32_t j_inner_s_373 = 0; j_inner_s_373 < 128; ++j_inner_s_373) {
          if (((j_outer_5 * 128) + j_inner_s_373) < (width * 4)) {
            int32_t cse_var_749 = (j_outer_5 * 128);
            int32_t cse_var_748 = (cse_var_749 + j_inner_s_373);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 117) * stride_4) + (cse_var_748 * stride_3))] = (((cse_var_748 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_748)) ? 0.000000e+00f : (((j_inner_s_373 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 117) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_373 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_749 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 117) * width) * 4)) + j_inner_s_373)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 118) < height) {
        for (int32_t j_inner_s_374 = 0; j_inner_s_374 < 128; ++j_inner_s_374) {
          if (((j_outer_5 * 128) + j_inner_s_374) < (width * 4)) {
            int32_t cse_var_751 = (j_outer_5 * 128);
            int32_t cse_var_750 = (cse_var_751 + j_inner_s_374);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 118) * stride_4) + (cse_var_750 * stride_3))] = (((cse_var_750 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_750)) ? 0.000000e+00f : (((j_inner_s_374 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 118) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_374 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_751 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 118) * width) * 4)) + j_inner_s_374)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 119) < height) {
        for (int32_t j_inner_s_375 = 0; j_inner_s_375 < 128; ++j_inner_s_375) {
          if (((j_outer_5 * 128) + j_inner_s_375) < (width * 4)) {
            int32_t cse_var_753 = (j_outer_5 * 128);
            int32_t cse_var_752 = (cse_var_753 + j_inner_s_375);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 119) * stride_4) + (cse_var_752 * stride_3))] = (((cse_var_752 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_752)) ? 0.000000e+00f : (((j_inner_s_375 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 119) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_375 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_753 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 119) * width) * 4)) + j_inner_s_375)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 120) < height) {
        for (int32_t j_inner_s_376 = 0; j_inner_s_376 < 128; ++j_inner_s_376) {
          if (((j_outer_5 * 128) + j_inner_s_376) < (width * 4)) {
            int32_t cse_var_755 = (j_outer_5 * 128);
            int32_t cse_var_754 = (cse_var_755 + j_inner_s_376);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 120) * stride_4) + (cse_var_754 * stride_3))] = (((cse_var_754 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_754)) ? 0.000000e+00f : (((j_inner_s_376 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 120) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_376 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_755 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 120) * width) * 4)) + j_inner_s_376)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 121) < height) {
        for (int32_t j_inner_s_377 = 0; j_inner_s_377 < 128; ++j_inner_s_377) {
          if (((j_outer_5 * 128) + j_inner_s_377) < (width * 4)) {
            int32_t cse_var_757 = (j_outer_5 * 128);
            int32_t cse_var_756 = (cse_var_757 + j_inner_s_377);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 121) * stride_4) + (cse_var_756 * stride_3))] = (((cse_var_756 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_756)) ? 0.000000e+00f : (((j_inner_s_377 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 121) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_377 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_757 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 121) * width) * 4)) + j_inner_s_377)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 122) < height) {
        for (int32_t j_inner_s_378 = 0; j_inner_s_378 < 128; ++j_inner_s_378) {
          if (((j_outer_5 * 128) + j_inner_s_378) < (width * 4)) {
            int32_t cse_var_759 = (j_outer_5 * 128);
            int32_t cse_var_758 = (cse_var_759 + j_inner_s_378);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 122) * stride_4) + (cse_var_758 * stride_3))] = (((cse_var_758 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_758)) ? 0.000000e+00f : (((j_inner_s_378 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 122) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_378 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_759 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 122) * width) * 4)) + j_inner_s_378)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 123) < height) {
        for (int32_t j_inner_s_379 = 0; j_inner_s_379 < 128; ++j_inner_s_379) {
          if (((j_outer_5 * 128) + j_inner_s_379) < (width * 4)) {
            int32_t cse_var_761 = (j_outer_5 * 128);
            int32_t cse_var_760 = (cse_var_761 + j_inner_s_379);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 123) * stride_4) + (cse_var_760 * stride_3))] = (((cse_var_760 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_760)) ? 0.000000e+00f : (((j_inner_s_379 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 123) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_379 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_761 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 123) * width) * 4)) + j_inner_s_379)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 124) < height) {
        for (int32_t j_inner_s_380 = 0; j_inner_s_380 < 128; ++j_inner_s_380) {
          if (((j_outer_5 * 128) + j_inner_s_380) < (width * 4)) {
            int32_t cse_var_763 = (j_outer_5 * 128);
            int32_t cse_var_762 = (cse_var_763 + j_inner_s_380);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 124) * stride_4) + (cse_var_762 * stride_3))] = (((cse_var_762 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_762)) ? 0.000000e+00f : (((j_inner_s_380 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 124) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_380 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_763 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 124) * width) * 4)) + j_inner_s_380)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 125) < height) {
        for (int32_t j_inner_s_381 = 0; j_inner_s_381 < 128; ++j_inner_s_381) {
          if (((j_outer_5 * 128) + j_inner_s_381) < (width * 4)) {
            int32_t cse_var_765 = (j_outer_5 * 128);
            int32_t cse_var_764 = (cse_var_765 + j_inner_s_381);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 125) * stride_4) + (cse_var_764 * stride_3))] = (((cse_var_764 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_764)) ? 0.000000e+00f : (((j_inner_s_381 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 125) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_381 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_765 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 125) * width) * 4)) + j_inner_s_381)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 126) < height) {
        for (int32_t j_inner_s_382 = 0; j_inner_s_382 < 128; ++j_inner_s_382) {
          if (((j_outer_5 * 128) + j_inner_s_382) < (width * 4)) {
            int32_t cse_var_767 = (j_outer_5 * 128);
            int32_t cse_var_766 = (cse_var_767 + j_inner_s_382);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 126) * stride_4) + (cse_var_766 * stride_3))] = (((cse_var_766 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_766)) ? 0.000000e+00f : (((j_inner_s_382 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 126) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_382 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_767 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 126) * width) * 4)) + j_inner_s_382)]));
          }
        }
      }
      if ((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 127) < height) {
        for (int32_t j_inner_s_383 = 0; j_inner_s_383 < 128; ++j_inner_s_383) {
          if (((j_outer_5 * 128) + j_inner_s_383) < (width * 4)) {
            int32_t cse_var_769 = (j_outer_5 * 128);
            int32_t cse_var_768 = (cse_var_769 + j_inner_s_383);
            ((float*)outputData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 127) * stride_4) + (cse_var_768 * stride_3))] = (((cse_var_768 < ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) || (((width * 4) - ((0 < ((sizeKernel / 2) & 3)) ? ((sizeKernel / 2) + ((sizeKernel / 2) & 3)) : (sizeKernel / 2))) <= cse_var_768)) ? 0.000000e+00f : (((j_inner_s_383 % 4) == 0) ? ((float*)derivativeData_1)[(((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 127) * stride_1) + (((j_outer_5 * 32) + (j_inner_s_383 >> 2)) * stride))] : ((float*)upsamplingData)[((cse_var_769 + (((((((v__605) < (v__606) ? (v__605) : (v__606)) * 128) + (i_outer_3 * 128)) + 127) * width) * 4)) + j_inner_s_383)]));
          }
        }
      }
    }
  }
  if (TVMBackendFreeWorkspace(1, dev_id, upsamplingData) != 0) {
    return -1;
  }
  if (TVMBackendFreeWorkspace(1, dev_id, inpaddedData) != 0) {
    return -1;
  }
  return 0;
}

// CodegenC: NOTE: Auto-generated entry function
#ifdef __cplusplus
extern "C"
#endif
TVM_DLL int32_t __tvm_main__(void* args, int* arg_type_ids, int num_args, void* out_ret_value, int* out_ret_tcode, void* resource_handle) {
  return filterUpsampling(args, arg_type_ids, num_args, out_ret_value, out_ret_tcode, resource_handle);
}
