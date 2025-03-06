#pragma once

#include "detect_isa.hpp"

#if defined(OIML_IS_ARM64)

	#include <arm_sve.h>
	#include <iostream>

OIML_INLINE void impl_02() {
	svfloat32_t va = svdup_f32(1.0f);
	svfloat32_t vb = svdup_f32(2.0f);
	svadd_f32_z(svptrue_b32(), va, vb);
	std::cout << "SVE Function Executed\n";
}

OIML_INLINE void impl_03() {
}

#endif