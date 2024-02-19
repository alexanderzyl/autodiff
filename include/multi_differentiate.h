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

    template<typename D, auto numargs>
    requires IsDual<D>
    struct _gradient {
        D _dual;
        static constexpr auto num_args = numargs;
        explicit _gradient(D dual) : _dual(dual) {}

    public:
        template<auto arg>
        auto function() const {
            auto args_func = [this](auto&&... args) {
                auto tuple = std::make_tuple(std::forward<decltype(args)>(args)...);
                return std::get<arg>(_dual.dx.partials)(tuple);
            };
            return args_func;
        }

        template<auto arg>
        auto partial() const {
            auto partial = std::get<arg>(_dual.dx.partials);
            return partial;
        }
    };
    template<auto numargs, typename F>
    auto differentiate(const F &func) {

        if constexpr (IsFunctor<F>)
        {
            auto builder = _gradientBuilder<decltype(func), numargs>{func};
            auto dual = builder.gradient();
            static_assert(IsDual<decltype(dual)>);
            return _gradient<decltype(dual), numargs>(dual);
        }
        else {
            auto tuple_func = [&func](auto &&tup) {
                return std::apply(func, tup);
            };
            auto grad_init = _gradientBuilder<decltype(tuple_func), numargs>{tuple_func};
            auto dual = grad_init.gradient();
            static_assert(IsDual<decltype(dual)>);
            return _gradient<decltype(dual), numargs>(dual);
        }
    }

}