#pragma once

#include <concepts>

namespace abstracts {
    struct identity{
    };

    struct zero {
    };

    // Multiplications
    template<typename V>
    constexpr auto operator*(V a, identity b) {
        return a;
    }
    template<typename V>
    constexpr auto operator*(identity a, V b) {
        return b;
    }
    template<typename V>
    constexpr auto operator*(V a, zero b) {
        return zero{};
    }
    template<typename V>
    constexpr auto operator*(zero a, V b) {
        return zero{};
    }

    // Additions
    template<typename V>
    constexpr auto operator+(V a, zero b) {
        return a;
    }
    template<typename V>
    constexpr auto operator+(zero a, V b) {
        return b;
    }

    // Subtractions
    template<typename V>
    constexpr auto operator-(V a, zero b) {
        return a;
    }
    template<typename V>
    constexpr auto operator-(zero a, V b) {
        return -b;
    }

    // Negations
    constexpr auto operator-(zero b) {
        return zero{};
    }
    constexpr auto operator-(identity b) {
        return -1;
    }

    template<typename TAbstract>
    concept IsAbstractsType = std::is_same_v<TAbstract, identity> || std::is_same_v<TAbstract, zero>;
}