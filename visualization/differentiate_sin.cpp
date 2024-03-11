#include "ChartVisualizers.h"

#include "qtemplates.h"

#include <fwddiff/uni>

using namespace univariate;

class DifferentiateSin : public ChartVisualizers {
public:
    void differentiate_sin() {
        constexpr auto generic_sin = [](auto x) {
            return univariate::sin(x);
        };

        this->addLineSeries(qtemplates::xy_range(generic_sin, -6., 6.0, 0.1), "Function");

        auto derivative = differentiate(generic_sin);
        this->addLineSeries(qtemplates::xy_range(derivative, -6.0, 6.0, 0.1), "Derivative");

        this->showChart("Sine");
    }
};

int main() {
    DifferentiateSin differentiate_sin;
    differentiate_sin.differentiate_sin();
    return 0;
}