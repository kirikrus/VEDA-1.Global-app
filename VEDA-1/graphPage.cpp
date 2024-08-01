#include "graphPage.h"
#include "CustomChartView.h"
#include "GLOBAL.h"
#include <qchart.h>
#include <qvalueaxis.h>
#include <qchartview.h>

void paintChart(bool show, QChart* chart, QColor color, quint32 id) {
    if (show) {
        auto series = MAIN_USER_POINTER->getExperimentById(id)->getChart();
        QPen pen(color);
        pen.setWidth(1);
        series->setPen(pen);
        series->setName(QString::number(id));
        chart->addSeries(series);
        chart->createDefaultAxes(); // Обновление осей для новой серии
#pragma region style

        chart->setBackgroundBrush(QBrush(QColor("#202325")));
        chart->setPlotAreaBackgroundVisible(false);

        QValueAxis* axisX = dynamic_cast<QValueAxis*>(chart->axisX());
        QValueAxis* axisY = dynamic_cast<QValueAxis*>(chart->axisY());

        QFont labelsFont;
        labelsFont.setPixelSize(12);
        labelsFont.setFamily("Inter V");
        axisX->setLabelsFont(labelsFont);
        axisY->setLabelsFont(labelsFont);
        labelsFont.setPixelSize(16);
        labelsFont.setBold(true);
        chart->setTitleFont(labelsFont);

        axisX->setLineVisible(false);
        axisY->setLineVisible(false);

        QBrush axisBrush(QColor("#d4d4d4"));
        axisX->setLabelsBrush(axisBrush);
        axisY->setLabelsBrush(axisBrush);

        axisX->setGridLineColor(QColor("#363b3e"));
        axisY->setGridLineColor(QColor("#363b3e"));

        axisX->setTickCount(21);
        axisY->setTickCount(21);
#pragma endregion
    }
    else {
        QList<QAbstractSeries*> allSeries = chart->series();
        for (QAbstractSeries* s : allSeries) {
            QLineSeries* lineSeries = qobject_cast<QLineSeries*>(s);
            if (lineSeries && lineSeries->name() == QString::number(id)) {
                chart->removeSeries(lineSeries);
                break;
            }
        }
    }
}

void show_bt(Ui::VEDA1Class* ui,QChart* chart, QVector<QRgb> colors) {
    auto exps = MAIN_USER_POINTER->getExperiments();

    QLayoutItem* item;
    while ((item = ui->horizontalLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    int counter{ 0 };
    for (experiment exp : exps) {
        QPushButton* pushButton = new QPushButton(ui->scrollAreaWidgetContents_4);
        pushButton->setText(exp.getName() == "" ? QString::number(exp.getId()) : exp.getName());
        pushButton->setMinimumSize(QSize(100, 20));
        pushButton->setMaximumSize(QSize(200, 20));
        pushButton->setStyleSheet("*{\n" +
            QString("background-color: rgba(%1, %2, %3, 50);").arg(QColor(colors[counter]).red()).arg(QColor(colors[counter]).green()).arg(QColor(colors[counter]).blue()) +
            "border-radius: 10px\n"
            "}\n"
            "*:checked{\n" +
            QString("background-color: rgba(%1, %2, %3, 255);").arg(QColor(colors[counter]).red()).arg(QColor(colors[counter]).green()).arg(QColor(colors[counter]).blue()) +
            "}");
        pushButton->setCheckable(true);
        if (exp.getId() == CURRENT_EXP+1)
            pushButton->setChecked(true);
        else
            pushButton->setChecked(false);
        pushButton->setFlat(true);

        ui->horizontalLayout->addWidget(pushButton);

        QObject::connect(pushButton, &QPushButton::pressed, [=]() {
            paintChart(!pushButton->isChecked(), chart, QColor(colors[counter]), counter);
            });
        counter++;
    }
}

void show_graph_page(Ui::VEDA1Class* ui){
    if (ui->chart_big->scene()) {
        QGraphicsScene* oldScene = ui->chart_big->scene();
        QList<QGraphicsItem*> items = oldScene->items();
        for (QGraphicsItem* item : items)
            oldScene->removeItem(item);
        oldScene->clear();
        ui->chart_big->setScene(nullptr);
        delete oldScene;
    }

    QVector<QRgb> colors = { qRgb(65, 93, 138),qRgb(160, 82, 45),qRgb(34, 139, 34),qRgb(94, 34, 140),qRgb(140, 137, 34),qRgb(161, 45, 53),qRgb(65, 65, 65),
                            qRgb(65, 93, 238),qRgb(160, 82, 145),qRgb(34, 139, 134),qRgb(94, 34, 240),qRgb(140, 137, 134),qRgb(161, 45, 153),qRgb(65, 65, 165),
                            qRgb(65, 193, 138),qRgb(160, 182, 45),qRgb(34, 239, 34),qRgb(94, 134, 140),qRgb(140, 237, 34),qRgb(161, 145, 53),qRgb(65, 165, 65) };


    experiment* exp = MAIN_USER_POINTER->getExperimentById(CURRENT_EXP);

    QLineSeries* series = exp->getChart();

    QChart* chart = new QChart;
    chart->legend()->hide();
    series->setName(QString::number(CURRENT_EXP));
    chart->addSeries(series);
    chart->createDefaultAxes();

#pragma region style
    chart->setMinimumSize(ui->chart_big->size());

    QPen pen(colors[CURRENT_EXP]);
    pen.setWidth(1);
    series->setPen(pen);

    chart->setBackgroundBrush(QBrush(QColor("#202325")));
    chart->setPlotAreaBackgroundVisible(false);

    QValueAxis* axisX = dynamic_cast<QValueAxis*>(chart->axisX());
    QValueAxis* axisY = dynamic_cast<QValueAxis*>(chart->axisY());

    QFont labelsFont;
    labelsFont.setPixelSize(12);
    labelsFont.setFamily("Inter V");
    axisX->setLabelsFont(labelsFont);
    axisY->setLabelsFont(labelsFont);
    labelsFont.setPixelSize(16);
    labelsFont.setBold(true);
    chart->setTitleFont(labelsFont);

    axisX->setLineVisible(false);
    axisY->setLineVisible(false);

    QBrush axisBrush(QColor("#d4d4d4"));
    axisX->setLabelsBrush(axisBrush);
    axisY->setLabelsBrush(axisBrush);

    axisX->setGridLineColor(QColor("#363b3e"));
    axisY->setGridLineColor(QColor("#363b3e"));

    CustomChartView* chartView = new CustomChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setStyleSheet("background-color: #202325;""color: rgb(212, 212, 212);");

    axisX->setTickCount(21);
    axisY->setTickCount(21);
#pragma endregion

    chartView->setMouseTracking(true);

    ui->chart_big->setScene(new QGraphicsScene());
    ui->chart_big->scene()->addWidget(chartView);

    show_bt(ui, chart, colors);
}