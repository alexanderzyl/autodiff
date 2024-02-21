#pragma once
#include "uni_dual.h"
#include "abstracts.h"

#include <tuple>

namespace univariate {

    template<typename F>
    static constexpr auto _init_dual(F func) {
        if constexpr (univariate::IsDual<decltype(func)>) {
            return func;
        } else {

            auto partial = univariate::dual{[](auto v) { return v; }, [](auto) { return abstracts::identity{}; }};
            auto df = func(partial);
            if constexpr (univariate::IsDual<decltype(df)>) {
                return df;
            } else {
                return univariate::dual{[df](auto) { return df; }, [](auto) { return abstracts::zero{}; }};
            }
        }
    }


    template<typename F>
    struct _Differential {
    private:
        decltype(_init_dual(std::declval<F>())) df;

        constexpr explicit _Differential(F func) : df(_init_dual(func)) {
        }

        template<typename F1>
        constexpr friend auto differentiate(const F1 &func);

        template<typename F1> friend
        struct _Differential;

        constexpr auto differentiate() const {
            auto lambda = [this](auto v) {
                return df.dx(v);
            };
            return _Differential<decltype(lambda)>(lambda);
        }

    public:
        static constexpr bool is_differential = true;

        template<typename V>
        constexpr auto operator()(V value) const {
            if constexpr (std::same_as<decltype(df.dx(value)), abstracts::zero>) {
                return V{0.0};
            } else if constexpr (std::same_as<decltype(df.dx(value)), abstracts::identity>) {
                return V{1.0};
            } else {
                return df.dx(value);
            }
        }
    };

    template<typename T>
    concept IsDifferential = T::is_differential;

    template<typename F>
    constexpr auto differentiate(const F &func) {
        if constexpr (IsDifferential<F>) {
            return func.differentiate();
        } else {
            return _Differential<F>(func);
        }
    }

    template<typename F, typename T>
    constexpr auto differentiate_at(F func, T value) {
        auto df = _init_dual(func);
        return df.dx(value);
    }
}