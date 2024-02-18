#pragma once
#include "functor.h"

namespace multivariate
{
    template<typename F>
    constexpr auto exp(const F& f) {
        return functor([f](auto... v) {
            return std::exp(f(v...));
        });
    }
}