#include "MSGconstructor.h"

bool msg(QMessageBox::Icon icon, QString name, QString info, QMessageBox::StandardButtons buttons){
    QMessageBox msgBox;
    msgBox.setIcon(icon);
    msgBox.setText(name);
    msgBox.setInformativeText(info);
    msgBox.setStyleSheet("background-color: #202325; color: White;");
    msgBox.setStandardButtons(buttons);
    int ret = msgBox.exec();

    switch (ret) {
    case QMessageBox::Ok: return true;
    case QMessageBox::Yes: return true;
    case QMessageBox::No: return false;
    case QMessageBox::Cancel: return false;
    }
}
