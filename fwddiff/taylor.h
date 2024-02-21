#pragma once
#include "uni_differentiate.h"
#include "polynomial.h"

namespace algorithms
{
    using namespace univariate;

    template <typename F, typename TX, typename TA, int degree, int cur_degree>
    requires (cur_degree != 0)
    constexpr auto taylor_eval(const F& f, const TX& x, const TA& a, double coeff)
    {
        if constexpr (cur_degree != degree) {
            coeff /= cur_degree;
            auto term = coeff * f(a) * polynomials::Pow<decltype(x - a), cur_degree>::compute(x - a);
            auto f_next = differentiate(f);
            return term + taylor_eval<decltype(f_next), TX, TA, degree, cur_degree + 1>(f_next, x, a, coeff);
        }
        else {
            coeff /= cur_degree;
            return coeff * f(a) * polynomials::Pow<decltype(x - a), cur_degree>::compute(x - a);
        }
    }

    // Template for starting
    template <typename F, typename TX, typename TA, int degree>
    constexpr auto taylor_eval(F f, const TX& x, const TA& a)
    {
        if constexpr (degree == 0)
        {
            return f(a);
        } else {
            auto f_next = differentiate<decltype(f)>(f);
            return f(a) + taylor_eval<decltype(f_next), TX, TA, degree, 1>(f_next, x, a, 1.0);
        }
    }

    template <int degree, typename F, typename TX, typename TA>
    constexpr auto taylor(const F& f, const TX& x, const TA& a)
    {
        return taylor_eval<F, TX, TA, degree>(f, x, a);
    }
}