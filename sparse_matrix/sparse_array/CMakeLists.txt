cmake_minimum_required(VERSION 3.28)

project(SparceArray VERSION 1.0 DESCRIPTION "Implementing sparce array using linked list" LANGUAGES CXX)

add_library(ArrayLL STATIC array_linked_list.hpp)
set_target_properties(ArrayLL PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(ArrayLL INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(SparseArray main.cpp)
target_link_libraries(SparseArray PUBLIC compiler_flags)

