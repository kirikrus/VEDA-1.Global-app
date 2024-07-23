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
	QObject::connect(ui->dataChange, &QPushButton::clicked, [=]() {
		if (ui->edite->height() == 626) {
			ui->edite->setGeometry(260, 670, 486, 51);
			ui->dataChange->setText(("\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214 \320\264\320\260\320\275\320\275\321\213\320\265"));//Открыть редактор
		}
		else {
			ui->edite->setGeometry(260, 95, 486, 626);
			ui->dataChange->setText(("\320\227\320\260\320\272\321\200\321\213\321\202\321\214 \321\200\320\265\320\264\320\260\320\272\321\202\320\276\321\200"));//Закрыть редактор
		}
		});

//Работа с запросами в редакторе
    QObject::connect(ui->addData, &QPushButton::pressed, [=]() {data_Editer(ui,"POST");});
	QObject::connect(ui->putData, &QPushButton::pressed, [=]() {data_Editer(ui, "PUT");});
	QObject::connect(ui->deleteData, &QPushButton::pressed, [=]() {data_Editer(ui, "DELETE");});
}