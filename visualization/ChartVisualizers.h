#pragma once
#include <gtest/gtest.h>
#include <string>
#include <QApplication>
#include <QChart>
#include <QLineSeries>


class ChartVisualizers : public ::testing::Test {
protected:
    void SetUp() override;

    void TearDown() override;

    void addLineSeries(const QList<QPointF> &points, const std::string &name);

    void showChart(const std::string& title);

private:
    QApplication *app;
    QChart *chart;
    QList<QLineSeries *> series;
};