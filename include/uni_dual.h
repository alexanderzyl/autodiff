#pragma once
#include "abstracts.h"
#include <functional>

namespace univariate
{
    template <typename FX, typename FDX>
    struct dual
    {
        FX f_x;
        FDX f_dx;

        constexpr dual(FX x, FDX dx) : f_x(x), f_dx(dx) {}

        template <typename V>
        constexpr auto x(V value) const
        {
            return f_x(value);
        }

        template <typename V>
        constexpr auto dx(V value) const
        {
            return f_dx(value);
        }

        static constexpr bool is_dual = true;
    };

    template <typename T>
    concept IsDual = T::is_dual;

    // Multiplications
    template <typename FX1, typename FDX1, typename FX2, typename FDX2>
    constexpr auto operator*(dual<FX1, FDX1> a, dual<FX2, FDX2> b)
    {
        auto x = [a, b](auto value) {
            return a.x(value) * b.x(value);
        };
        auto dx = [a, b](auto value){
            return a.x(value) * b.dx(value) + a.dx(value) * b.x(value);
        };
        return dual{x, dx};
    }

    template <typename V, typename FX, typename FDX>
    constexpr auto operator*(V a, dual<FX, FDX> b)
    {
        auto x = [a, b](auto value) {
            return a * b.x(value);
        };
        auto dx = [a, b](auto value){
            return a * b.dx(value);
        };
        return dual{x, dx};
    }

    template <typename V, typename FX, typename FDX>
    constexpr auto operator*(dual<FX, FDX> a, V b)
    {
        return b * a;
    }

    template <typename FX, typename FDX>
    constexpr auto operator*(dual<FX, FDX> a, abstracts::identity)
    {
        return a;
    }

    template <typename FX, typename FDX>
    constexpr auto operator*(abstracts::identity, dual<FX, FDX> b)
    {
        return b;
    }

    template <typename FX, typename FDX>
    constexpr auto operator*(dual<FX, FDX> a, abstracts::zero)
    {
        return dual{[a](auto value) { return 0; }, [a](auto value) { return 0; }};
    }

    template <typename FX, typename FDX>
    constexpr auto operator*(abstracts::zero, dual<FX, FDX> b)
    {
        return b * abstracts::zero{};
    }

    // Division
    template <typename FX1, typename FDX1, typename FX2, typename FDX2>
    constexpr auto operator/(dual<FX1, FDX1> a, dual<FX2, FDX2> b)
    {
        auto x = [a, b](auto value) {
            return a.x(value) / b.x(value);
        };
        auto dx = [a, b](auto value){
            return (a.dx(value) * b.x(value) - a.x(value) * b.dx(value)) / (b.x(value) * b.x(value));
        };
        return dual{x, dx};
    }

    template <typename V, typename FX, typename FDX>
    constexpr auto operator/(V a, dual<FX, FDX> b)
    {
        auto x = [a, b](auto value) {
            return a / b.x(value);
        };
        auto dx = [a, b](auto value){
            return -a * b.dx(value) / (b.x(value) * b.x(value));
        };
        return dual{x, dx};
    }

    template <typename V, typename FX, typename FDX>
    constexpr auto operator/(dual<FX, FDX> a, V b)
    {
        auto x = [a, b](auto value) {
            return a.x(value) / b;
        };
        auto dx = [a, b](auto value){
            return a.dx(value) / b;
        };
        return dual{x, dx};
    }

    // Additions
    template <typename FX1, typename FDX1, typename FX2, typename FDX2>
    constexpr auto operator+(dual<FX1, FDX1> a, dual<FX2, FDX2> b)
    {
        auto x = [a, b](auto value) {
            return a.x(value) + b.x(value);
        };
        auto dx = [a, b](auto value){
            return a.dx(value) + b.dx(value);
        };
        return dual{x, dx};
    }

    template <typename V, typename FX, typename FDX>
    constexpr auto operator+(V a, dual<FX, FDX> b)
    {
        auto x = [a, b](auto value) {
            return a + b.x(value);
        };
        auto dx = [a, b](auto value){
            return b.dx(value);
        };
        return dual{x, dx};
    }

    template <typename V, typename FX, typename FDX>
    constexpr auto operator+(dual<FX, FDX> a, V b)
    {
        return b + a;
    }

    // negation
    template <typename FX, typename FDX>
    constexpr auto operator-(dual<FX, FDX> a)
    {
        return dual{[a](auto value) { return -a.x(value); }, [a](auto value) { return -a.dx(value); }};
    }
    // Subtractions
    template <typename FX1, typename FDX1, typename FX2, typename FDX2>
    constexpr auto operator-(dual<FX1, FDX1> a, dual<FX2, FDX2> b)
    {
        return dual{[a,b](auto value) { return a.x(value) - b.x(value); },
                    [a,b](auto value) { return a.dx(value) - b.dx(value); }};
    }

    template <typename V, typename FX, typename FDX>
    constexpr auto operator-(V a, dual<FX, FDX> b)
    {
        return dual{[a, b](auto value) { return a - b.x(value); },
                    [a, b](auto value) { return -b.dx(value); }};
    }

    template <typename V, typename FX, typename FDX>
    constexpr auto operator-(dual<FX, FDX> a, V b)
    {
        return dual{[a,b](auto value) { return a.x(value) - b; },
                    [a,b](auto value) { return a.dx(value); }};
    }
}