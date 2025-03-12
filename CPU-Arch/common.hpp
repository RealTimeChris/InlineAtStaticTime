#pragma once
#include "detect_isa.hpp"
#include "config.hpp"

#if defined(OIML_IS_X86_64)

#include <immintrin.h>

inline __m256 __avx_f32cx8_load(const uint16_t* x) {
	alignas(32) float tmp[8]{};

	for (int i = 0; i < 8; i++) {
		tmp[i] = x[i];
	}

	return _mm256_load_ps(tmp);
}

inline void __avx_f32cx8_store(uint16_t* x, __m256 y) {
	float arr[8];

	_mm256_storeu_ps(arr, y);

	for (int i = 0; i < 8; i++)
		x[i] = (arr[i]);
}

inline static void impl(int n, float* __restrict s, const uint16_t* __restrict x, const uint16_t* __restrict y, int nrc) {
	( void )(nrc);

	float sumf = 0.0;

	const int np = (n & ~(32 - 1));

	__m256 sum[(32 / 8)]{};

	__m256 ax[(32 / 8)];
	__m256 ay[(32 / 8)];
	for (int i = 0; i < np; i += 32) {
		for (int j = 0; j < (32 / 8); j++) {
			ax[j]  = __avx_f32cx8_load(x + i + j * 8);
			ay[j]  = __avx_f32cx8_load(y + i + j * 8);
			sum[j] = _mm256_add_ps(_mm256_mul_ps(ax[j], ay[j]), sum[j]);
		}
	}
	int offset = (32 / 8) >> 1;
	for (int i = 0; i < offset; ++i) {
		sum[i] = _mm256_add_ps(sum[i], sum[offset + i]);
	}
	offset >>= 1;
	for (int i = 0; i < offset; ++i) {
		sum[i] = _mm256_add_ps(sum[i], sum[offset + i]);
	}
	offset >>= 1;
	for (int i = 0; i < offset; ++i) {
		sum[i] = _mm256_add_ps(sum[i], sum[offset + i]);
	}
	const __m128 t0 = _mm_add_ps(_mm256_castps256_ps128(sum[0]), _mm256_extractf128_ps(sum[0], 1));
	const __m128 t1 = _mm_hadd_ps(t0, t0);
	sumf			= ( float )_mm_cvtss_f32(_mm_hadd_ps(t1, t1));
	// leftovers
	for (int i = np; i < n; ++i) {
		sumf += ( float )((x[i]) * (y[i]));
	}

	*s = sumf;
}
#else

#include <arm_neon.h>
#include <arm_sve.h>

#endif

enum class function_type { test_type = 0 };

template<function_type type, size_t index> struct function_dispatcher_impl {
	static void impl();
};
