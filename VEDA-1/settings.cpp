#include "modalUserInfo.h"
#include "settings.h"
#include "Profile.h"
#include "MSGconstructor.h"

void show_settings(Ui::VEDA1Class* ui) {
	ui->nameS->setText(MAIN_USER_POINTER->getUserName());
	ui->emailS->setText(MAIN_USER_POINTER->getEmail());
	ui->phoneS->setText(MAIN_USER_POINTER->getPhone());
	ui->passwordS->setText(MAIN_USER_POINTER->getPassword());

	QObject::disconnect(ui->userSave, &QPushButton::pressed, nullptr, nullptr);
	QObject::connect(ui->userSave, &QPushButton::pressed, [=]() {
		HTTPclient http;
		QEventLoop loop;
		QJsonObject item;

		item["fullname"] = ui->nameS->text();
		item["phone"] = ui->phoneS->text();
		item["password"] = ui->passwordS->text();

		QString endpoint = SERVER + QString("/User/UserSettings/%1").arg(MAIN_USER_POINTER->getId());

		QObject::connect(&http, &HTTPclient::requestReply, [&](const QByteArray& reply) {
			if (reply.toInt() <= 0 && reply.size() < 5)
				msg(QMessageBox::Warning, ("Упс..."), ("Перепроверьте данные!"), QMessageBox::Ok);
			else {
				ui->expPage->setDisabled(false);
				ui->settingPage->setDisabled(true);
				ui->adminPage->setDisabled(false);
				ui->articlePage->setDisabled(false);
				MAIN_USER_POINTER->setOneoff(0);
				MAIN_USER_POINTER->update(ui->nameS->text(), ui->phoneS->text(), ui->passwordS->text());
			}
			loop.quit();
			});

		http.put(endpoint, item);
		loop.exec();
		});

	QObject::connect(ui->exitUser, &QPushButton::pressed, [=]() {
		ui->tabWidget->setCurrentIndex(0);
		delete MAIN_USER_POINTER;
		MAIN_USER_POINTER = nullptr;
		CURRENT_EXP = -1;
		USER_ENTERED = false;
		validate(ui);
		});
}