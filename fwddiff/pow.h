#pragma once
#include <type_traits>
#include <cmath>
#include <stdexcept>

namespace univariate
{
    template <int N, typename T>
    requires std::is_arithmetic_v<T>
    constexpr auto pow(T x) {
        if constexpr (N == 0) {
            return 1;
        }
        else if constexpr (N == 1) {
            return x;
        }
        else if constexpr (N > 1) {
            if constexpr (N % 2 == 0) {
                return pow<N / 2>(x) * pow<N / 2>(x);
            }
            else {
                return x * pow<N - 1>(x);
            }
        }
        else {
            if (x == 0) {
                return std::numeric_limits<T>::infinity();
            }
            return 1 / pow<-N>(x);
        }
    }
}