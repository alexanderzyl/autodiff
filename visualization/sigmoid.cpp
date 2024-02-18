#include <gtest/gtest.h>
#include "qtemplates.h"
#include "ChartVisualizers.h"

class SigmoidVisualizations: public ChartVisualizers{
protected:
};

TEST_F(SigmoidVisualizations, sigmoid) {
    constexpr auto sigmoid = [](auto x, auto offset, auto scale, auto max, auto min) {
        using namespace std;
        return (max - min) / (1.0 + exp(-scale * (x - offset))) + min;
    };

    constexpr auto offset = 1.0;
    constexpr auto scale = 2.0;
    constexpr auto max = 5.0;
    constexpr auto min = 0.0;

    constexpr auto concrete_sigmoid = [sigmoid, offset, scale, max, min](auto x) {
        return sigmoid(x, offset, scale, max, min);
    };

    this->addLineSeries(qtemplates::xy_range(concrete_sigmoid, -10.0, 10.0, 0.1), "Sigmoid");

    this->showChart("Sigmoid");
}