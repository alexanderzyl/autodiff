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
}