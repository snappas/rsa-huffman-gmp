
#include "gtest/gtest.h"

TEST(basic_check, test_eq) {
    EXPECT_EQ(1, 1);
}

TEST(basic_check, test_neq) {
    EXPECT_NE(1, 0);
}

TEST(basic_check, TestName) {
    EXPECT_EQ(true, true);
}
