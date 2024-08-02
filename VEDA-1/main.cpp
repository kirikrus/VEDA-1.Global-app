#include "VEDA1.h"
#include <QtWidgets/QApplication>
#include "GLOBAL.h"
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSettings settings("config.ini", QSettings::IniFormat);
    SERVER = settings.value("HOST/server").toString();

    VEDA1 w;
    w.show();
    return a.exec();
}
