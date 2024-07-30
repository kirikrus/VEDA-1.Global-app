#include "CustomChartView.h"

#include <QChartView>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QPointF>


CustomChartView::CustomChartView(QChart* chart, QWidget* parent)
    : QChartView(chart, parent), isDragging(false) {
    setRenderHint(QPainter::Antialiasing);
}
    
void CustomChartView::wheelEvent(QWheelEvent* event)  {
    // ��������������� ��� ������ �������� ����
    if (event->angleDelta().y() > 0) {
        chart()->zoomIn();
    }
    else {
        chart()->zoomOut();
    }
    event->accept();
}

void CustomChartView::mousePressEvent(QMouseEvent* event)  {
    // ������ ���������������
    if (event->button() == Qt::LeftButton) {
        isDragging = true;
        lastMousePos = event->pos();
        setCursor(Qt::ClosedHandCursor); // ��������� �������
    }
    QChartView::mousePressEvent(event);
}

void CustomChartView::mouseMoveEvent(QMouseEvent* event) {
    if (event->buttons() & Qt::LeftButton) {
        // ����������� ������� ��� ����������� ����� ������ ����
        QPointF delta = (lastMousePos - event->pos()) * scaleFactor;
        chart()->scroll(delta.x(), -delta.y());
        lastMousePos = event->pos();
    }
    QChartView::mouseMoveEvent(event);
}


void CustomChartView::mouseReleaseEvent(QMouseEvent* event) {
    // ����� ���������������
    if (event->button() == Qt::LeftButton) {
        isDragging = false;
        setCursor(Qt::ArrowCursor); // ������� � �������� �������
    }
    QChartView::mouseReleaseEvent(event);
}
        