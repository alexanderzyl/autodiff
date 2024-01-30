#include "differentiate.h"
#include <gtest/gtest.h>

class TestClass : public ::testing::Test {
protected:
};

TEST_F(TestClass, TestName) {
    auto lambda = [](auto x) {
        return  2. * x * x +3.0 * x + 3.0;
    };
    double value = 5.0;
    auto result = differentiate(lambda, value);
    EXPECT_EQ(result, 23.0);
}