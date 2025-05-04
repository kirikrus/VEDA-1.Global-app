#pragma once

#include <QChartView>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QPointF>

class CustomChartView : public QChartView {
    Q_OBJECT

public:
    CustomChartView(QChart* chart, QWidget* parent = nullptr);

    double scaleFactor = 1;

protected:
    void wheelEvent(QWheelEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;

    void mouseMoveEvent(QMouseEvent* event) override;

    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    bool isDragging;
    QPoint lastMousePos;
};
