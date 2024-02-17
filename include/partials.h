#pragma once
#include "functor.h"
#include "tuple_arithmetics.h"

namespace multivariate
{
    using namespace arithmetics;
    using arithmetics::operator*;
    using arithmetics::operator+;
    using arithmetics::operator-;

    template<IsFunctor ...F>
    struct _partials {
        std::tuple<F...> partials;

        _partials(F... f) : partials(f...) {}

        explicit _partials(const std::tuple<F...>& tuple) : partials(tuple) {}

        template<typename V, auto pos>
        constexpr auto dx(V v_tuple) const {
            return std::get<pos>(partials)(v_tuple);
        }

        static constexpr bool is_partials = true;
    };

    template <typename T>
    concept IsPartials = T::is_partials;

    // arithmetics for _partials
    template<typename ...F1, typename ...F2>
    constexpr auto operator+(const _partials<F1...>& a, const _partials<F2...>& b) {
        auto new_partials = _partials(a.partials + b.partials);
        static_assert(IsPartials<decltype(new_partials)>);
        return new_partials;
    }

    template<typename T, typename ...F>
    requires std::is_arithmetic_v<T>
    constexpr auto operator+(T a, const _partials<F...>& b) {
        auto new_partials = _partials(a + b.partials);
        static_assert(IsPartials<decltype(new_partials)>);
        return new_partials;
    }

    template<typename T, typename ...F>
    requires std::is_arithmetic_v<T>
    constexpr auto operator+(const _partials<F...>& a, T b) {
        auto new_partials = _partials(a.partials + b);
        static_assert(IsPartials<decltype(new_partials)>);
        return new_partials;
    }

    template<typename ...F1, typename ...F2>
    constexpr auto operator-(const _partials<F1...>& a, const _partials<F2...>& b) {
        auto new_partials = _partials(a.partials - b.partials);
        static_assert(IsPartials<decltype(new_partials)>);
        return new_partials;
    }

    template<typename T, typename ...F>
    requires std::is_arithmetic_v<T>
    constexpr auto operator-(T a, const _partials<F...>& b) {
        auto new_partials = _partials(a - b.partials);
        static_assert(IsPartials<decltype(new_partials)>);
        return new_partials;
    }

    template<typename T, typename ...F>
    requires std::is_arithmetic_v<T>
    constexpr auto operator-(const _partials<F...>& a, T b) {
        auto new_partials = _partials(a.partials - b);
        static_assert(IsPartials<decltype(new_partials)>);
        return new_partials;
    }

    template<typename ...F1, typename ...F2>
    constexpr auto operator*(const _partials<F1...>& a, const _partials<F2...>& b) {
        auto new_partials = _partials(a.partials * b.partials);
        static_assert(IsPartials<decltype(new_partials)>);
        return new_partials;
    }

    template<typename T, typename ...F>
    requires std::is_arithmetic_v<T>
    constexpr auto operator*(T a, const _partials<F...>& b) {
        auto new_partials = _partials(a * b.partials);
        static_assert(IsPartials<decltype(new_partials)>);
        return new_partials;
    }

    template<typename T, typename ...F>
    requires std::is_arithmetic_v<T>
    constexpr auto operator*(const _partials<F...>& a, T b) {
        auto new_partials = _partials(a.partials * b);
        static_assert(IsPartials<decltype(new_partials)>);
        return new_partials;
    }

    // arithmetics for _partials and _functor
    template<typename F1, typename ...F2>
    constexpr auto operator*(const functor<F1>& a, const _partials<F2...>& b) {
        auto new_partials = _partials(a * b.partials);
        static_assert(IsPartials<decltype(new_partials)>);
        return new_partials;
    }

    template<typename F1, typename ...F2>
    constexpr auto operator*(const _partials<F2...>& a, const functor<F1>& b) {
        auto new_partials = _partials(a.partials * b);
        static_assert(IsPartials<decltype(new_partials)>);
        return new_partials;
    }

    template<typename F1, typename ...F2>
    constexpr auto operator+(const functor<F1>& a, const _partials<F2...>& b) {
        auto new_partials = _partials(a + b.partials);
        static_assert(IsPartials<decltype(new_partials)>);
        return new_partials;
    }

    template<typename F1, typename ...F2>
    constexpr auto operator+(const _partials<F2...>& a, const functor<F1>& b) {
        auto new_partials = _partials(a.partials + b);
        static_assert(IsPartials<decltype(new_partials)>);
        return new_partials;
    }

    template<typename F1, typename ...F2>
    constexpr auto operator-(const functor<F1>& a, const _partials<F2...>& b) {
        auto new_partials = _partials(a - b.partials);
        static_assert(IsPartials<decltype(new_partials)>);
        return new_partials;
    }

    template<typename F1, typename ...F2>
    constexpr auto operator-(const _partials<F2...>& a, const functor<F1>& b) {
        auto new_partials = _partials(a.partials - b);
        static_assert(IsPartials<decltype(new_partials)>);
        return new_partials;
    }
}