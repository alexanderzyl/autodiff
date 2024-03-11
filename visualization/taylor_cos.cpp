#include "ChartVisualizers.h"

#include <fwddiff/uni>
#include <fwddiff/taylor.h>

#include "qtemplates.h"

class TaylorVisualizations : public ChartVisualizers {
public:
    void taylor_cos() {
        constexpr auto taylor_cos = [](auto x) {
            return cos(x);
        };

        this->addLineSeries(qtemplates::xy_range([taylor_cos](double x) {
            return algorithms::taylor<10>(taylor_cos, x, abstracts::zero{});
        }, -3.14, 3.14, 0.1), "taylor cos");

        this->addLineSeries(qtemplates::xy_range([](double x) {
            return std::cos(x);
        }, -3.14, 3.14, 0.1), "std::cos");

        this->showChart("Taylor Series vs std::cos");
    }
};

int main() {
    TaylorVisualizations taylor_visualizations;
    taylor_visualizations.taylor_cos();
    return 0;
}