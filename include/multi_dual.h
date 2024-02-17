#pragma once
#include "tuple_arithmetics.h"
#include "functor.h"
#include "epsilon.h"

namespace multivariate {

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

    template<typename ...F1, typename ...F2>
    constexpr auto operator*(const _partials<F1...>& a, const _partials<F2...>& b) {
        auto new_partials = a.partials * b.partials;
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
        auto new_partials = b * a;
        static_assert(IsPartials<decltype(new_partials)>);
        return new_partials;
    }

    template<typename FX, typename ...DXs>
    struct dual {

        functor<FX> x;
        _partials<DXs...> dx;

        constexpr dual(FX x, _partials<DXs...> dx) : x(x), dx(dx) {}

        constexpr dual(functor<FX>&& x, _partials<DXs...>&& dx) : x(std::move(x)), dx(std::move(dx)) {}

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