#pragma once
#include "functor.h"


namespace multivariate
{
    using std::sin;
    using std::cos;
    using std::exp;

    template<typename F>
    constexpr auto exp(const F& f) {
        return functor([f](auto... v) {
            return exp(f(v...));
        });
    }

    template<typename F>
    constexpr auto sin(const F& f) {
        return functor([f](auto... v) {
            return sin(f(v...));
        });
    }

    template<typename F>
    constexpr auto cos(const F& f) {
        return functor([f](auto... v) {
            return cos(f(v...));
        });
    }
}