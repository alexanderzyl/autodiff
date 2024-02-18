#pragma once
#include "partials.h"
#include "functor.h"
#include "epsilon.h"

#include "tuple_arithmetics.h"
#include "pow.h"

namespace multivariate {

    using namespace arithmetics;
    using arithmetics::operator*;
    using arithmetics::operator+;
    using arithmetics::operator-;
    using arithmetics::pow;

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

    template<typename T, typename FX, typename ...DXs>
    requires std::is_arithmetic_v<T>
    constexpr auto operator*(T a, dual<FX, DXs...> b) {
        auto dx = a * b.dx;
        static_assert(IsPartials<decltype(dx)>);
        return dual{a * b.x, dx};
    }

    template<typename T, typename FX, typename ...DXs>
    requires std::is_arithmetic_v<T>
    constexpr auto operator*(dual<FX, DXs...> a, T b) {
        auto dx = a.dx * b;
        static_assert(IsPartials<decltype(dx)>);
        return dual{a.x * b, dx};
    }

    // Additions
    template<typename FX1, typename ...DXs1, typename FX2, typename ...DXs2>
    constexpr auto operator+(dual<FX1, DXs1...> a, dual<FX2, DXs2...> b) {
        return dual{a.x + b.x, a.dx + b.dx};
    }

    template<typename T, typename FX, typename ...DXs>
    requires std::is_arithmetic_v<T>
    constexpr auto operator+(T a, dual<FX, DXs...> b) {
        return dual{a + b.x, b.dx};
    }

    template<typename T, typename FX, typename ...DXs>
    requires std::is_arithmetic_v<T>
    constexpr auto operator+(dual<FX, DXs...> a, T b) {
        return dual{a.x + b, a.dx};
    }

    // Subtractions
    template<typename FX1, typename ...DXs1, typename FX2, typename ...DXs2>
    constexpr auto operator-(dual<FX1, DXs1...> a, dual<FX2, DXs2...> b) {
        return dual{a.x - b.x, a.dx - b.dx};
    }

    template<typename T, typename FX, typename ...DXs>
    requires std::is_arithmetic_v<T>
    constexpr auto operator-(T a, dual<FX, DXs...> b) {
        return dual{a - b.x, b.dx};
    }

    template<typename T, typename FX, typename ...DXs>
    requires std::is_arithmetic_v<T>
    constexpr auto operator-(dual<FX, DXs...> a, T b) {
        return dual{a.x - b, a.dx};
    }

    // Negations
    template<typename FX, typename ...DXs>
    constexpr auto operator-(dual<FX, DXs...> a) {
        return dual{-a.x, -a.dx};
    }
}

namespace arithmetics
{
    using namespace multivariate;
    // Powers
    template<int N, typename FX, typename ...DXs>
    constexpr auto pow(dual<FX, DXs...> a) {
        auto dx = N * pow<N - 1>(a.x) * a.dx;
        static_assert(IsPartials<decltype(dx)>);
        return dual{pow<N>(a.x), dx};
    }

}

namespace multivariate
{
    // Divisions

    template<typename FX1, typename ...DXs1, typename FX2, typename ...DXs2>
    constexpr auto operator/(dual<FX1, DXs1...> a, dual<FX2, DXs2...> b) {
        return a * arithmetics::pow<-1>(b);
    }

}