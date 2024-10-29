cmake_minimum_required(VERSION 3.28)

project(SparseMatrix
  VERSION 1.0
  DESCRIPTION "Implementing sparse matrix nested sparse ArrayLinkedList"
  LANGUAGES CXX
)

add_subdirectory(sparse_array)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_11)

add_executable(SparseMatrix main.cpp)

target_link_libraries(SparseMatrix PUBLIC compiler_flags ArrayLL)
