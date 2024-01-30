#include "ChartVisualizers.h"

#include "qtemplates.h"

#include "uni_differentiate.h"
#include "uni_math.h"

class DifferentialVisualizations: public ChartVisualizers{
protected:
};

TEST_F(DifferentialVisualizations, differentiate_sigmoid) {
    constexpr auto sigmoid = [](auto x) {
        using namespace std;
        return 1.0 / (1.0 + exp(-x));
    };

    this->addLineSeries(qtemplates::xy_range(sigmoid, -10.0, 10.0, 0.1), "Function");

    auto derivative = differentiate(sigmoid);
    this->addLineSeries(qtemplates::xy_range(derivative, -10.0, 10.0, 0.1), "Derivative");

    this->showChart("Sigmoid");
}

TEST_F(DifferentialVisualizations, differentiate_sin) {
    constexpr auto generic_sin = [](auto x) {
        return sin(x);
    };

    this->addLineSeries(qtemplates::xy_range(generic_sin, -6., 6.0, 0.1), "Function");

    auto derivative = differentiate(generic_sin);
    this->addLineSeries(qtemplates::xy_range(derivative, -6.0, 6.0, 0.1), "Derivative");

    this->showChart("Sine");
}

TEST_F(DifferentialVisualizations, differentiate_cos) {
    constexpr auto generic_cos = [](auto x) {
        return cos(x);
    };

    this->addLineSeries(qtemplates::xy_range(generic_cos, -6., 6.0, 0.1), "Function");

    auto derivative = differentiate(generic_cos);
    this->addLineSeries(qtemplates::xy_range(derivative, -6.0, 6.0, 0.1), "Derivative");

    this->showChart("Cosine");
}