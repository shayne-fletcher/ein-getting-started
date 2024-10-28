# SPDX-FileType: Source
# SPDX-FileCopyrightText: 2024 Edward Kmett <ekmett@gmail.com>
# SPDX-FileCopyrightText: 2024 Shayne Fletcher <shayne@shaynefletcher.org>
# SPDX-License-Identifier: BSD-2-Clause OR Apache-2.0

cmake_minimum_required(VERSION 3.30.5 FATAL_ERROR)
cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})

set(PROJECT_BRIEF "getting started with ein")

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

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-O0 -g3 -ggdb3 -gcolumn-info -gembed-source")

set(CXX_Clang "$<COMPILE_LANG_AND_ID:CXX,AppleClang,Clang>")
set(CXX_Gcc "$<COMPILE_LANG_AND_ID:CXX,GNU>")
set(CXX_GccOrClang "$<COMPILE_LANG_AND_ID:CXX,AppleClang,Clang,GNU>")

set(Link_Clang "$<LINK_LANG_AND_ID:CXX,AppleClang,Clang>")
set(Link_Gcc "$<COMPILE_LANG_AND_ID:CXX,GNU>")
set(Link_GccOrClang "$<LINK_LANG_AND_ID:CXX,AppleClang,Clang,GNU>")

set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/lib")

include(FetchContent)

FetchContent_Declare(
  ein
  GIT_REPOSITORY https://github.com/ekmett/ein.git
  GIT_TAG sf-external-builds-more
)

FetchContent_MakeAvailable(ein)

target_include_directories(ein PUBLIC "${ein_BINARY_DIR}/h")

set(exes
  "ein_getting_started:src/ein_getting_started.cpp"
)
foreach(EXECUTABLE_ITEM ${exes})
  string(REPLACE ":" ";" EXECUTABLE_INFO ${EXECUTABLE_ITEM})
  list(GET EXECUTABLE_INFO 0 exe)
  list(GET EXECUTABLE_INFO 1 src)

  add_executable(${exe} ${src})

  target_compile_options(${exe} PUBLIC "$<${CXX_GccOrClang}:-std=c++23>")
  target_compile_options(${exe} PUBLIC "$<${CXX_GccOrClang}:-msse4.2;-mavx;-mbmi2;-mfma;-mavx2;-ftree-vectorize;-funroll-loops>")

  target_link_libraries(${exe} PRIVATE ein)

endforeach()
