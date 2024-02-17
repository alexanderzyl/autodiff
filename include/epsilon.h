#pragma once
#include "functor.h"

namespace multivariate
{
    struct epsilon {
        static constexpr bool is_functor = true;
        template<typename ...V>
        constexpr auto operator()(V... v) const {
            return 1.0;
        }
    };
    struct zero {
        static constexpr bool is_functor = true;
        template<typename ...V>
        constexpr auto operator()(V... v) const {
            return 0.0;
        }
    };

    constexpr auto operator+(const zero& a, const zero& b) {
        return zero{};
    }

    constexpr auto operator+(const epsilon& a, const zero& b) {
        return epsilon{};
    }

    constexpr auto operator+(const zero& a, const epsilon& b) {
        return epsilon{};
    }

    // arithmetics for _functor and _epsilon
    template<typename F>
    constexpr auto operator*(const functor<F>& a, const epsilon& b) {
        return a;
    }

    template<typename F>
    constexpr auto operator*(const epsilon& a, const functor<F>& b) {
        return b;
    }

    // arithmetics for _functor and _zero
    template<typename F>
    constexpr auto operator*(const functor<F>& a, const zero& b) {
        return zero{};
    }

    template<typename F>
    constexpr auto operator*(const zero& a, const functor<F>& b) {
        return zero{};
    }

    template<typename F>
    constexpr auto operator+(const functor<F>& a, const zero& b) {
        return a;
    }

    template<typename F>
    constexpr auto operator+(const zero& a, const functor<F>& b) {
        return b;
    }
}