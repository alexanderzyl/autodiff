#pragma once

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
    template<typename F1, typename F2>
    constexpr auto operator+(const functor<F1>& a, const functor<F2>& b) {
        auto new_func = [a, b](auto... v) {
            return a(v...) + b(v...);
        };
        return functor<decltype(new_func)>(new_func);
    }

    template<typename F1, typename F2>
    constexpr auto operator*(const functor<F1>& a, const functor<F2>& b) {
        auto new_func = [a, b](auto... v) {
            return a(v...) * b(v...);
        };
        return functor<decltype(new_func)>(new_func);
    }
}