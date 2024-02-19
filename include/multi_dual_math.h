#pragma once

#include "multi_dual.h"

namespace multivariate
{
    template <typename FX, typename ...DXs>
    constexpr auto exp(const dual<FX, DXs...>& x) {
        auto dx = exp(x.x) * x.dx;
        static_assert(IsPartials<decltype(dx)>);
        return dual{exp(x.x), dx};
    }

    template <typename FX, typename ...DXs>
    constexpr auto sin(const dual<FX, DXs...>& x) {
        auto dx = cos(x.x) * x.dx;
        static_assert(IsPartials<decltype(dx)>);
        return dual{sin(x.x), dx};
    }

    template <typename FX, typename ...DXs>
    constexpr auto cos(const dual<FX, DXs...>& x) {
        auto dx = -sin(x.x) * x.dx;
        static_assert(IsPartials<decltype(dx)>);
        return dual{cos(x.x), dx};
    }
}