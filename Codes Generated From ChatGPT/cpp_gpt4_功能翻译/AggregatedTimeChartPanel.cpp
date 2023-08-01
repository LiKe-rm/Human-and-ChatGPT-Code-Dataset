#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <map>
#include <chrono>
#include <memory>
#include <functional>
#include "collect_server.h"
#include "node.h"
#include "sensor_data.h"

#include <QVBoxLayout>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QWidget>

using namespace QtCharts;

class AggregatedTimeChartPanel {
public:
    AggregatedTimeChartPanel(CollectServer& server,
                             const std::string& category,
                             const std::string& title,
                             const std::string& timeAxisLabel,
                             const std::string& valueAxisLabel)
        : server_(server),
          category_(category),
          title_(title),
          chart_(std::make_unique<QChart>()),
          chart_view_(std::make_unique<QChartView>(chart_.get())),
          series_(std::make_unique<QLineSeries>()) {
        chart_->setTitle(QString::fromStdString(title));
        chart_->addSeries(series_.get());
        chart_->createDefaultAxes();

        QDateTimeAxis* axisX = new QDateTimeAxis;
        axisX->setTickCount(10);
        axisX->setFormat("hh:mm");
        axisX->setTitleText(QString::fromStdString(timeAxisLabel));
        chart_->setAxisX(axisX, series_.get());

        QValueAxis* axisY = new QValueAxis;
        axisY->setLabelFormat("%.1f");
        axisY->setTitleText(QString::fromStdString(valueAxisLabel));
        chart_->setAxisY(axisY, series_.get());

        QVBoxLayout* mainLayout = new QVBoxLayout;
        mainLayout->addWidget(chart_view_.get());
        this->setLayout(mainLayout);
    }

    virtual ~AggregatedTimeChartPanel() = default;

    std::string getCategory() const {
        return category_;
    }

    std::string getTitle() const {
        return title_;
    }

    QWidget* getPanel() {
        return this;
    }

    void nodeAdded(std::shared_ptr<Node> node) {
        // Ignore
    }

    void nodesSelected(std::vector<std::shared_ptr<Node>> nodes) {
        if (isVisible()) {
            updateSelected(nodes);
        }
    }

protected:
    CollectServer& server_;
    std::string category_;
    std::string title_;
    std::unique_ptr<QChart> chart_;
    std::unique_ptr<QChartView> chart_view_;
    std::unique_ptr<QLineSeries> series_;
    std::vector<std::shared_ptr<Node>> selected_nodes_;
    std::map<std::shared_ptr<Node>, std::shared_ptr<void>> selected_map_;

private:
    void updateSelected(std::vector<std::shared_ptr<Node>>& nodes) {
        // Add implementation for updating selected nodes
    }
};

int main() {
    // Initialize the simulation, AggregatedTimeChartPanel objects and other required components here
    // For example:
    // QApplication app(argc, argv);
    // CollectServer server;
    // AggregatedTimeChartPanel chart_panel(server, "category", "title", "Time", "Value");
    // chart_panel.show();
    // return app.exec();

    return 0;
}
