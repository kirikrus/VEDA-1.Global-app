#include "HTTPclient.h"

HTTPclient::HTTPclient(QObject* parent) : QObject(parent) {
    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, &HTTPclient::onReplyFinished);
}

void HTTPclient::fetchUserData(const QString& userId) {
    QUrl url("http://localhost:5011/User/" + userId);
    qDebug() << "Request URL:" << url.toString();
    QNetworkRequest request(url);
    networkManager->get(request);
}

void HTTPclient::onReplyFinished(QNetworkReply* reply) {
    qDebug() << "onReplyFinished called";
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObject = jsonResponse.object();
        QString userName = jsonObject["userName"].toString();
        emit userDataReceived(userName);
    }
    else {
        qDebug() << "Error:" << reply->errorString();
    }
    reply->deleteLater();
}