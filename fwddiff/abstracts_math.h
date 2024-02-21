#pragma once

#include "abstracts.h"

namespace abstracts
{
    constexpr double exp(const zero& )
    {
        return 1.0;
    }

    constexpr double sin(const zero& )
    {
        return 0.0;
    }

    constexpr double cos(const zero& )
    {
        return 1.0;
    }
}