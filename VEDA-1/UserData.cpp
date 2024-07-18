#include "UserData.h"
#include <QDebug>

UserData::UserData(quint32 id_, QObject* parent) : QObject(parent), id(id_) {
    http = new HTTPclient(this);


    connect(http, &HTTPclient::requestFinished, this, &UserData::onUserDataReceived);
    connect(http, &HTTPclient::requestError, this, &UserData::onError);

    QString endpoint = QString("http://localhost:5011/User/%1").arg(id);
    http->get(endpoint);

    loop.exec();
}

void UserData::onUserDataReceived(const QJsonObject& jsonResponse) {
    qDebug() << "User data received";
    name = jsonResponse["userName"].toString();

    loop.quit();
}

void UserData::onError(const QString& errorString) {
    qDebug() << "Error received:" << errorString;

    loop.quit();
}

QString UserData::getUserName() const {return name;}
