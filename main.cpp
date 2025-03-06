#include "cpu_arch.hpp"
#include <unordered_map>

#if defined(OIML_MSVC) || defined(OIML_LINUX)
	#include <immintrin.h>
#endif
#include <vector>

template<typename value_type01, typename value_type02> constexpr value_type01 roundUpToMultiple(value_type01 value, value_type02 multiple) noexcept {
	if ((multiple & (multiple - 1)) == 0) {
		auto mulSub1{ multiple - 1 };
		auto notMulSub1{ ~mulSub1 };
		return (value + (mulSub1)) & notMulSub1;
	} else {
		const auto remainder = value % multiple;
		return remainder == 0 ? value : value + (multiple - remainder);
	}
}

template<typename value_type_new> class alloc_wrapper {
  public:
	using value_type	   = value_type_new;
	using pointer		   = value_type_new*;
	using const_pointer	   = const value_type_new*;
	using reference		   = value_type_new&;
	using const_reference  = const value_type_new&;
	using size_type		   = std::size_t;
	using difference_type  = std::ptrdiff_t;
	using allocator_traits = std::allocator_traits<alloc_wrapper<value_type>>;

	template<typename U> struct rebind {
		using other = alloc_wrapper<U>;
	};

	alloc_wrapper() noexcept = default;

	template<typename U> alloc_wrapper(const alloc_wrapper<U>&) noexcept {
	}

	static pointer allocate(size_type count) noexcept {
		if (count == 0) {
			return nullptr;
		}
		uint64_t alignment{ oiml::aligments[oiml::cpu_arch_index] };
#if defined(OIML_WIN) || defined(OIML_LINUX)
		return static_cast<value_type*>(_mm_malloc(roundUpToMultiple(count * sizeof(value_type), alignment), alignment));
#else
		return static_cast<value_type*>(aligned_alloc(alignment, roundUpToMultiple(count * sizeof(value_type), alignment)));
#endif
	}

	void deallocate(pointer ptr, size_t = 0) noexcept {
		if (ptr) {
#if defined(OIML_WIN) || defined(OIML_LINUX)
			_mm_free(ptr);
#else
			free(ptr);
#endif
		}
	}

	template<typename... arg_types> static void construct(pointer ptr, arg_types&&... args) noexcept {
		if (ptr) {
			new (ptr) value_type(std::forward<arg_types>(args)...);
		}
	}

	static size_type maxSize() noexcept {
		return allocator_traits::max_size(alloc_wrapper{});
	}

	static void destroy(pointer ptr) noexcept {
		ptr->~value_type();
	}
};

int main() {
	std::vector<int32_t, alloc_wrapper<int32_t>> test_vector{};
	std::unordered_map<std::string, std::string> test_map{};
	test_vector.resize(23);
	test_map.reserve(354);
	std::cout << "CPU ARCH INDEX: " << static_cast<uint32_t>(oiml::cpu_arch_index) << std::endl;
	function_dispatcher::impl<function_type::test_type>(oiml::cpu_arch_index);
	return 0;
}
