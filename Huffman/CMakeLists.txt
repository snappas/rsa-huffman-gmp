cmake_minimum_required(VERSION 3.3)
project(Huffman)

add_definitions(-std=gnu++11)
#include_directories(Huffman)

set(HEADER_FILES HuffmanTree.h)

set(SOURCE_FILES HuffmanTree.cpp nonconst_priority_queue.h HuffmanCode.cpp HuffmanCode.h)

add_library(Huffman STATIC ${SOURCE_FILES} ${HEADER_FILES})

#target_link_libraries(RSA gmpxx gmp)