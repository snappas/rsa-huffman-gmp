include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runRSATests basic_check.cpp rsa_check.cpp)

target_link_libraries(runRSATests gtest gtest_main)
target_link_libraries(runRSATests RSA)