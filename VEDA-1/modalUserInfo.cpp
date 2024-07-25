#include "modalUserInfo.h"

modalUserInfo::modalUserInfo(UserData* user_,QWidget* parent) : user(user_), QWidget(parent) {
	//connect(this, &QWidget::mousePressEvent, this, &modalUserInfo::goBig);
    
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

void modalUserInfo::goBig(){
    return;
}
