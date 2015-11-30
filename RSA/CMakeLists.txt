cmake_minimum_required(VERSION 3.3)
project(RSA)

add_definitions(-std=gnu++11)

include_directories(Huffman)

set(HEADER_FILES RSA.h)

set(SOURCE_FILES RSA.cpp)

add_library(RSA STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(RSA gmpxx gmp Huffman)
