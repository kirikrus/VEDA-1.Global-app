#include "VEDA1.h"
#include <qobject.h>

void connections(Ui::VEDA1Class ui) {
	QObject::connect(ui.scrollArea->verticalScrollBar(), &QScrollBar::valueChanged, ui.verticalScrollBar, &QScrollBar::setValue);
	QObject::connect(ui.verticalScrollBar, &QScrollBar::valueChanged, ui.scrollArea->verticalScrollBar(), &QScrollBar::setValue);
}