#include "polynomial.h"
#include "abstracts.h"
#include <gtest/gtest.h>

class PolynomialTests : public ::testing::Test {
protected:

    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST_F(PolynomialTests, SimpleSecondDegreePolynomial) {
    constexpr polynomials::Polynomial p(1., 4., 3.);
    ASSERT_EQ(p.degree, 2);

    ASSERT_EQ(p(0.), 1);
    ASSERT_EQ(p(1.0), 8);
    ASSERT_EQ(p(-3.0), 16.0);
    ASSERT_EQ(p(-0.5), -0.25);

    constexpr auto static_value = polynomials::static_polynomial(p, 1.5);
    ASSERT_EQ(static_value, 13.75);
    ASSERT_EQ(static_value, p(1.5));
}

TEST_F(PolynomialTests, MissingCoefficents) {
    constexpr polynomials::Polynomial p(-3.0, abstracts::zero(), abstracts::identity());
    ASSERT_EQ(p.degree, 2);

    ASSERT_EQ(p(0.), -3.0);
    ASSERT_EQ(p(1.0), -2.0);
}