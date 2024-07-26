#include "VEDA1.h"
#include <qobject.h>
#include "Profile.h"
#include <qlineedit.h>

void connections(Ui::VEDA1Class *ui) {
//коннект скрола
	ui->verticalScrollBar->setMaximum(ui->scrollArea->verticalScrollBar()->maximum());
	QObject::connect(ui->scrollArea->verticalScrollBar(), &QScrollBar::valueChanged, ui->verticalScrollBar, &QScrollBar::setValue);
	QObject::connect(ui->verticalScrollBar, &QScrollBar::valueChanged, ui->scrollArea->verticalScrollBar(), &QScrollBar::setValue);

//кнопка переключения на авторизацию
	QObject::connect(ui->profile_button, &QPushButton::clicked, [=]() {show_profile(ui);});

//кнопка переключения на главную
	QObject::connect(ui->home_button, &QPushButton::clicked, [=]() {ui->tabWidget->setCurrentIndex(0);});

//Развертка блока с точками на странице профиля
	QObject::connect(ui->dataViewChange, &QPushButton::clicked, [=]() {
		if (ui->dataGraphPanel->height() == 626) {
			ui->dataGraphPanel->setGeometry(610, 435, 351, 196);
			ui->dataGraphTable->setFixedHeight(141);
			ui->dataViewChange->setText(QString::fromLocal8Bit("Развернуть  >"));
		}
		else {
			ui->dataGraphPanel->setGeometry(610, 5, 351, 626);
			ui->dataGraphTable->setFixedHeight(576);
			ui->dataViewChange->setText(QString::fromLocal8Bit("Свернуть    >"));
		}
		});
	QObject::connect(ui->dataChange, &QPushButton::clicked, [=]() {
		if (ui->edite->height() == 626) {
			ui->edite->setGeometry(20, 580, 571, 51);
			ui->dataChange->setText(("\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214 \320\264\320\260\320\275\320\275\321\213\320\265"));//Открыть редактор
		}
		else {
			ui->edite->setGeometry(20, 10, 571, 626);
			ui->dataChange->setText(("\320\227\320\260\320\272\321\200\321\213\321\202\321\214 \321\200\320\265\320\264\320\260\320\272\321\202\320\276\321\200"));//Закрыть редактор
		}
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
		});
	QObject::connect(ui->settingPage, &QPushButton::pressed, [=]() {
		ui->tabWidget_2->setCurrentIndex(0);
		ui->hightlighter->setGeometry(ui->settingPage->geometry());
		ui->expPage->setDisabled(false);
		ui->settingPage->setDisabled(true);
		ui->adminPage->setDisabled(false);
		});
	QObject::connect(ui->adminPage, &QPushButton::pressed, [=]() {
		ui->tabWidget_2->setCurrentIndex(2);
		ui->hightlighter->setGeometry(ui->adminPage->geometry());
		ui->expPage->setDisabled(false);
		ui->settingPage->setDisabled(false);
		ui->adminPage->setDisabled(true);
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
			delete label_45;
			delete addMember;
			delete label_46;
			delete memberBt;
			delete exitMemberBt;
			delete backdrop;
			delete widget;
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
		
}