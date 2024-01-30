#include "ChartVisualizers.h"
#include <QChartView>
#include <QMainWindow>

void ChartVisualizers::SetUp() {
    int argc = 0;
    char **argv = nullptr;
    app = new QApplication(argc, argv);
    chart = new QChart();
}

void ChartVisualizers::TearDown() {
    delete app;
}

void ChartVisualizers::showChart(const std::string &title) {
    for (auto &s : series) {
        chart->addSeries(s);
    }

    chart->createDefaultAxes();
    chart->setTitle(QString::fromStdString(title));

    auto *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();

    app->exec();
}

void ChartVisualizers::addLineSeries(const QList<QPointF> &points, const std::string &name) {
    auto *function_plot = new QLineSeries();
    function_plot->setName(QString::fromStdString(name));
    function_plot->replace(points);
    function_plot->setName(QString::fromStdString(name));
    series.append(function_plot);

}


