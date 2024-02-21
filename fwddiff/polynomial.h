#pragma once

#include <cmath>
#include <tuple>
#include <utility>

namespace polynomials
{
    template<typename T, unsigned int exp>
    struct Pow
    {
        static constexpr auto compute(const T& base)
        {
            return base * Pow<T, exp - 1>::compute(base);
        }
    };

    template<typename T>
    struct Pow<T, 0>
    {
        static constexpr T compute(const T&)
        {
            return T{1};
        }
    };

    template<typename... Ts>
    struct Polynomial
    {
        std::tuple<Ts...> coefficients;
        [[maybe_unused]] static constexpr size_t degree = sizeof...(Ts) - 1;

        constexpr Polynomial(Ts... coeffs) : coefficients(std::make_tuple(coeffs...)) {}

        template<class V, std::size_t... Is>
        constexpr auto evaluate(V x, std::index_sequence<Is...>) const
        {
            return ((std::get<Is>(coefficients) * Pow<decltype(x), Is>::compute(x)) + ...);
        }

        template<class V>
        constexpr auto operator()(V x) const
        {
            return evaluate(x, std::index_sequence_for<Ts...>{});
        }
    };
} // namespace polynomials