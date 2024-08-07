#pragma execution_character_set("utf-8")

#include "VEDA1.h"
#include <QtWidgets/QApplication>
#include "GLOBAL.h"
#include <QSettings>
#include "mainPage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSettings settings("config.ini", QSettings::IniFormat);
    SERVER = settings.value("HOST/server").toString();

    VEDA1 w;

    LOADING(&w.ui)
    
    w.show();
    connections(&w.ui);
    mainPage(&w.ui);

    CLOSE_LOADING
    return a.exec();
}
