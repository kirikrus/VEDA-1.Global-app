#include "VEDA1.h"
#include <qobject.h>
#include "Profile.h"

void connections(Ui::VEDA1Class *ui) {
//������� ������
	QObject::connect(ui->scrollArea->verticalScrollBar(), &QScrollBar::valueChanged, ui->verticalScrollBar, &QScrollBar::setValue);
	QObject::connect(ui->verticalScrollBar, &QScrollBar::valueChanged, ui->scrollArea->verticalScrollBar(), &QScrollBar::setValue);

//������ ������������ �� ������� 
	QObject::connect(ui->profile_button, &QPushButton::clicked, [=]() {show_profile(ui);});
}