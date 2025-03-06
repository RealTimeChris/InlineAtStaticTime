#pragma once 

#include "detect_isa.hpp"
#include "cpu_traits.hpp"

enum class function_type { test_type = 0 };

struct function_dispatcher {
	template<function_type, typename... arg_types> static void impl(size_t, arg_types&&...);
};

