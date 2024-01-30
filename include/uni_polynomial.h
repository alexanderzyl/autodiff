#pragma once
#include "uni_dual.h"
#include "polynomial.h"
#include "abstracts.h"

namespace polynomials{
    using namespace univariate;
    // Derivative of a polynomial. d(x^n) = n*x^(n-1)*dx
    template<typename FX, typename FDX, unsigned int exp>
    struct Pow<dual<FX, FDX>, exp>
    {
        static constexpr auto compute(dual<FX, FDX> base)
        {
            auto x = [base](auto value) {
                return Pow<decltype(base.x(value)), exp>::compute(base.x(value));
            };
            auto dx = [base](auto value) {
                return exp * Pow<decltype(base.x(value)), exp - 1>::compute(base.x(value)) * base.dx(value);
            };
            return dual{x, dx};
        }
    };

    template<typename FX, typename FDX>
    struct Pow<dual<FX, FDX>, 0>
    {
        static constexpr auto compute(dual<FX, FDX>& base)
        {
            auto x = [base](auto value) {
                return abstracts::identity{};
            };
            auto dx = [base](auto value) {
                return abstracts::zero{};
            };
            return dual{x, dx};
        }
    };

}// namespace polynomials