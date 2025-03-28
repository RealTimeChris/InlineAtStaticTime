﻿file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
project(oiml_cpu)

add_subdirectory(arm)
add_subdirectory(avx_2)
add_subdirectory(avx_512)

add_library(
  "oiml_cpu" 
  INTERFACE
  "${HEADERS}"
)
set_target_properties(oiml_cpu PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library("oiml_cpu::oiml_cpu" ALIAS "oiml_cpu")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi ${AVX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /OPT:REF /OPT:ICF")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /OPT:REF /OPT:ICF")

    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi /DEBUG /ZI ${AVX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /DEBUG")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} /DEBUG")
endif()

if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|amd64|AMD64|i[3-6]86")
    message(STATUS "Architecture: x86_64")
    set(OIML_COMPILE_OPTIONS     
        "$<$<STREQUAL:$<LOWER_CASE:$<CXX_COMPILER_ID>>,gnu>:-Wnull-dereference;-Wuninitialized;-Wconversion;-Wpedantic;-Wshadow;-Wextra;-Wall;-Wno-narrowing>"
        "$<$<STREQUAL:$<LOWER_CASE:$<CXX_COMPILER_ID>>,clang>:-Wnull-dereference;-Wuninitialized;-Wconversion;-Wpedantic;-Wshadow;-Wextra;-Wall;-Wno-narrowing>"
        "$<$<STREQUAL:$<LOWER_CASE:$<CXX_COMPILER_ID>>,msvc>:/Wall;/W4;/Zi;/DNDBUG;/Zc:preprocessor;/permissive;/Zc:lambda;/bigobj;/Gy>"
    )
    set(OIML_LINK_OPTIONS 
        "$<$<STREQUAL:$<LOWER_CASE:$<CXX_COMPILER_ID>>,gnu>:-flto;-Wl,-O2>"
        "$<$<STREQUAL:$<LOWER_CASE:$<CXX_COMPILER_ID>>,clang>:-flto;-Wl,-O2>"
        "$<$<STREQUAL:$<LOWER_CASE:$<CXX_COMPILER_ID>>,msvc>:/OPT:REF;/OPT:ICF;/INCREMENTAL:NO;/LTCG>"
    )
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm64|ARM.*")  
    message(STATUS "Architecture: arm64")
    set(OIML_COMPILE_OPTIONS     
        "$<$<STREQUAL:$<LOWER_CASE:$<CXX_COMPILER_ID>>,appleclang>:-Wnull-dereference;-Wuninitialized;-Wconversion;-Wpedantic;-Wshadow;-Wextra;-Wall;-Wno-narrowing>"
        "$<$<STREQUAL:$<LOWER_CASE:$<CXX_COMPILER_ID>>,clang>:-Wnull-dereference;-Wuninitialized;-Wconversion;-Wpedantic;-Wshadow;-Wextra;-Wall;-Wno-narrowing>"
        "$<$<STREQUAL:$<LOWER_CASE:$<CXX_COMPILER_ID>>,gnu>:-Wnull-dereference;-Wuninitialized;-Wconversion;-Wpedantic;-Wshadow;-Wextra;-Wall;-Wno-narrowing>"
    )
    set(OIML_LINK_OPTIONS 
        "$<$<STREQUAL:$<LOWER_CASE:$<CXX_COMPILER_ID>>,gnu>:-flto;-Wl,-O2>"
        "$<$<STREQUAL:$<LOWER_CASE:$<CXX_COMPILER_ID>>,clang>:-flto;-Wl,-O2>"
        "$<$<STREQUAL:$<LOWER_CASE:$<CXX_COMPILER_ID>>,appleclang>:-flto;-Wl,-O2>"
    )
else()
    message(STATUS "Architecture: Unknown")
endif()

target_compile_options(
    "oiml_cpu" INTERFACE
    "${OIML_COMPILE_OPTIONS}"
)

target_link_libraries("oiml_cpu" INTERFACE "oiml_cpu_arm" "oiml_cpu_avx_2" "oiml_cpu_avx_512")

target_link_options(
    "oiml_cpu" INTERFACE "${OIML_LINK_OPTIONS}"
)

target_include_directories(
    "oiml_cpu" INTERFACE 
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
    "$<INSTALL_INTERFACE:/include>"
)