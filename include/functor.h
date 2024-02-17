#pragma once
#include <type_traits>

namespace multivariate
{
    template<typename F>
    struct functor {
        F func;

        explicit functor(F f) : func(f) {}

        template<typename ...V>
        constexpr auto operator()(V... v) const {
            return func(v...);
        }

        static constexpr bool is_functor = true;
    };

    template <typename T>
    concept IsFunctor = T::is_functor;

    // arithmetics for _functor

    // Additions
    template<typename F1, typename F2>
    constexpr auto operator+(const functor<F1>& a, const functor<F2>& b) {
        auto new_func = [a, b](auto... v) {
            return a(v...) + b(v...);
        };
        return functor<decltype(new_func)>(new_func);
    }

    template<typename T, typename F>
    requires std::is_arithmetic_v<T>
    constexpr auto operator+(T a, const functor<F>& b) {
        auto new_func = [a, b](auto... v) {
            return a + b(v...);
        };
        return functor<decltype(new_func)>(new_func);
    }

    template<typename T, typename F>
    requires std::is_arithmetic_v<T>
    constexpr auto operator+(const functor<F>& a, T b) {
        auto new_func = [a, b](auto... v) {
            return a(v...) + b;
        };
        return functor<decltype(new_func)>(new_func);
    }

    // Subtractions
    template<typename F1, typename F2>
    constexpr auto operator-(const functor<F1>& a, const functor<F2>& b) {
        auto new_func = [a, b](auto... v) {
            return a(v...) - b(v...);
        };
        return functor<decltype(new_func)>(new_func);
    }

    template<typename T, typename F>
    requires std::is_arithmetic_v<T>
    constexpr auto operator-(T a, const functor<F>& b) {
        auto new_func = [a, b](auto... v) {
            return a - b(v...);
        };
        return functor<decltype(new_func)>(new_func);
    }

    template<typename T, typename F>
    requires std::is_arithmetic_v<T>
    constexpr auto operator-(const functor<F>& a, T b) {
        auto new_func = [a, b](auto... v) {
            return a(v...) - b;
        };
        return functor<decltype(new_func)>(new_func);
    }

    // Multiplications
    template<typename F1, typename F2>
    constexpr auto operator*(const functor<F1>& a, const functor<F2>& b) {
        auto new_func = [a, b](auto... v) {
            return a(v...) * b(v...);
        };
        return functor<decltype(new_func)>(new_func);
    }

    template<typename T, typename F>
    requires std::is_arithmetic_v<T>
    constexpr auto operator*(T a, const functor<F>& b) {
        auto new_func = [a, b](auto... v) {
            return a * b(v...);
        };
        return functor<decltype(new_func)>(new_func);
    }

    template<typename T, typename F>
    requires std::is_arithmetic_v<T>
    constexpr auto operator*(const functor<F>& a, T b) {
        auto new_func = [a, b](auto... v) {
            return a(v...) * b;
        };
        return functor<decltype(new_func)>(new_func);
    }
}