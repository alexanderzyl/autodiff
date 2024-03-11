#include "ChartVisualizers.h"

#include "qtemplates.h"

#include <fwddiff/uni>

using namespace univariate;

class DifferentiateSigmoid : public ChartVisualizers {
    public:
    void differentiate_sigmoid() {
        constexpr auto sigmoid = [](auto x) {
            using namespace std;
            return 1.0 / (1.0 + univariate::exp(-x));
        };

        this->addLineSeries(qtemplates::xy_range(sigmoid, -10.0, 10.0, 0.1), "Function");

        auto derivative = differentiate(sigmoid);
        this->addLineSeries(qtemplates::xy_range(derivative, -10.0, 10.0, 0.1), "Derivative");

        this->showChart("Sigmoid");
    }
};

int main() {
    DifferentiateSigmoid differentiate_sigmoid;
    differentiate_sigmoid.differentiate_sigmoid();
    return 0;
}