#pragma once
#include "uni"
#include <cmath>

namespace solvers{
    using namespace univariate;

    template <typename T>
    constexpr T abs(T x) {
        return (x < 0) ? -x : x;
    }

    template <typename Func, typename T>
    constexpr auto newton(Func f, T x, T y, double epsilon = 1e-6, int max_iterations = 1000) -> T {

        int count = 0;

        while (count < max_iterations) {

            auto fx = f(x);
            auto dfx = differentiate_at(f, x);

            T diff = fx - y;

            if (abs(diff) <= epsilon) {
                break;
            }

            x = x - diff / dfx;
            ++count;
        }

        return x;
    }
}