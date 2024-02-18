#include "ChartVisualizers.h"
#include "solvers.h"
#include "uni_dual.h"
#include "uni_math.h"
#include "qtemplates.h"
#include <random>

class SolverVisualizers: public ChartVisualizers{

public:
    const double true_offset = -3.1;
};

TEST_F(SolverVisualizers, noisy_sigmoid) {
    constexpr auto parameter_sigmoid = [](auto offset, auto x) {
        return 1.0 / (1.0 + exp(-x - offset));
    };

    // noisy sigmoid
    std::random_device rd;  // will be used to obtain a seed for the random number engine
    std::mt19937 gen(123); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(-0.5, 0.5);

    auto noisy_sigmoid = [parameter_sigmoid, &gen, &dis](double x, double offset)->double {
        return parameter_sigmoid(offset, x) + 1.0 * dis(gen);
    };

    auto data = qtemplates::xy_range([noisy_sigmoid, this](double x){
        return noisy_sigmoid(x, true_offset);},
                                     -10.0, 10.0, 0.1);

    this->addLineSeries(qtemplates::xy_range([parameter_sigmoid](auto x){
        return parameter_sigmoid(0.1, x);},
                                             -10.0, 10.0, 0.1), "pure sigmoid");
    this->addLineSeries(data, "noisy sigmoid");

    this->showChart("fit sigmoid to noisy data");
}

//TEST_F(SolverVisualizers, fit_noisy_sigmoid) {
//    constexpr auto parameter_sigmoid = [](auto offset, auto x) {
//        return 1.0 / (1.0 + exp(-x - offset));
//    };
//
//    // noisy sigmoid
//    std::random_device rd;  // will be used to obtain a seed for the random number engine
//    std::mt19937 gen(1231); // Standard mersenne_twister_engine seeded with rd()
//    std::uniform_real_distribution<> dis(-0.5, 0.5);
//
//    auto noisy_sigmoid = [parameter_sigmoid, &gen, &dis](double x, double offset)->double {
//        return parameter_sigmoid(offset, x) + 1.0 * dis(gen);
//    };
//
//    auto data = qtemplates::xy_range([noisy_sigmoid, this](double x){
//                                         return noisy_sigmoid(x, true_offset);},
//                                     -10.0, 10.0, 0.1);
//
//    // transform data to vector of std pairs
//    std::vector<std::pair<double, double>> data_vector;
//    for (auto& xy: data) {
//        data_vector.emplace_back(xy.x(), xy.y());
//    }
//
//    // define loss function
//
//    auto loss = [parameter_sigmoid, &data_vector](auto offset) {
//        auto single_loss = [parameter_sigmoid, &offset]( auto&  xy) {
//            auto x = xy.first;
//            auto y = xy.second;
//            auto t = y - parameter_sigmoid(offset, x);
//            return t * t;
//        };
//        auto loss = agregators::sum(single_loss, data_vector);
//        return loss;
//    };
//
//    this->addLineSeries(qtemplates::xy_range([loss](auto offset){
//        return loss(offset);
//        },-10.0, 10.0, 0.1), "loss function");
//    this->showChart("loss function");
//
////    auto diff_loss = differentiate(loss);
//
//    // find minimum of loss function
////    auto minimum = solvers::newton_solver(loss, 0.0);
//
////    EXPECT_EQ(minimum, true_offset);
//}