#include "modalUserInfo.h"
#include "settings.h"
#include "Profile.h"
#include "MSGconstructor.h"
#include "qregularexpression.h"

void password_lvl(Ui::VEDA1Class* ui, const QString& text) {
	quint16 lvl = 0;
	text.length() >= 8 ? lvl++ : 0;
	text.contains(QRegularExpression("[a-z]")) == true ? lvl++ : 0;
	text.contains(QRegularExpression("[A-Z]")) == true ? lvl++ : 0;
	text.contains(QRegularExpression("[0-9]")) == true ? lvl++ : 0;
	text.contains(QRegularExpression("[^a-zA-Z0-9]")) == true ? lvl++ : 0;

	QColor rgb;

	switch (lvl) {
	case 0:
		rgb = QColor(qRgb(179, 61, 61));
		ui->password_lvl->setText("Пустой");
		break;
	case 1:
		rgb = QColor(qRgb(179, 112, 61));
		ui->password_lvl->setText("Очень слабый");
		break;
	case 2:
		rgb = QColor(qRgb(179, 161, 61));
		ui->password_lvl->setText("Слабый");
		break;
	case 3:
		rgb = QColor(qRgb(155, 179, 61));
		ui->password_lvl->setText("Средний");
		break;
	case 4:
		rgb = QColor(qRgb(120, 179, 61));
		ui->password_lvl->setText("Надежный");
		break;
	case 5:
		rgb = QColor(qRgb(163, 236, 90));
		ui->password_lvl->setText("Очень надежный");
		break;
	}

	ui->passwordS->setStyleSheet(QString("border: 1px solid rgb(%1, %2, %3);").arg(rgb.red()).arg(rgb.green()).arg(rgb.blue()) + \
		"background-color: rgb(22, 25, 26);"
		"border-radius: 10px;"
		"color: White;"
	);
	ui->password_lvl->setStyleSheet(QString("color: rgb(%1, %2, %3);").arg(rgb.red()).arg(rgb.green()).arg(rgb.blue()));
}

void show_settings(Ui::VEDA1Class* ui) {
	ui->phoneS->setInputMask("\8(999)-999-99-99;");
	ui->passwordS->setEchoMode(QLineEdit::EchoMode::PasswordEchoOnEdit);

	ui->nameS->setText(MAIN_USER_POINTER->getUserName());
	ui->emailS->setText(MAIN_USER_POINTER->getEmail());
	ui->phoneS->setText(MAIN_USER_POINTER->getPhone());
	ui->passwordS->setText(MAIN_USER_POINTER->getPassword());
	ui->user_ico_bt->setIcon(QIcon(MAIN_USER_POINTER->getAvatar(126)));
	
	password_lvl(ui, MAIN_USER_POINTER->getPassword());

	QObject::connect(ui->passwordS, &QLineEdit::textChanged, [=](const QString& text) {password_lvl(ui, text);});

	QObject::disconnect(ui->userSave, &QPushButton::pressed, nullptr, nullptr);
	QObject::connect(ui->userSave, &QPushButton::pressed, [=]() {
		HTTPclient http;
		QEventLoop loop;
		QJsonObject item;

		item["fullname"] = ui->nameS->text();
		item["phone"] = ui->phoneS->text().replace(QRegularExpression("[()\\-]"), "");
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
				ui->home_button->setDisabled(false);
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