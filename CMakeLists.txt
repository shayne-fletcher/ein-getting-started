# SPDX-FileType: Source
# SPDX-FileCopyrightText: 2024 Shayne Fletcher <hayne@shaynefletcher.org>
# SPDX-License-Identifier: BSD-2-Clause OR Apache-2.0

cmake_minimum_required(VERSION 3.30.5 FATAL_ERROR)
cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})

set(PROJECT_BRIEF "SIMD Tools Getting Started")

project(ein_getting_started)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_EXPERIMENTAL_CXX_MODULES TRUE)
set(CMAKE_CXX_SCAN_FOR_MODULES TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CXX_Clang "$<COMPILE_LANG_AND_ID:CXX,AppleClang,Clang>")
set(CXX_Gcc "$<COMPILE_LANG_AND_ID:CXX,GNU>")
set(CXX_GccOrClang "$<COMPILE_LANG_AND_ID:CXX,AppleClang,Clang,GNU>")
set(Link_Clang "$<LINK_LANG_AND_ID:CXX,AppleClang,Clang>")
set(Link_Gcc "$<COMPILE_LANG_AND_ID:CXX,GNU>")
set(Link_GccOrClang "$<LINK_LANG_AND_ID:CXX,AppleClang,Clang,GNU>")

# add lots of debug info to Debug builds
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-O0 -g3 -ggdb3 -gcolumn-info -gembed-source")

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/h)

set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/lib")

include(FetchContent)

FetchContent_Declare(
  ein
  GIT_REPOSITORY https://github.com/ekmett/ein.git
  GIT_TAG sf-ein-getting-started
)

FetchContent_MakeAvailable(ein)

message("CMAKE_BINARY_DIR/h = ${CMAKE_BINARY_DIR}/h")

file(MAKE_DIRECTORY "${ein_BINARY_DIR}/h")
message("ein_BINARY_DIR/h = ${ein_BINARY_DIR}/h")

target_include_directories(ein INTERFACE "${CMAKE_BINARY_DIR}/h")
target_include_directories(ein INTERFACE "${ein_BINARY_DIR}/h")

configure_file(
  "${ein_SOURCE_DIR}/h/config.hpp.in"
  "${ein_BINARY_DIR}/h/config.hpp"
)

# # Copy headers to the binary directory
# add_custom_target(ein_headers
#     COMMAND ${CMAKE_COMMAND} -E copy_directory ${ein_SOURCE_DIR}/h ${ein_BINARY_DIR}/h
#     COMMENT "Copying header files to build directory"
# )

# Make sure headers are generated before compiling ein
# add_dependencies(ein ein_headers)

# Set the include directories for ein
target_include_directories(ein PUBLIC "${CMAKE_BINARY_DIR}/h")
target_include_directories(ein PUBLIC "${ein_BINARY_DIR}/h")
target_include_directories(ein PUBLIC "${ein_BINARY_DIR}/lib/h")
message("cmake binary dir = ${cmake_BINARY_DIR}/h")
message("binary dir = ${ein_BINARY_DIR}/h")

add_executable(ein_getting_started src/ein_getting_started.cpp)
# Ensure to add the directory containing the module files (.pcm)
target_include_directories(ein_getting_started PRIVATE "${CMAKE_SOURCE_DIR}/lib/ein-build/src/CMakeFiles/ein.dir")
target_link_libraries(ein_getting_started PRIVATE ein)

target_compile_options(ein_getting_started PUBLIC "$<${CXX_GccOrClang}:-std=c++23>") # why isn't this being set?!
target_compile_options(ein_getting_started PUBLIC "$<${CXX_GccOrClang}:-msse4.2;-mavx;-mbmi2;-mfma;-mavx2;-ftree-vectorize;-funroll-loops>")
# target_compile_options(ein PUBLIC "$<${CXX_GccOrClang}:-mavx512f;-mavx512dq;-mavx512bw;-mavx512vl;-mavx512vbmi2;-mavx512vp2intersect;-mavx512bf16>")
# target_compile_options(ein PUBLIC "$<${CXX_GccOrClang}:-Wno-unqualified-std-cast-call>")
