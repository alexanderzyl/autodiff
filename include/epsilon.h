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

        constexpr zero operator-() const {
            return zero{};
        }
    };

    constexpr auto operator+(const zero& a, const zero& b) {
        return zero{};
    }

    constexpr auto operator-(const zero& a, const zero& b) {
        return zero{};
    }

    constexpr auto operator+(const epsilon& a, const zero& b) {
        return epsilon{};
    }

    constexpr auto operator+(const zero& a, const epsilon& b) {
        return epsilon{};
    }

    constexpr auto operator-(const epsilon& a, const zero& b) {
        return epsilon{};
    }

    constexpr auto operator-(const zero& a, const epsilon& b) {
        return epsilon{};
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    constexpr auto operator*(T a, const epsilon& b) {
        return functor([a](auto... v) {
            return a;
        });
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    constexpr auto operator*(const epsilon& a, T b) {
        return functor([b](auto... v) {
            return b;
        });
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    constexpr auto operator*(T a, const zero& b) {
        return zero{};
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

    template<typename F>
    constexpr auto operator-(const functor<F>& a, const zero& b) {
        return a;
    }

    template<typename F>
    constexpr auto operator-(const zero& a, const functor<F>& b) {
        return functor([b](auto... v) {
            return -b(v...);
        });
    }
}