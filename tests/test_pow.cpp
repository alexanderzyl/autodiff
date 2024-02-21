#include <gtest/gtest.h>
#include <fwddiff/pow.h>

using namespace univariate;

class TestPow : public ::testing::Test {

};

TEST_F(TestPow, square) {
    constexpr auto result1 = pow<2>(2.5);
    static_assert(result1 != 0.0, "Static evaluation failed");
    EXPECT_NEAR(result1, 6.25, 1e-7);

    constexpr auto result2 = pow<2>(-2.5);
    EXPECT_NEAR(result2, 6.25, 1e-7);

    constexpr auto result3 = pow<2>(5);
    EXPECT_EQ(result3, 25);
}

TEST_F(TestPow, cube) {
    constexpr auto result1 = pow<3>(2.5);
    EXPECT_NEAR(result1, 15.625, 1e-7);

    constexpr auto result2 = pow<3>(-2.5);
    EXPECT_NEAR(result2, -15.625, 1e-7);

    constexpr auto result3 = pow<3>(5);
    EXPECT_EQ(result3, 125);
}

TEST_F(TestPow, ones) {
    constexpr auto result1 = pow<1>(2.5);
    EXPECT_NEAR(result1, 2.5, 1e-7);

    constexpr auto result2 = pow<1>(-2.5);
    EXPECT_NEAR(result2, -2.5, 1e-7);

    constexpr auto result3 = pow<1>(5);
    EXPECT_EQ(result3, 5);

    constexpr auto result4 = pow<1>(1.);
    EXPECT_EQ(result4, 1);

    constexpr auto result5 = pow<1>(1.);
    EXPECT_EQ(result5, 1);
}

TEST_F(TestPow, zero) {

    constexpr auto result1 = pow<0>(2.5);
    EXPECT_EQ(result1, 1);

    constexpr auto result2 = pow<0>(5);
    EXPECT_EQ(result2, 1);

    constexpr auto result3 = pow<0>(1);
    EXPECT_EQ(result3, 1);

    constexpr auto result4 = pow<0>(0.);
    EXPECT_EQ(result4, 1.);

    constexpr auto result5 = pow<0>(0);
    EXPECT_EQ(result5, 1.);

    constexpr auto result6 = pow<0>(-2.5);
    EXPECT_EQ(result6, 1);

    constexpr auto result7 = pow<0>(-5);
    EXPECT_EQ(result7, 1);
}

TEST_F(TestPow, negative_one) {
    constexpr auto result1 = pow<-1>(2.5);
    EXPECT_NEAR(result1, 0.4, 1e-7);

    constexpr auto result2 = pow<-1>(5);
    EXPECT_EQ(result2, 0);

    constexpr auto result3 = pow<-1>(1);
    EXPECT_EQ(result3, 1);

    constexpr auto result4 = pow<-1>(0.);
    EXPECT_EQ(result4, std::numeric_limits<double>::infinity());

    constexpr auto result5 = pow<-1>(0);
    EXPECT_EQ(result5, std::numeric_limits<int>::infinity());

    constexpr auto result6 = pow<-1>(-2.5);
    EXPECT_NEAR(result6, -0.4, 1e-7);

    constexpr auto result7 = pow<-1>(-5);
    EXPECT_EQ(result7, 0);

    constexpr auto result8 = pow<-1>(-1.0);
    EXPECT_EQ(result8, -1.0);
}

TEST_F(TestPow, negative_two) {
    constexpr auto result1 = pow<-2>(2.5);
    EXPECT_NEAR(result1, 0.16, 1e-7);

    constexpr auto result2 = pow<-2>(5);
    EXPECT_EQ(result2, 0);

    constexpr auto result3 = pow<-2>(1);
    EXPECT_EQ(result3, 1);

    constexpr auto result4 = pow<-2>(0.);
    EXPECT_EQ(result4, std::numeric_limits<double>::infinity());

    constexpr auto result5 = pow<-2>(0);
    EXPECT_EQ(result5, std::numeric_limits<int>::infinity());

    constexpr auto result6 = pow<-2>(-2.5);
    EXPECT_NEAR(result6, 0.16, 1e-7);

    constexpr auto result7 = pow<-2>(-5);
    EXPECT_EQ(result7, 0);
}

TEST_F(TestPow, negative_three) {
    constexpr auto result1 = pow<-3>(2.5);
    EXPECT_NEAR(result1, 0.064, 1e-7);

    constexpr auto result2 = pow<-3>(5);
    EXPECT_EQ(result2, 0);

    constexpr auto result3 = pow<-3>(1);
    EXPECT_EQ(result3, 1);

    constexpr auto result4 = pow<-3>(0.);
    EXPECT_EQ(result4, std::numeric_limits<double>::infinity());

    constexpr auto result5 = pow<-3>(0);
    EXPECT_EQ(result5, std::numeric_limits<int>::infinity());

    constexpr auto result6 = pow<-3>(-2.5);
    EXPECT_NEAR(result6, -0.064, 1e-7);

    constexpr auto result7 = pow<-3>(-5);
    EXPECT_EQ(result7, 0);
}