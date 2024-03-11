#include "ChartVisualizers.h"

#include "qtemplates.h"

#include <fwddiff/uni>

using namespace univariate;

class DifferentiateCos : public ChartVisualizers {
public:
    void differentiate_cos() {
        constexpr auto generic_cos = [](auto x) {
            return univariate::cos(x);
        };

        this->addLineSeries(qtemplates::xy_range(generic_cos, -6., 6.0, 0.1), "Function");

        auto derivative = differentiate(generic_cos);
        this->addLineSeries(qtemplates::xy_range(derivative, -6.0, 6.0, 0.1), "Derivative");

        this->showChart("Cosine");
    }
};

int main() {
    DifferentiateCos differentiate_cos;
    differentiate_cos.differentiate_cos();
    return 0;
}