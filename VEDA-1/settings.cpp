#include "modalUserInfo.h"
#include "settings.h"

void show_settings(Ui::VEDA1Class* ui) {
	ui->nameS->setText(MAIN_USER_POINTER->getUserName());
	ui->emailS->setText(MAIN_USER_POINTER->getEmail());
	ui->phoneS->setText(MAIN_USER_POINTER->getPhone());
	ui->passwordS->setText(MAIN_USER_POINTER->getPassword());

	QObject::connect(ui->exitUser, &QPushButton::pressed, [=]() {
		ui->tabWidget->setCurrentIndex(0);
		delete MAIN_USER_POINTER;
		MAIN_USER_POINTER = nullptr;
		CURRENT_EXP = -1;
		USER_ENTERED = false;
		});
}