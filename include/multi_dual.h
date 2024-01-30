#pragma once
#include "tuple_arithmetics.h"

namespace multivariate {

    using namespace arithmetics;
    using arithmetics::operator*;
    using arithmetics::operator+;
    using arithmetics::operator-;

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

    template<typename F>
    struct _functor {
        F func;

        explicit _functor(F f) : func(f) {}

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
    constexpr auto operator+(const _functor<F1>& a, const _functor<F2>& b) {
        auto new_func = [a, b](auto... v) {
            return a(v...) + b(v...);
        };
        return _functor<decltype(new_func)>(new_func);
    }

    template<typename F1, typename F2>
    constexpr auto operator*(const _functor<F1>& a, const _functor<F2>& b) {
        auto new_func = [a, b](auto... v) {
            return a(v...) * b(v...);
        };
        return _functor<decltype(new_func)>(new_func);
    }

    // arithmetics for _functor and _epsilon
    template<typename F>
    constexpr auto operator*(const _functor<F>& a, const epsilon& b) {
        return a;
    }

    template<typename F>
    constexpr auto operator*(const epsilon& a, const _functor<F>& b) {
        return b;
    }

    // arithmetics for _functor and _zero
    template<typename F>
    constexpr auto operator*(const _functor<F>& a, const zero& b) {
        return zero{};
    }

    template<typename F>
    constexpr auto operator*(const zero& a, const _functor<F>& b) {
        return zero{};
    }

    template<typename F>
    constexpr auto operator+(const _functor<F>& a, const zero& b) {
        return a;
    }

    template<typename F>
    constexpr auto operator+(const zero& a, const _functor<F>& b) {
        return b;
    }

    constexpr auto operator+(const zero& a, const zero& b) {
        return zero{};
    }

    constexpr auto operator+(const epsilon& a, const zero& b) {
        return epsilon{};
    }

    constexpr auto operator+(const zero& a, const epsilon& b) {
        return epsilon{};
    }

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

    template<typename ...F1, typename ...F2>
    constexpr auto operator*(const _partials<F1...>& a, const _partials<F2...>& b) {
        auto new_partials = a.partials * b.partials;
        static_assert(IsPartials<decltype(new_partials)>);
        return new_partials;
    }

    // arithmetics for _partials and _functor
    template<typename F1, typename ...F2>
    constexpr auto operator*(const _functor<F1>& a, const _partials<F2...>& b) {
        auto new_partials = _partials(a * b.partials);
        static_assert(IsPartials<decltype(new_partials)>);
        return new_partials;
    }

    template<typename F1, typename ...F2>
    constexpr auto operator*(const _partials<F2...>& a, const _functor<F1>& b) {
        auto new_partials = b * a;
        static_assert(IsPartials<decltype(new_partials)>);
        return new_partials;
    }

    template<typename FX, typename ...DXs>
    struct dual {

        _functor<FX> x;
        _partials<DXs...> dx;

        constexpr dual(FX x, _partials<DXs...> dx) : x(x), dx(dx) {}

        constexpr dual(_functor<FX>&& x, _partials<DXs...>&& dx) : x(std::move(x)), dx(std::move(dx)) {}

        static constexpr bool is_dual = true;
    };

    template <typename T>
    concept IsDual = T::is_dual;

    // Multiplications
    template<typename FX1, typename ...DXs1, typename FX2, typename ...DXs2>
    constexpr auto operator*(dual<FX1, DXs1...> a, dual<FX2, DXs2...> b) {
        auto dx1 =a.dx * b.x;
        static_assert(IsPartials<decltype(dx1)>);
        auto dx2 = a.x * b.dx;
        static_assert(IsPartials<decltype(dx2)>);
        auto p = dx1 + dx2;
        static_assert(IsPartials<decltype(p)>);
        return dual{a.x * b.x, p};
    }

    // Additions
    template<typename FX1, typename ...DXs1, typename FX2, typename ...DXs2>
    constexpr auto operator+(dual<FX1, DXs1...> a, dual<FX2, DXs2...> b) {
        return dual{a.x + b.x, a.dx + b.dx};
    }
}