#include "ChartVisualizers.h"

#include "taylor.h"
#include "abstracts_math.h"
#include "uni_math.h"
#include "qtemplates.h"

class TaylorVisualizations: public ChartVisualizers{
};

TEST_F(TaylorVisualizations, taylor_exp) {
    constexpr auto taylor_exp = [](auto x) {
        return exp(x);
    };

    this->addLineSeries(qtemplates::xy_range([taylor_exp](double x){
        return algorithms::taylor<10>(taylor_exp, x, abstracts::zero{});
        }, 0., 6.0, 0.1), "Estimated by Taylor");

    this->addLineSeries(qtemplates::xy_range([](double x){
        return exp(x);
        }, 0., 6.0, 0.1), "std:: Computed");

    this->showChart("Taylor Series vs std::exp");
}

TEST_F(TaylorVisualizations, taylor_sin) {
    constexpr auto taylor_sin = [](auto x) {
        return sin(x);
    };

    this->addLineSeries(qtemplates::xy_range([](double x){
        return std::sin(x);
        }, -3.14, 3.14, 0.1), "std:: Computed");

    auto *std_plot = new QLineSeries();
    std_plot->replace(qtemplates::xy_range([](double x){
        return std::sin(x);
        }, -3.14, 3.14, 0.1));

    this->addLineSeries(qtemplates::xy_range([taylor_sin](double x){
        return algorithms::taylor<10>(taylor_sin, x, abstracts::zero{});
        }, -3.14, 3.14, 0.1), "Estimated by Taylor");

    this->showChart("Taylor Series vs std::sin");
}

TEST_F(TaylorVisualizations, taylor_cos) {
    constexpr auto taylor_cos = [](auto x) {
        return cos(x);
    };

    this->addLineSeries(qtemplates::xy_range([taylor_cos](double x) {
        return algorithms::taylor<10>(taylor_cos, x, abstracts::zero{});
    }, -3.14, 3.14, 0.1), "Estimated by Taylor");

    this->addLineSeries(qtemplates::xy_range([](double x){
        return std::cos(x);
        }, -3.14, 3.14, 0.1), "std:: Computed");

    this->showChart("Taylor Series vs std::cos");

}