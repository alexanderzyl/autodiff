#pragma once
#include "uni_differentiate.h"
#include <cmath>

namespace solvers{
    using namespace univariate;

    template <typename Func, typename T>
    constexpr auto newton(Func f, T x, T y, double epsilon = 1e-6, int max_iterations = 1000) -> T {

        int count = 0;

        while (count < max_iterations) {

            auto fx = f(x);
            auto dfx = differentiate_at(f, x);

            T diff = fx - y;

            if (std::abs(diff) <= epsilon) {
                break;
            }

            x = x - diff / dfx;
            ++count;
        }

        return x;
    }

    template <typename Func, typename T>
    constexpr auto newton_solver(Func f, T x, double epsilon = 1e-6, int max_iterations = 1000) -> T {

        int count = 0;
        auto diff1 = differentiate(f);
        auto diff2 = differentiate(diff1);

        while (count < max_iterations) {
            auto x_updated = x - diff1(x) / diff2(x);
            if (std::abs(x_updated - x) <= epsilon) {
                x = x_updated;
                break;
            }
            x = x_updated;
        }

        return x;
    }
}