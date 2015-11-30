include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runHuffmanTests basic_check.cpp huffmantree_check.cpp huffmancode_check.cpp)

target_link_libraries(runHuffmanTests gtest gtest_main)
target_link_libraries(runHuffmanTests Huffman)