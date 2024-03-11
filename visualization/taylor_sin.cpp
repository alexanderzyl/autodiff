#include "ChartVisualizers.h"

#include <fwddiff/uni>
#include <fwddiff/taylor.h>

#include "qtemplates.h"

class TaylorVisualizations : public ChartVisualizers {
public:
    void taylor_sin() {
        constexpr auto taylor_sin = [](auto x) {
            return sin(x);
        };

        this->addLineSeries(qtemplates::xy_range([](double x) {
            return std::sin(x);
        }, -3.14, 3.14, 0.1), "std::sin");

        auto *std_plot = new QLineSeries();
        std_plot->replace(qtemplates::xy_range([](double x) {
            return std::sin(x);
        }, -3.14, 3.14, 0.1));

        this->addLineSeries(qtemplates::xy_range([taylor_sin](double x) {
            return algorithms::taylor<10>(taylor_sin, x, abstracts::zero{});
        }, -3.14, 3.14, 0.1), "taylor sin");

        this->showChart("Taylor Series vs std::sin");
    }
};

int main() {
    TaylorVisualizations taylor_visualizations;
    taylor_visualizations.taylor_sin();
    return 0;
}