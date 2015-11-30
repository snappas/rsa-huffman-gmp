cmake_minimum_required(VERSION 3.3)
project(gmp_rsa)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L C:/Users/Ryan/ClionProjects/gmp-rsa")

add_definitions(-std=gnu++11)
#add_definitions()

set(SOURCE_FILES main.cpp)


add_executable(gmp_rsa ${SOURCE_FILES})

include_directories(RSA)
include_directories(Huffman)

add_subdirectory(tests)
add_subdirectory(RSA)
add_subdirectory(Huffman)

target_link_libraries(gmp_rsa RSA Huffman)