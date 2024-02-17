#pragma once

#include <tuple>
#include <utility>


namespace arithmetics
{
    template<typename... T, typename... U, std::size_t... Is>
    auto tuple_plus(const std::tuple<T...>& t1, const std::tuple<U...>& t2, std::index_sequence<Is...>)
    {
        return std::make_tuple((std::get<Is>(t1) + std::get<Is>(t2))...);
    }

    template<typename... T, typename... U>
    auto operator+(const std::tuple<T...>& t1, const std::tuple<U...>& t2)
    {
        return tuple_plus(t1, t2, std::index_sequence_for<T...>{});
    }

    template<typename... T, typename... U, std::size_t... Is>
    auto tuple_minus(const std::tuple<T...>& t1, const std::tuple<U...>& t2, std::index_sequence<Is...>)
    {
        return std::make_tuple((std::get<Is>(t1) - std::get<Is>(t2))...);
    }

    template<typename... T, typename... U>
    auto operator-(const std::tuple<T...>& t1, const std::tuple<U...>& t2)
    {
        return tuple_minus(t1, t2, std::index_sequence_for<T...>{});
    }

    // Negation
    template<typename... T, std::size_t... Is>
    auto tuple_minus(const std::tuple<T...>& t1, std::index_sequence<Is...>)
    {
        return std::make_tuple(-std::get<Is>(t1)...);
    }
    template<typename... T>
    auto operator-(const std::tuple<T...>& t1)
    {
        return tuple_minus(t1, std::index_sequence_for<T...>{});
    }

    template<typename... T, typename... U, std::size_t... Is>
    auto tuple_mult(const std::tuple<T...>& t1, const std::tuple<U...>& t2, std::index_sequence<Is...>)
    {
        return std::make_tuple((std::get<Is>(t1) * std::get<Is>(t2))...);
    }

    template<typename... T, typename... U>
    auto operator*(const std::tuple<T...>& t1, const std::tuple<U...>& t2)
    {
        return tuple_mult(t1, t2, std::index_sequence_for<T...>{});
    }

    template<typename T, typename... U, std::size_t... Is>
    auto tuple_scalar_mult(const T& t1, const std::tuple<U...>& t2, std::index_sequence<Is...>)
    {
        return std::make_tuple((t1 * std::get<Is>(t2))...);
    }

    template<typename T, typename... U>
    auto operator*(const T& t1, const std::tuple<U...>& t2)
    {
        return tuple_scalar_mult(t1, t2, std::index_sequence_for<U...>{});
    }

    template<typename T, typename... U>
    auto operator*(const std::tuple<U...>& t2, const T& t1)
    {
        return tuple_scalar_mult(t1, t2, std::index_sequence_for<U...>{});
    }

    template<typename... T, typename... U, std::size_t... Is>
    auto tuple_div(const std::tuple<T...>& t1, const std::tuple<U...>& t2, std::index_sequence<Is...>)
    {
        return std::make_tuple((std::get<Is>(t1) / std::get<Is>(t2))...);
    }

    template<typename... T, typename... U>
    auto operator/(const std::tuple<T...>& t1, const std::tuple<U...>& t2)
    {
        return tuple_div(t1, t2, std::index_sequence_for<T...>{});
    }
}