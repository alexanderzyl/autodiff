#include "ChartVisualizers.h"

#include <fwddiff/uni>
#include <fwddiff/taylor.h>

#include "qtemplates.h"

class TaylorExp : public ChartVisualizers {
public:
    void taylor_exp() {
        constexpr auto taylor_exp = [](auto x) {
            return exp(x);
        };

        this->addLineSeries(qtemplates::xy_range([taylor_exp](double x) {
            return algorithms::taylor<10>(taylor_exp, x, abstracts::zero{});
        }, 0., 6.0, 0.1), "taylor exp");

        this->addLineSeries(qtemplates::xy_range([](double x) {
            return exp(x);
        }, 0., 6.0, 0.1), "std::exp");

        this->showChart("Taylor Series vs std::exp");
    }
};

int main() {
    TaylorExp taylor_exp;
    taylor_exp.taylor_exp();
    return 0;
}