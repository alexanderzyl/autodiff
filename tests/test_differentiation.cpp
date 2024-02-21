#include <fwddiff/uni>


#include <gtest/gtest.h>

using namespace univariate;

class DifferentiationTests : public ::testing::Test {
protected:
};

TEST_F(DifferentiationTests, x_squared)
{
    constexpr auto f = [](auto x) {
        return x * x;
    };

    EXPECT_EQ(f(2.0), 4.0);
    EXPECT_EQ(differentiate_at(f, 2.0), 4.0);
    EXPECT_EQ(f(1.0), 1.0);
    EXPECT_EQ(differentiate_at(f, 1.0), 2.0);
}


TEST_F(DifferentiationTests, differntial) {
    constexpr auto lambda = [](auto x) {
        return 3.0 * x;
     };

    constexpr double value1 = 2.0;
    constexpr auto derivative1 = differentiate(lambda);
    constexpr auto d1 = derivative1(value1);
    static_assert(d1 != 0.0, "Static differentiation failed");
    EXPECT_EQ(d1, 3.0);

    static_assert(differentiate_at(lambda, value1) == 3.0, "Static differentiation failed");

    constexpr auto derivative2 = differentiate(derivative1);
    constexpr auto d2 = derivative2(value1);
    static_assert(d2 == 0.0, "Static differentiation failed");
    EXPECT_EQ(d2, 0.0);
}

TEST_F(DifferentiationTests, higer_order_differentials) {
    constexpr auto lambda = [](auto x) {
        return  -2.5*x*x*x + 2. * x * x +3.0 * x + 1.5;
    };

    constexpr double value = 1.0;
    constexpr auto result0 = lambda(value);
    EXPECT_EQ(result0, 4.0);
    constexpr auto result1 = differentiate_at(lambda, value);
    constexpr auto derivative1 = differentiate(lambda);
    EXPECT_EQ(result1, derivative1(value));
    EXPECT_EQ(result1, -0.5);

    constexpr auto derivative2 = differentiate(derivative1);
    EXPECT_EQ(derivative2(value), -11.0);

    constexpr auto derivative3 = differentiate(derivative2);
    EXPECT_EQ(derivative3(value), -15.0);

    constexpr auto derivative4 = differentiate(derivative3);
    EXPECT_EQ(derivative4(value), 0.0);

    constexpr auto derivative5 = differentiate(derivative4);
    EXPECT_EQ(derivative5(value), 0.0);
}

TEST_F(DifferentiationTests, sigmoid)
{
    // std::exp is not constexpr, so this result is not compile-time computed
    constexpr auto sigmoid = [](auto x) {
        return 1.0 / (1.0 + exp(-x));
    };

    constexpr double value = 1.0;

    auto result = differentiate_at(sigmoid, value);
    EXPECT_NEAR(result, 0.196612, 0.000001);
}

TEST_F(DifferentiationTests, polynomial)
{
    using namespace polynomials;
    constexpr Polynomial function(1., 4., 3.);
    constexpr Polynomial derivative(4., 6.);

    constexpr double value = 1.0;
    constexpr auto result = differentiate_at(function, value);
    EXPECT_EQ(result, derivative(value));

    constexpr double value2 = 13.3;
    constexpr auto result2 = differentiate_at(function, value2);
    EXPECT_EQ(result2, derivative(value2));
    EXPECT_NEAR(result2, 83.8, 0.000001);

    constexpr double static_value = -2.3;
    constexpr auto static_result = differentiate_at(function, static_value);
    static_assert(static_result != 0.0, "Static differentiation failed");
    EXPECT_EQ(static_result, derivative(static_value));
}
