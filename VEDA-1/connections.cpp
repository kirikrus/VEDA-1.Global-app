#include "VEDA1.h"
#include <qobject.h>
#include "Profile.h"
#include "admin.h"
#include "graphPage.h"
#include "MSGconstructor.h"
#include <qlineedit.h>
#include <qchartview.h>
#include "GLOBAL.h"
#include "settings.h"
#include "userArticlesPage.h"

void connections(Ui::VEDA1Class *ui) {
//коннект скрола
	bool *blockScrollSignal = new bool(false);
	QObject::connect(ui->scrollArea->verticalScrollBar(), &QScrollBar::valueChanged, [=](int value) {
		if (!*blockScrollSignal) {
			*blockScrollSignal = true;
			double ratio = (double)ui->verticalScrollBar->maximum() / ui->scrollArea->verticalScrollBar()->maximum();
			ui->verticalScrollBar->setValue(value * ratio);
			*blockScrollSignal = false;
		}
		});
	QObject::connect(ui->verticalScrollBar, &QScrollBar::valueChanged, [=](int value) {
		if (!*blockScrollSignal) {
			*blockScrollSignal = true;
			double ratio = (double)ui->scrollArea->verticalScrollBar()->maximum() / ui->verticalScrollBar->maximum();
			ui->scrollArea->verticalScrollBar()->setValue(value * ratio);
			*blockScrollSignal = false;
		}
		});

//кнопка переключения на авторизацию
	QObject::connect(ui->profile_button, &QPushButton::clicked, [=]() {show_profile(ui);});

//кнопка переключения на главную
	QObject::connect(ui->home_button, &QPushButton::clicked, [=]() {ui->tabWidget->setCurrentIndex(0);});

//Развертка блоков на странице профиля
	QObject::connect(ui->dataViewChange, &QPushButton::clicked, [=]() {
		if (ui->dataGraphPanel->height() == 626) {
			ui->dataGraphPanel->setGeometry(610, 435, 351, 196);
			ui->dataGraphTable->setFixedHeight(141);
			ui->dataViewChange->setText(("Развернуть  >"));
		}
		else {
			ui->dataGraphPanel->setGeometry(610, 5, 351, 626);
			ui->dataGraphTable->setFixedHeight(576);
			ui->dataViewChange->setText(("Свернуть    >"));
		}
		});
	QObject::connect(ui->dataChange, &QPushButton::clicked, [=]() {
		if (ui->edite->height() == 626) {
			ui->edite->setGeometry(20, 580, 571, 51);
			ui->dataChange->setText(("\320\240\320\265\320\264\320\260\320\272\321\202\320\276\321\200 \320\264\320\260\320\275\320\275\321\213\321\205"));
			if (CURRENT_EXP == -1)
				return;
			if (MAIN_USER_POINTER->getExperimentById(CURRENT_EXP)->getAuthorId() == MAIN_USER_POINTER->getId() || MAIN_USER_POINTER->is_admin())
				ui->expChange->show();
		}
		else {
			if (MAIN_USER_POINTER->getExperiments().size() == 0)
				return;
			ui->edite->setGeometry(20, 10, 571, 626);
			ui->dataChange->setText(("\320\227\320\260\320\272\321\200\321\213\321\202\321\214 \321\200\320\265\320\264\320\260\320\272\321\202\320\276\321\200"));
			ui->tabWidget_3->setCurrentIndex(0);
			ui->expChange->hide();
		}
		});
	QObject::connect(ui->expChange, &QPushButton::clicked, [=]() {
		if (MAIN_USER_POINTER->getExperiments().size() == 0)
			return;
			ui->edite->setGeometry(20, 10, 571, 626);
			ui->dataChange->setText(("\320\227\320\260\320\272\321\200\321\213\321\202\321\214 \321\200\320\265\320\264\320\260\320\272\321\202\320\276\321\200"));
			ui->tabWidget_3->setCurrentIndex(1);
			ui->expChange->hide();
			ui->expEdit->setText("\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214");
			ui->dataFrame->show();
		});

//Работа с запросами в редакторе
    QObject::connect(ui->addData, &QPushButton::pressed, [=]() {data_Editer(ui,"POST");});
	QObject::connect(ui->putData, &QPushButton::pressed, [=]() {data_Editer(ui, "PUT");});
	QObject::connect(ui->deleteData, &QPushButton::pressed, [=]() {data_Editer(ui, "DELETE");});

//переключение страниц профиля
	QObject::connect(ui->expPage, &QPushButton::pressed, [=]() {
		ui->tabWidget_2->setCurrentIndex(1);
		ui->hightlighter->setGeometry(ui->expPage->geometry());
		ui->expPage->setDisabled(true);
		ui->settingPage->setDisabled(false);
		ui->adminPage->setDisabled(false);
		ui->articlePage->setDisabled(false);
		});
	QObject::connect(ui->settingPage, &QPushButton::pressed, [=]() {
		ui->tabWidget_2->setCurrentIndex(2);
		ui->hightlighter->setGeometry(ui->settingPage->geometry());
		ui->expPage->setDisabled(false);
		ui->settingPage->setDisabled(true);
		ui->adminPage->setDisabled(false);
		ui->articlePage->setDisabled(false);
		show_settings(ui);
		});
	QObject::connect(ui->adminPage, &QPushButton::pressed, [=]() {
		ui->tabWidget_2->setCurrentIndex(0);
		ui->hightlighter->setGeometry(ui->adminPage->geometry());
		ui->expPage->setDisabled(false);
		ui->settingPage->setDisabled(false);
		ui->adminPage->setDisabled(true);
		ui->articlePage->setDisabled(false);
		show_admin_panel(ui);
		});
	QObject::connect(ui->articlePage, &QPushButton::pressed, [=]() {
		ui->tabWidget_2->setCurrentIndex(4);
		ui->hightlighter->setGeometry(ui->articlePage->geometry());
		ui->expPage->setDisabled(false);
		ui->settingPage->setDisabled(false);
		ui->adminPage->setDisabled(false);
		ui->articlePage->setDisabled(true);
		show_user_articles(ui);
		});
	QObject::connect(ui->fullScreenGraph_bt, &QPushButton::pressed, [=]() {
		ui->tabWidget_2->setCurrentIndex(3);
		if(MAIN_USER_POINTER->getExperiments().size() != 0)
			show_graph_page(ui);
		});
	QObject::connect(ui->fullScreenGraph_bt_2, &QPushButton::pressed, [=]() {
		ui->tabWidget_2->setCurrentIndex(1);
		});

//Подсказка 1
	ui->helpBtPanel1->setGeometry(650, 255, 301, 291);
	ui->helpBtPanel1->setVisible(false);
	QObject::connect(ui->helpBt1, &QPushButton::pressed, [=]() {
		ui->helpBtPanel1->setVisible(!ui->helpBtPanel1->isVisible());
		});

//Добавление участника эксп-та
	QObject::connect(ui->add_member, &QPushButton::pressed, [=]() {
		QFrame* backdrop = new QFrame(ui->centralWidget);

		backdrop->setGeometry(ui->centralWidget->rect());
		backdrop->setStyleSheet("background-color: rgba(22, 25, 26, 200);");
		backdrop->show();

		QWidget* widget;
		QLabel* label_45;
		QLineEdit* addMember;
		QLabel* label_46;
		QPushButton* memberBt;
		QPushButton* exitMemberBt;

#pragma region print
		QFont font7;
		font7.setFamilies({ QString::fromUtf8("Inter V") });
		font7.setPointSize(12);
		font7.setBold(true);
		QFont font9;
		font9.setFamilies({ QString::fromUtf8("Inter V") });
		font9.setPointSize(10);

		widget = new QWidget(ui->centralWidget);
		widget->setObjectName(QString::fromUtf8("widget"));
		widget->setGeometry(QRect(370, 250, 341, 201));
		widget->setStyleSheet(QString::fromUtf8("background-color: rgb(32, 35, 37);\n"
			"border-radius: 21px;\n"
			"border: 1px solid rgb(163, 236, 90);\n"
			"color: white;"));
		label_45 = new QLabel(widget);
		label_45->setObjectName(QString::fromUtf8("label_45"));
		label_45->setGeometry(QRect(20, 15, 271, 26));
		label_45->setFont(font7);
		label_45->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
			"border: none;"));
		addMember = new QLineEdit(widget);
		addMember->setObjectName(QString::fromUtf8("addMember"));
		addMember->setGeometry(QRect(45, 75, 246, 41));
		addMember->setStyleSheet(QString::fromUtf8("border: none;\n"
			"border-radius: 20px;\n"
			"background-color: rgb(58, 58, 58);"));
		addMember->setAlignment(Qt::AlignCenter);
		label_46 = new QLabel(widget);
		label_46->setObjectName(QString::fromUtf8("label_46"));
		label_46->setGeometry(QRect(55, 55, 56, 26));
		QFont font12;
		font12.setFamilies({ QString::fromUtf8("Inter V") });
		font12.setPointSize(10);
		font12.setBold(false);
		font12.setKerning(true);
		label_46->setFont(font12);
		label_46->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
			"border: none;\n"
			"color: rgb(212, 212, 212);\n"
			"background-color: rgba(255, 255, 255, 0);"));
		memberBt = new QPushButton(widget);
		memberBt->setObjectName(QString::fromUtf8("memberBt"));
		memberBt->setGeometry(QRect(185, 145, 106, 30));
		memberBt->setFont(font9);
		memberBt->setStyleSheet(QString::fromUtf8("QPushButton{\n"
			"	background-color: transparent;\n"
			"	border: 1px solid rgb(54, 59, 62);\n"
			"border-radius: 15px;\n"
			"color: rgb(212, 212, 212);\n"
			"}\n"
			"QPushButton:hover{\n"
			"	background-color: rgb(58, 58, 58);\n"
			"}"));
		exitMemberBt = new QPushButton(widget);
		exitMemberBt->setObjectName(QString::fromUtf8("exitMemberBt"));
		exitMemberBt->setGeometry(QRect(45, 145, 106, 30));
		exitMemberBt->setFont(font9);
		exitMemberBt->setStyleSheet(QString::fromUtf8("QPushButton{\n"
			"	background-color: transparent;\n"
			"	border: 1px solid rgb(54, 59, 62);\n"
			"border-radius: 15px;\n"
			"color: rgb(212, 212, 212);\n"
			"}\n"
			"QPushButton:hover{\n"
			"	background-color: rgb(58, 58, 58);\n"
			"}"));

		label_45->setText(QCoreApplication::translate("VEDA1Class", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\203\321\207\320\260\321\201\321\202\320\275\320\270\320\272\320\260", nullptr));
		addMember->setPlaceholderText(QCoreApplication::translate("VEDA1Class", "email@stankin.ru", nullptr));
		label_46->setText(QCoreApplication::translate("VEDA1Class", "\320\237\320\276\321\207\321\202\320\260", nullptr));
		memberBt->setText(QCoreApplication::translate("VEDA1Class", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
		exitMemberBt->setText(QCoreApplication::translate("VEDA1Class", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));

#pragma endregion

		QObject::connect(memberBt, &QPushButton::pressed, [=]() {
			HTTPclient http;
			QEventLoop loop;
			QJsonObject item;

			auto exp = MAIN_USER_POINTER->getExperimentById(CURRENT_EXP);

			item["expid"] = (int)exp->getId();
			item["email"] = addMember->text();

			QString endpoint = SERVER + "/User/AddMember";

			QObject::connect(&http, &HTTPclient::requestReply, [&](const QByteArray& reply) {
				switch (reply.toInt()) {
					case -1: 
						msg(QMessageBox::Warning, ("Упс..."), ("Пользователь с данной почтой уже участник!"), QMessageBox::Ok);
						break;
					case -2:
						msg(QMessageBox::Warning, ("Упс..."), ("Пользователь с данной почтой не существует!"), QMessageBox::Ok);
						break;
					default:
						delete label_45;
						delete addMember;
						delete label_46;
						delete memberBt;
						delete exitMemberBt;
						delete backdrop;
						delete widget;
						MAIN_USER_POINTER->initExp();
						show_users(ui);
				}
				loop.quit();
				});

			http.post(endpoint, item);
			loop.exec();
			});

		QObject::connect(exitMemberBt, &QPushButton::pressed, [=]() {
			delete label_45;
			delete addMember;
			delete label_46;
			delete memberBt;
			delete exitMemberBt;
			delete backdrop;
			delete widget;
			});

		widget->show();

		});

//Изменение экспа
	QObject::connect(ui->expChange, &QPushButton::pressed, [=]() {
		HTTPclient http;
		QEventLoop loop;

		QString endpoint = SERVER + "/Experiment/TOP";
		QObject::connect(&http, &HTTPclient::requestFinished, [&](const QJsonObject& jsonResponse) {
			ui->comboExpType->clear();

			QJsonArray arr = jsonResponse["tops"].toArray();

			for (const QJsonValue& value : arr) {
				QJsonObject obj = value.toObject();
				quint32 id = obj["id"].toInt();
				QString jsonDate = obj["name"].toString();

				ui->comboExpType->addItem(jsonDate,id);
			}
			loop.quit();
			});
		http.get(endpoint);
		loop.exec();

		if (MAIN_USER_POINTER->getExperiments().size() == 0)
			return;
		auto exp = MAIN_USER_POINTER->getExperimentById(CURRENT_EXP);

		ui->comboExpType->setCurrentIndex(exp->getProcessTypeId()-1);
		ui->materialExp->setText(exp->getMaterial());
		ui->dateEdit->setDate(exp->getDate());
		if (exp->getName() != "")
			ui->nameExp->setText(exp->getName());
		});
	QObject::connect(ui->deleteExp, &QPushButton::pressed, [=]() {
		auto exp = MAIN_USER_POINTER->getExperimentById(CURRENT_EXP);
		HTTPclient http;

		QString expName;
		if (exp->getName() == "") expName = QString("№%1").arg(exp->getId());
		else expName = exp->getName();

		QString err = QString("Вы хотите удалить эксперимент: %1?").arg(expName);
		bool yes = msg(QMessageBox::Question, "", err, QMessageBox::Yes | QMessageBox::No);

		if (yes) {
			QString endpoint = QString(SERVER + "/Experiment/DeleteExperiment/%1").arg(exp->getId());
			http.delet(endpoint,NULL);
			MAIN_USER_POINTER->initExp();
			show_profile(ui);
		}
		else return;
		});
	QObject::connect(ui->expEdit, &QPushButton::pressed, [=]() {
		HTTPclient http;
		QEventLoop loop;
		QJsonObject item;

		auto exp = MAIN_USER_POINTER->getExperimentById(CURRENT_EXP);

		item["date"] = ui->dateEdit->date().toString("yyyy-MM-dd");
		item["material"] = ui->materialExp->text();
		item["typeofproces_id"] = ui->comboExpType->itemData(ui->comboExpType->currentIndex()).toString();
		item["name"] = ui->nameExp->text();

		QString endpoint = QString(SERVER + "/Experiment/UpdateExperiment/%1").arg(exp->getId());

		QObject::connect(&http, &HTTPclient::requestReply, [&](const QByteArray& reply) {
			if (reply.toInt() <= 0 && reply.size() < 5)
				msg(QMessageBox::Warning, ("Упс..."), ("Перепроверьте данные!"), QMessageBox::Ok);
			else {
				MAIN_USER_POINTER->initExp();
				show_experiments(ui);
			}
			loop.quit();
			});

		http.put(endpoint, item);
		loop.exec();
		});

//Создание экспа
	QObject::connect(ui->add_exp, &QPushButton::pressed, ui->expChange, &QPushButton::pressed);
	QObject::connect(ui->add_exp, &QPushButton::pressed, [=]() {
		ui->edite->setGeometry(20, 10, 571, 626);
		ui->tabWidget_3->setCurrentIndex(1);
		ui->expChange->hide();
		ui->deleteExp->hide();
		ui->expEdit->hide();
		ui->expCreate->show();
		ui->dataFrame->hide();
		});
	QObject::connect(ui->expCreate, &QPushButton::pressed, [=]() {
		HTTPclient http;
		QEventLoop loop;
		QJsonObject item;

		item["authorId"] = MAIN_USER_POINTER->getId();
		item["material"] = ui->materialExp->text();
		item["typeofprocesId"] = ui->comboExpType->itemData(ui->comboExpType->currentIndex()).toString();
		item["name"] = ui->nameExp->text();

		QString endpoint = QString(SERVER + "/Experiment/CreateExperiment");

		QObject::connect(&http, &HTTPclient::requestReply, [&](const QByteArray& reply) {
			if (reply.toInt() <= 0 && reply.size() < 5)
				msg(QMessageBox::Warning, ("Упс..."), ("Перепроверьте данные!"), QMessageBox::Ok);
			else {
				MAIN_USER_POINTER->initExp();
				show_experiments(ui);
			}
			loop.quit();
			});

		http.post(endpoint, item);
		loop.exec();
		});
}