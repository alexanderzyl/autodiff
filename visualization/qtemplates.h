#pragma once
#include <ranges>
#include <numeric>
#include <QVector>
#include <QPointF>

namespace qtemplates
{
    template <typename F>
    auto xy_range(const F& function, double x_min, double x_max, double x_step = 0.1){
        auto num_steps = int((x_max - x_min) / x_step);
        auto x_values = std::views::iota(0, num_steps)
                        | std::views::transform([=](double n){ return x_min + n * x_step; });

        QVector<QPointF> points;
        for (double x : x_values)
        {
            double y = function(x);
            points.append(QPointF(x,y));
        }
        return points;
    }
}