#include "cpu_arch.hpp"

#include <cpu_arch.hpp>
#include <arm_neon.hpp>
#include <arm_sve.hpp>
#include <avx_512.hpp>
#include <avx_2.hpp>
#include <avx.hpp>
#include <unordered_map>

int main() {
	std::unordered_map<std::string, std::string> test_map{};
	test_map.reserve(354);
	test_map.rehash(23);
	std::cout << "CPU ARCH INDEX: " << oiml::cpu_arch_index << std::endl;
	impl_test_function_01(oiml::cpu_arch_index);
	return 0;
}
void impl_test_function_01(size_t index) {
	if (index == 0) {
		std::cout << "Index 0: " << std::endl;
		impl_01();
	} else if (index == 1) {
		std::cout << "Index 1: " << std::endl;
		impl_02();
	} else if (index == 2) {
		std::cout << "Index 2: " << std::endl;
		impl_03();
	}
}