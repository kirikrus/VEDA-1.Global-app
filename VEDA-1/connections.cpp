#include "VEDA1.h"
#include <qobject.h>
#include "Profile.h"

void connections(Ui::VEDA1Class *ui) {
//коннект скрола
	QObject::connect(ui->scrollArea->verticalScrollBar(), &QScrollBar::valueChanged, ui->verticalScrollBar, &QScrollBar::setValue);
	QObject::connect(ui->verticalScrollBar, &QScrollBar::valueChanged, ui->scrollArea->verticalScrollBar(), &QScrollBar::setValue);

//кнопка переключения на профиль 
	QObject::connect(ui->profile_button, &QPushButton::clicked, [=]() {show_profile(ui);});

//Развертка блока с точками на странице профиля
	QObject::connect(ui->dataViewChange, &QPushButton::clicked, [=]() {
		if (ui->dataGraphPanel->height() == 626) {
			ui->dataGraphPanel->setGeometry(760, 525, 271, 196);
			ui->dataGraphTable->setFixedHeight(141);
			ui->dataViewChange->setText(QString::fromLocal8Bit("Развернуть  >"));
		}
		else {
			ui->dataGraphPanel->setGeometry(760, 95, 271, 626);
			ui->dataGraphTable->setFixedHeight(576);
			ui->dataViewChange->setText(QString::fromLocal8Bit("Свернуть    >"));
		}
		});
}