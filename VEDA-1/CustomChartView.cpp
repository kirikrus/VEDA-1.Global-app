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
    // Масштабирование при помощи колесика мыши
    if (event->angleDelta().y() > 0) {
        chart()->zoomIn();
    }
    else {
        chart()->zoomOut();
    }
    event->accept();
}

void CustomChartView::mousePressEvent(QMouseEvent* event)  {
    // Начало панорамирования
    if (event->button() == Qt::LeftButton) {
        isDragging = true;
        lastMousePos = event->pos();
        setCursor(Qt::ClosedHandCursor); // Изменение курсора
    }
    QChartView::mousePressEvent(event);
}

void CustomChartView::mouseMoveEvent(QMouseEvent* event) {
    if (event->buttons() & Qt::LeftButton) {
        // Перемещение графика при удерживании левой кнопки мыши
        QPointF delta = (lastMousePos - event->pos()) * scaleFactor;
        chart()->scroll(delta.x(), -delta.y());
        lastMousePos = event->pos();
    }
    QChartView::mouseMoveEvent(event);
}


void CustomChartView::mouseReleaseEvent(QMouseEvent* event) {
    // Конец панорамирования
    if (event->button() == Qt::LeftButton) {
        isDragging = false;
        setCursor(Qt::ArrowCursor); // Возврат к обычному курсору
    }
    QChartView::mouseReleaseEvent(event);
}
        