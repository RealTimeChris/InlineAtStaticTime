#pragma once

#include <detect_isa.hpp>

#pragma once

#include <fallback.hpp>
#include <cpu_arch.hpp>
#include <arm_neon.hpp>
#include <arm_sve.hpp>
#include <avx_512.hpp>
#include <avx_2.hpp>
#include <avx.hpp>


template<function_type type, typename... arg_types> void function_dispatcher::impl(size_t index, arg_types&&... args) {
	static_assert(sizeof...(args) == 1, "impl expects exactly one argument!");

	auto first_arg = (static_cast<uint32_t>(args), ...);// Extract first argument
	switch (first_arg) {
		case 0:
			return impl_00();
		case 1:
			return impl_01();
		case 2:
			return impl_02();
		case 3:
			return impl_03();
	}
}

template<> void function_dispatcher::impl<function_type::test_type>(size_t index) {

	switch (index) {
		case 0:
			return impl_00();
		case 1:
			return impl_01();
		case 2:
			return impl_02();
		case 3:
			return impl_03();
	}
}
