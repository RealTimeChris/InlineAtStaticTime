cmake_minimum_required(VERSION 3.18)

project(
  "BenchmarkExe"
  VERSION "1.0.0"
  LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

add_executable(
  "BenchmarkExe" 
  "./main.cpp"
)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|amd64|AMD64|i[3-6]86")  
    message(STATUS "Architecture: x86_64")
    set(OIML_COMPILE_OPTIONS 
        "$<$<CXX_COMPILER_ID:MSVC>:/Wall;/W4;/arch:AVX;/arch:AVX2;/arch:AVX512;/GL>"
        "$<$<CXX_COMPILER_ID:GNU>:-Wnull-dereference;-Wuninitialized;-Wconversion;-Wpedantic;-Wshadow;-Wextra;-Wall;-mavx512f;-mfma;-mavx2;-mavx;-flto>"
        "$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:clang>,$<CXX_COMPILER_ID:CLANG>>:-Wuninitialized;-Wconversion;-Wpedantic;-Wshadow;-Wextra;-Wall;-mavx512f;-mfma;-mavx2;-mavx;-flto>"
    )
    set(OIML_LINK_OPTIONS 
        "$<$<CXX_COMPILER_ID:GNU>:-flto>"
        "$<$<CXX_COMPILER_ID:Clang>:-flto>"
        "$<$<CXX_COMPILER_ID:MSVC>:/LTCG>"
    )
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm64|ARM.*")  
    message(STATUS "Architecture: arm64")
    set(OIML_COMPILE_OPTIONS 
        "$<$<CXX_COMPILER_ID:GNU>:-Wnull-dereference;-Wuninitialized;-Wconversion;-Wpedantic;-Wshadow;-Wextra;-Wall;-march=armv8.2-a+sve+sve2+simd>"
        "$<$<CXX_COMPILER_ID:AppleClang>:-Wnull-dereference;-Wuninitialized;-Wconversion;-Wpedantic;-Wshadow;-Wextra;-Wall;-march=armv8.2-a+sve+sve2+simd>"
        "$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:clang>,$<CXX_COMPILER_ID:CLANG>>:-Wuninitialized;-Wconversion;-Wpedantic;-Wshadow;-Wextra;-Wall;-march=armv8.2-a+sve+sve2+simd>"
    )
    set(OIML_LINK_OPTIONS 
        "$<$<CXX_COMPILER_ID:GNU>:-flto>"
        "$<$<CXX_COMPILER_ID:Clang>:-flto>"
        "$<$<CXX_COMPILER_ID:MSVC>:/LTCG>"
    )
else()
    message(STATUS "Architecture: Unknown")
endif()

target_compile_options(
    "BenchmarkExe" PRIVATE 
    "${OIML_COMPILE_OPTIONS}"
)

target_link_options(
    "BenchmarkExe" PRIVATE 
    "${OIML_LINK_OPTIONS}"
)

target_include_directories(
	"BenchmarkExe" PUBLIC
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/CPU-Arch>"
    "$<INSTALL_INTERFACE:/include>"
)

if (WIN32)
	install(
		FILES 
		"$<TARGET_PDB_FILE:BenchmarkExe>"
		DESTINATION "$<IF:$<CONFIG:Debug>,bin,bin>"
		OPTIONAL
	)
endif()

install(
	FILES 
	"$<TARGET_FILE:BenchmarkExe>"
	DESTINATION "$<IF:$<CONFIG:Debug>,bin,bin>"
	OPTIONAL
)

