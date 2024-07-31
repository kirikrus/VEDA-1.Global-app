#include "modalUserInfo.h"
#include "MSGconstructor.h"
#include "Profile.h"

#include <QMouseEvent>

modalUserInfo::modalUserInfo(UserData* user_, Ui::VEDA1Class* ui, QWidget* parent) : user(user_),ui(ui), QWidget(parent) {
    
    name.setParent(this);
    ava.setParent(this);
    status.setParent(this);
    panel.setParent(this);
    
    setMaximumSize(QSize(316, 42));
    setMinimumSize(QSize(316, 42));
    setStyleSheet(QString::fromUtf8("QWidget{\n"
        "border: 1px solid rgb(212, 212, 212);\n"
        "color: White;\n"
        "	font: 10pt \"Inter V\";\n"
        "}\n"
        "QWidget:hover{\n"
        "	background-color: rgba(212, 212, 212, 50);\n"
        "}"));

    panel.setMaximumSize(QSize(316, 42));
    panel.setMinimumSize(QSize(316, 42));
    panel.setStyleSheet(QString::fromUtf8("QWidget{\n"
        "border: 1px solid rgb(212, 212, 212);\n"
        "color: White;\n"
        "	font: 10pt \"Inter V\";\n"
        "}\n"
        "QWidget:hover{\n"
        "	background-color: rgba(212, 212, 212, 50);\n"
        "}"));

    name.setObjectName(QString::fromUtf8("label_9"));
    name.setGeometry(QRect(45, 5, 221, 31));
    name.setStyleSheet(QString::fromUtf8("*{\n"
        "border: none;\n"
        "}\n"
        "*:hover{\n"
        "	background-color: transparent;\n"
        "}"));
    name.setTextFormat(Qt::AutoText);
    name.setScaledContents(true);
    name.setWordWrap(false);
    name.setText(user->getUserName());
    ava.setObjectName(QString::fromUtf8("label_45"));
    ava.setGeometry(QRect(4, 3, 35, 35));
    ava.setStyleSheet(QString::fromUtf8("*{\n"
        "border: none;\n"
        "}\n"
        "*:hover{\n"
        "	background-color: transparent;\n"
        "}"));
    ava.setPixmap(QPixmap(QString::fromUtf8(":/icons/icons/test_avatar.png")));
    ava.setScaledContents(true);
    status.setObjectName(QString::fromUtf8("label_46"));
    status.setGeometry(QRect(265, 7, 25, 25));
    status.setStyleSheet(QString::fromUtf8("*{\n"
        "border: none;\n"
        "}\n"
        "*:hover{\n"
        "	background-color: transparent;\n"
        "}"));
    if(user->is_admin())
        status.setPixmap(QPixmap(QString::fromUtf8(":/icons/icons/crown.png")));
    status.setScaledContents(true);
}

modalUserInfo::~modalUserInfo(){
    delete user;
    user = nullptr;
}

void modalUserInfo::mousePressEvent(QMouseEvent* event) {
    switch (event->button())
    {
    case Qt::LeftButton:
        goBig();
        break;
    case Qt::RightButton:
        if (ui->tabWidget_2->currentIndex() == 0) {}
        else if (MAIN_USER_POINTER->getId() != MAIN_USER_POINTER->getExperimentById(CURRENT_EXP)->getAuthorId()) 
                if (!MAIN_USER_POINTER->is_admin())
                    return;
        
        QString err = QString::fromLocal8Bit("Вы хотите удалить\n%1?").arg(user->getUserName());
        bool yes = msg(QMessageBox::Question, "", err, QMessageBox::Yes | QMessageBox::No);
        if (yes) {
            HTTPclient http;
            QEventLoop loop;
            QJsonObject item;

            auto exp = MAIN_USER_POINTER->getExperimentById(CURRENT_EXP);

            item["expid"] = (int)exp->getId();
            item["userid"] = user->getId();

            QString endpoint = "http://localhost:5011/User/ExcludeMember";

            http.deleteWithCondition(endpoint, item);

            MAIN_USER_POINTER->initExp();
            show_users(ui);
        }
        break;
    }
}

void modalUserInfo::goBig() {
    QFrame* backdrop = new QFrame(ui->centralWidget);

    backdrop->setGeometry(ui->centralWidget->rect());
    backdrop->setStyleSheet("background-color: rgba(22, 25, 26, 200);");
    backdrop->show();

    QWidget* widget;
    QLabel* photo;
    QLabel* name_;
    QLabel* phone;
    QLabel* email;

#pragma region print
    widget = new QWidget(ui->centralWidget);
    widget->setGeometry(QRect(310, 225, 446, 281));
    widget->setStyleSheet(QString::fromUtf8("background-color: rgb(32, 35, 37);\n"
        "border-radius: 21px;\n"
        "border: 1px solid rgb(163, 236, 90);"));
    photo = new QLabel(widget);
    photo->setGeometry(QRect(20, 20, 100, 100));
    photo->setStyleSheet(QString::fromUtf8("background-color: rgb(32, 35, 37);\n"
        "border: none"));
    photo->setPixmap(QPixmap(QString::fromUtf8(":/icons/icons/test_avatar.png")));
    photo->setScaledContents(true);
    name_ = new QLabel(widget);
    name_->setGeometry(QRect(140, 25, 276, 86));
    QFont font12;
    font12.setFamilies({ QString::fromUtf8("Inter V") });
    font12.setPointSize(16);
    font12.setBold(true);
    name_->setFont(font12);
    name_->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
        "background-color: rgb(32, 35, 37);\n"
        "border: none"));
    name_->setWordWrap(true);
    email = new QLabel(widget);
    email->setGeometry(QRect(85, 140, 281, 26));
    QFont font7;
    font7.setFamilies({ QString::fromUtf8("Inter V") });
    font7.setPointSize(12);
    font7.setBold(true);
    email->setFont(font7);
    email->setStyleSheet(QString::fromUtf8("color: rgb(212, 212, 212);\n"
        "background-color: rgb(32, 35, 37);\n"
        "border: none"));
    email->setAlignment(Qt::AlignCenter);
    email->setWordWrap(true);
    phone = new QLabel(widget);
    phone->setGeometry(QRect(85, 170, 281, 26));
    phone->setFont(font7);
    phone->setStyleSheet(QString::fromUtf8("color: rgb(212, 212, 212);\n"
        "background-color: rgb(32, 35, 37);\n"
        "border: none"));
    phone->setAlignment(Qt::AlignCenter);
    phone->setWordWrap(true);
    QPushButton* user_ok_bt = new QPushButton(widget);
    user_ok_bt->setGeometry(QRect(120, 225, 211, 30));
    user_ok_bt->setFont(font7);
    user_ok_bt->setStyleSheet(QString::fromUtf8("QPushButton{\n"
        "	background-color: transparent;\n"
        "	border: 1px solid rgb(54, 59, 62);\n"
        "border-radius: 15px;\n"
        "color: rgb(212, 212, 212);\n"
        "}\n"
        "QPushButton:hover{\n"
        "	background-color: rgb(58, 58, 58);\n"
        "}"));

    phone->setTextInteractionFlags(Qt::TextInteractionFlag::TextSelectableByMouse);
    email->setTextInteractionFlags(Qt::TextInteractionFlag::TextSelectableByMouse);
#pragma endregion

    name_->setText(user->getUserName());
    phone->setText(user->getPhone());
    email->setText(user->getEmail());
    user_ok_bt->setText("\320\227\320\260\320\272\321\200\321\213\321\202\321\214");

    widget->raise();
    widget->show();

    connect(user_ok_bt, &QPushButton::pressed, [=]() {
        delete email;
        delete phone;
        delete name_;
        delete photo;
        delete widget;
        delete backdrop;
        });
}