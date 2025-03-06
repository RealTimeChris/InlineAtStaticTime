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

target_compile_options(
	"BenchmarkExe" PUBLIC
	"$<$<CXX_COMPILER_ID:MSVC>:$<$<STREQUAL:${ASAN_ENABLED},TRUE>:/fsanitize=address>>"
     "$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:CLANG>>:-Wuninitialized;-Wconversion;-Wpedantic;-Wshadow;-Wextra;-Wall;-flto>"
    "$<$<CXX_COMPILER_ID:GNU>:-Wnull-dereference;-Wuninitialized;-Wconversion;-Wpedantic;-Wshadow;-Wextra;-Wall;-flto>"
	"$<$<CXX_COMPILER_ID:MSVC>:/Wall;/W4;/GL>"
)

target_link_options(
	"BenchmarkExe" PUBLIC
	"$<$<CXX_COMPILER_ID:GNU>:$<$<STREQUAL:${ASAN_ENABLED},TRUE>:-fsanitize=address>>"
    "$<$<CXX_COMPILER_ID:GNU>:-flto>"
	"$<$<CXX_COMPILER_ID:Clang>:-flto>"
	"$<$<CXX_COMPILER_ID:MSVC>:/LTCG>"
)

add_subdirectory(CPU-Arch)


target_link_libraries(
	"BenchmarkExe" PUBLIC CPU-Arch
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

