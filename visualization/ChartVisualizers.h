#pragma once
#include <string>
#include <QApplication>
#include <QChart>
#include <QLineSeries>


class ChartVisualizers {
protected:
    ChartVisualizers();

    ~ChartVisualizers();

    void addLineSeries(const QList<QPointF> &points, const std::string &name);

    void showChart(const std::string& title);

private:
    QApplication *app;
    QChart *chart;
    QList<QLineSeries *> series;
};