#include "HTTPclient.h"
#include <QEventLoop>
#include <QDebug>

HTTPclient::HTTPclient(QObject* parent) : QObject(parent) {
    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, &HTTPclient::onReplyFinished);
}

void HTTPclient::get(const QString& endpoint) {
    QUrl url(endpoint);
    qDebug() << "GET Request URL:" << url.toString();
    QNetworkRequest request(url);
    networkManager->get(request);
}

void HTTPclient::post(const QString& endpoint, const QJsonObject& data) {
    QUrl url(endpoint);
    qDebug() << "POST Request URL:" << url.toString();
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonDocument jsonDoc(data);
    QByteArray jsonData = jsonDoc.toJson();
    networkManager->post(request, jsonData);
}

void HTTPclient::onReplyFinished(QNetworkReply* reply) {
    qDebug() << "onReplyFinished called";
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObject = jsonResponse.object();
        emit requestFinished(jsonObject);
    }
    else {
        qDebug() << "Error:" << reply->errorString();
        emit requestError(reply->errorString());
    }
    reply->deleteLater();
}
