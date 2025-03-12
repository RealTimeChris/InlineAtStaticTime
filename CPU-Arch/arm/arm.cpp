#include <arm/arm_sve.hpp>
#include <arm/arm_neon.hpp>

#if defined(OIML_IS_ARM64)

template<> void function_dispatcher_impl<function_type::test_type, 1>::impl() {
	std::cout << "arm-neon Function Executed\n";
}

template<> void function_dispatcher_impl<function_type::test_type, 2>::impl() {
	std::cout << "arm-sve Function Executed\n";
}

#endif