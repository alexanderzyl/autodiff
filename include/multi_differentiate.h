#pragma once
#include "multi_dual.h"

namespace multivariate
{

    template<typename F, auto numargs>
    struct _gradientBuilder {
        F func;

        template<auto C, auto I>
        auto build_dx() {
            if constexpr (C == I) {
                return epsilon{};
            }
            else {
                return zero{};
            }
        }

        template<auto I, auto ... Cs>
        auto build_dual(std::index_sequence<Cs...>) {
            auto dxs = multivariate::_partials(build_dx<Cs, I>()...);
            auto indicator = [](auto v_tuple) {
                return std::get<I>(v_tuple);
            };
            auto dual = multivariate::dual{indicator, dxs};
            return dual;
        }

        template<auto... Is>
        auto build_partial(std::index_sequence<Is...>) {
            auto arg = std::tuple(build_dual<Is>(std::make_index_sequence<numargs>())...);
            auto result_dual = func(arg);
            return result_dual;
        }

        auto gradient() {
            return build_partial(std::make_index_sequence<numargs>());
        }


        _gradientBuilder(F func) : func(func) {}
    };

    template<typename F, int numargs>
    static constexpr auto _init_dual(F func) {
        auto tuple_func = [&func](auto&& tup) {
            return std::apply(func, tup);
        };
        auto grad_init = _gradientBuilder<decltype(tuple_func), numargs>{tuple_func};
        return grad_init.gradient();
    }

    template<typename F, auto numargs>
    struct _gradient {
        decltype(_init_dual<F, numargs>(std::declval<F>()))_dual;

        explicit _gradient(F func) : _dual(_init_dual<F, numargs>(func)) {
        }

    public:

        template<auto arg>
        auto partial() const {
            return std::get<arg>(_dual.dx.partials);
        }
    };
    template<typename F, int numargs>
    auto differentiate(const F &func) {

        return _gradient<F, numargs>(func);
    }
}