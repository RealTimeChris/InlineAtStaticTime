#pragma once
#include "common.hpp"
#include <detect_isa.hpp>
#include <assert.h>
#include <cassert>

template<> inline void function_dispatcher_impl<function_type::test_type, 0>::impl() {
	std::cout << "x86-fallback Function Executed\n";
}
