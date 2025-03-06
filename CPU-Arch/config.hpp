#pragma once

#include <iostream>

#if defined(__clang__) || (defined(__GNUC__) && defined(__llvm__)) || (defined(__APPLE__) && defined(__clang__))
	#define OIML_CLANG 1
#elif defined(_MSC_VER)
	#define OIML_MSVC 1
	#pragma warning(disable : 4820)
	#pragma warning(disable : 4371)
	#pragma warning(disable : 4710)
	#pragma warning(disable : 4711)
#elif defined(__GNUC__) && !defined(__clang__)
	#define OIML_GNUCXX 1
#endif

#if defined(macintosh) || defined(Macintosh) || (defined(__APPLE__) && defined(__MACH__))
	#define OIML_MAC 1
#elif defined(linux) || defined(__linux) || defined(__linux__) || defined(__gnu_linux__)
	#define OIML_LINUX 1
#elif defined(WIN32) || defined(_WIN32) || defined(_WIN64)
	#define OIML_WIN 1
#endif

#if defined(NDBUG)
	#if defined(OIML_MSVC)
	#define OIML_INLINE [[msvc::forceinline]] inline
#elif defined(OIML_CLANG)
	#define OIML_INLINE inline __attribute__((always_inline))
#elif defined(OIML_GNUCXX)
	#define OIML_INLINE inline __attribute__((always_inline))
#else
	#define OIML_INLINE inline
#endif
#else
	#define OIML_INLINE inline
#endif

#if (defined(__x86_64__) || defined(_M_AMD64)) && !defined(_M_ARM64EC)
	#define OIML_IS_X86_64 1
#elif defined(__aarch64__) || defined(_M_ARM64) || defined(_M_ARM64EC)
	#define OIML_IS_ARM64 1
#endif