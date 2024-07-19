#include "VEDA1.h"
#include <qobject.h>
#include "Profile.h"

void connections(Ui::VEDA1Class *ui) {
//������� ������
	QObject::connect(ui->scrollArea->verticalScrollBar(), &QScrollBar::valueChanged, ui->verticalScrollBar, &QScrollBar::setValue);
	QObject::connect(ui->verticalScrollBar, &QScrollBar::valueChanged, ui->scrollArea->verticalScrollBar(), &QScrollBar::setValue);

//������ ������������ �� ������� 
	QObject::connect(ui->profile_button, &QPushButton::clicked, [=]() {show_profile(ui);});

//��������� ����� � ������� �� �������� �������
	QObject::connect(ui->dataViewChange, &QPushButton::clicked, [=]() {
		if (ui->dataGraphPanel->height() == 626) {
			ui->dataGraphPanel->setGeometry(760, 525, 271, 196);
			ui->dataGraphTable->setFixedHeight(141);
			ui->dataViewChange->setText(QString::fromLocal8Bit("����������  >"));
		}
		else {
			ui->dataGraphPanel->setGeometry(760, 95, 271, 626);
			ui->dataGraphTable->setFixedHeight(576);
			ui->dataViewChange->setText(QString::fromLocal8Bit("��������    >"));
		}
		});
}