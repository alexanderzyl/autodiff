#pragma once
#include <delta.h>

#include <type_traits>

template<typename F, typename T>
auto differentiate(F func, T value) {
    delta<T> dx (value, 1.0);

    delta<T> result = func(dx);
    return result.dx;
}