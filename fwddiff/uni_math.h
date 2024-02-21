#pragma once
#include "uni_dual.h"
#include <cmath>

namespace univariate
{
    inline double exp(const double & a)
    {
        return std::exp(a);
    }

    template <typename FX, typename FDX>
    constexpr auto exp(dual<FX, FDX> a)
    {
        return dual{[a](auto value) {
            return exp(a.x(value));
        }, [a](auto value){
            return exp(a.x(value)) * a.dx(value);
        }};
    }

    inline double sin(const double & a)
    {
        return std::sin(a);
    }

    inline double cos(const double & a)
    {
        return std::cos(a);
    }

    template <typename FX, typename FDX>
    constexpr auto sin(dual<FX, FDX> a)
    {
        return dual{[a](auto value) {
            return sin(a.x(value));
        }, [a](auto value){
            return cos(a.x(value)) * a.dx(value);
        }};
    }

    template <typename FX, typename FDX>
    constexpr auto cos(dual<FX, FDX> a)
    {
        return dual{[a](auto value) {
            return cos(a.x(value));
        }, [a](auto value){
            return -sin(a.x(value)) * a.dx(value);
        }};
    }
}