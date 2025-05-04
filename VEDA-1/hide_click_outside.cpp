#include "hide_click_outside.h"
#include "qevent.h"
#include <ui_VEDA1.h>

hide_click_outside::hide_click_outside(QWidget* parent) : QScrollArea(parent) {};

bool hide_click_outside::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);

        if (!this->rect().contains(this->mapFromGlobal(mouseEvent->globalPos()))) {
            this->hide();
            return true;
        }
    }
    return QWidget::eventFilter(obj, event);
}

void hide_click_outside::showEvent(QShowEvent* event) {
    QWidget::showEvent(event);
    qApp->installEventFilter(this);  // глобальный фильтр
}

void hide_click_outside::hideEvent(QHideEvent* event) {
    QWidget::hideEvent(event);
    qApp->removeEventFilter(this);
}