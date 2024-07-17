#include "UserData.h"
#include <qeventloop.h>

UserData::UserData(quint32 id_) : id(id_){
	http = new HTTPclient();

    QEventLoop loop;
    connect(http, &HTTPclient::userDataReceived, [&](const QString name_) {
        name = name_;
        loop.quit();
        });

    http->fetchUserData(QString::number(id));
    loop.exec();
}

QString UserData::getUserName() {
	return name;
}