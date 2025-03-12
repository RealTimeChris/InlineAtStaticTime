#include <avx_512/avx_512.hpp>

#if defined(OIML_IS_X86_64)

template<> void function_dispatcher_impl<function_type::test_type, 2>::impl() {
	std::cout << "avx-512 Function Executed\n";
}

#endif
