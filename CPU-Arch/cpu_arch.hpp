#pragma once 
#include "common.hpp"
#include "detect_isa.hpp"
#include "cpu_traits.hpp"
#include "fallback.hpp"

struct function_dispatcher {
	template<function_type type, typename... arg_types>
	static auto impl(size_t index, arg_types&&... args) {
		switch (index) {
			case 0:
				return function_dispatcher_impl<function_type::test_type, 0>::impl();
			case 1:
				return function_dispatcher_impl<function_type::test_type, 1>::impl();
			case 2:
				return function_dispatcher_impl<function_type::test_type, 2>::impl();
		}
	}
};
