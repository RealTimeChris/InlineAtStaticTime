#include <avx_2/avx_2.hpp>

#if defined(OIML_IS_X86_64)

template<> void function_dispatcher_impl<function_type::test_type, 1>::impl() {
	std::cout << "avx-2 Function Executed\n";
}

#endif
