#include "VEDA1.h"
#include <qobject.h>
#include "Profile.h"

void connections(Ui::VEDA1Class ui) {
//коннект скрола
	QObject::connect(ui.scrollArea->verticalScrollBar(), &QScrollBar::valueChanged, ui.verticalScrollBar, &QScrollBar::setValue);
	QObject::connect(ui.verticalScrollBar, &QScrollBar::valueChanged, ui.scrollArea->verticalScrollBar(), &QScrollBar::setValue);

//коннект кнопок на главном экране
	//QObject::connect(ui.profile_button, &QPushButton::hover, [=]() { //кнопка переключения на профиль 
	//	ui.switcher->setStyleSheet("background-color: white;\nborder-radius: 27px;");
    //});
	QObject::connect(ui.profile_button, &QPushButton::clicked, [=]() { //кнопка переключения на профиль 
		show_profile(ui);
		});
}