#include <malloc.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "zq_cnn_base_operator.h"
#include "../ZQ_CNN_CompileConfig.h"
#if __ARM_NEON
#include <arm_neon.h>
#else
#if defined(__GNUC__)
#if ZQ_CNN_USE_SSETYPE >= ZQ_CNN_SSETYPE_SSE
#include <smmintrin.h>
#endif
#if ZQ_CNN_USE_SSETYPE >= ZQ_CNN_SSETYPE_AVX
#include <x86intrin.h>
#endif
#elif defined(_WIN32)
#if ZQ_CNN_USE_SSETYPE >= ZQ_CNN_SSETYPE_SSE
#include <mmintrin.h> //MMX  
#include <xmmintrin.h> //SSE(include mmintrin.h)  
#include <emmintrin.h> //SSE2(include xmmintrin.h)  
#include <pmmintrin.h> //SSE3(include emmintrin.h)  
#include <tmmintrin.h>//SSSE3(include pmmintrin.h)  
#include <smmintrin.h>//SSE4.1(include tmmintrin.h)  
#include <nmmintrin.h>//SSE4.2(include smmintrin.h)  
#endif 
#if ZQ_CNN_USE_SSETYPE >= ZQ_CNN_SSETYPE_AVX
#include <wmmintrin.h>//AES(include nmmintrin.h)  
#include <immintrin.h>//AVX(include wmmintrin.h)  
#include <intrin.h>//(include immintrin.h)  
#endif
#endif
#endif //__ARM_NEON

#if defined(__cplusplus) || defined(c_plusplus) 
extern "C" {
#endif

#if __ARM_NEON
#define zq_cnn_resize_with_safeborder zq_cnn_resize_with_safeborder_nchwc4
#define zq_cnn_resize_without_safeborder zq_cnn_resize_without_safeborder_nchwc4
#define zq_mm_load_ps vld1q_f32
#define zq_mm_store_ps vst1q_f32
#define zq_mm_set1_ps vdupq_n_f32
#define zq_mm_add_ps vaddq_f32
#define zq_mm_mul_ps vmulq_f32
#define zq_mm_sub_ps vsubq_f32
#define zq_mm_type float32x4_t
#define zq_base_type float
#define zq_mm_align_size 4

#include "zq_cnn_resize_nchwc_raw.h"

#undef zq_cnn_resize_with_safeborder
#undef zq_cnn_resize_without_safeborder
#undef zq_mm_load_ps
#undef zq_mm_store_ps
#undef zq_mm_set1_ps
#undef zq_mm_add_ps
#undef zq_mm_mul_ps
#undef zq_mm_sub_ps
#undef zq_mm_type
#undef zq_base_type
#undef zq_mm_align_size

#else
#if ZQ_CNN_USE_SSETYPE >= ZQ_CNN_SSETYPE_SSE
#define zq_cnn_resize_with_safeborder zq_cnn_resize_with_safeborder_nchwc4
#define zq_cnn_resize_without_safeborder zq_cnn_resize_without_safeborder_nchwc4
#define zq_mm_load_ps _mm_load_ps
#define zq_mm_store_ps _mm_store_ps
#define zq_mm_set1_ps _mm_set1_ps
#define zq_mm_add_ps _mm_add_ps
#define zq_mm_mul_ps _mm_mul_ps
#define zq_mm_sub_ps _mm_sub_ps
#define zq_mm_type __m128
#define zq_base_type float
#define zq_mm_align_size 4

#include "zq_cnn_resize_nchwc_raw.h"

#undef zq_cnn_resize_with_safeborder
#undef zq_cnn_resize_without_safeborder
#undef zq_mm_load_ps
#undef zq_mm_store_ps
#undef zq_mm_set1_ps
#undef zq_mm_add_ps
#undef zq_mm_mul_ps
#undef zq_mm_sub_ps
#undef zq_mm_type
#undef zq_base_type
#undef zq_mm_align_size
#endif

#if ZQ_CNN_USE_SSETYPE >= ZQ_CNN_SSETYPE_AVX
#define zq_cnn_resize_with_safeborder zq_cnn_resize_with_safeborder_nchwc8
#define zq_cnn_resize_without_safeborder zq_cnn_resize_without_safeborder_nchwc8
#define zq_mm_load_ps _mm256_load_ps
#define zq_mm_store_ps _mm256_store_ps
#define zq_mm_set1_ps _mm256_set1_ps
#define zq_mm_add_ps _mm256_add_ps
#define zq_mm_mul_ps _mm256_mul_ps
#define zq_mm_sub_ps _mm256_sub_ps
#define zq_mm_type __m256
#define zq_base_type float
#define zq_mm_align_size 8

#include "zq_cnn_resize_nchwc_raw.h"

#undef zq_cnn_resize_with_safeborder
#undef zq_cnn_resize_without_safeborder
#undef zq_mm_load_ps
#undef zq_mm_store_ps
#undef zq_mm_set1_ps
#undef zq_mm_add_ps
#undef zq_mm_mul_ps
#undef zq_mm_sub_ps
#undef zq_mm_type
#undef zq_base_type
#undef zq_mm_align_size
#endif
#endif//__ARM_NEON


#define zq_cnn_resize_with_safeborder zq_cnn_resize_with_safeborder_nchwc1
#define zq_cnn_resize_without_safeborder zq_cnn_resize_without_safeborder_nchwc1
#define zq_mm_load_ps my_mm_load_ps
#define zq_mm_store_ps my_mm_store_ps
#define zq_mm_set1_ps my_mm_set1_ps
#define zq_mm_add_ps my_mm_add_ps
#define zq_mm_mul_ps my_mm_mul_ps
#define zq_mm_sub_ps my_mm_sub_ps
#define zq_mm_type float
#define zq_base_type float
#define zq_mm_align_size 1

#include "zq_cnn_resize_nchwc_raw.h"

#undef zq_cnn_resize_with_safeborder
#undef zq_cnn_resize_without_safeborder
#undef zq_mm_load_ps
#undef zq_mm_store_ps
#undef zq_mm_set1_ps
#undef zq_mm_add_ps
#undef zq_mm_mul_ps
#undef zq_mm_sub_ps
#undef zq_mm_type
#undef zq_base_type
#undef zq_mm_align_size

#if defined(__cplusplus) || defined(c_plusplus) 
}
#endif