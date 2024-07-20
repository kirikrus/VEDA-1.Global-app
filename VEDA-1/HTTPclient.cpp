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

void HTTPclient::post(const QString& endpoint, const QJsonValue& data) {
    QUrl url(endpoint);
    qDebug() << "POST Request URL:" << url.toString();
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonDocument doc;
    if (data.isArray())
        doc = QJsonDocument(data.toArray());
    else if (data.isObject())
        doc = QJsonDocument(data.toObject());

    // ѕреобразование JSON в строку и добавление кавычек
    QByteArray jsonData = QString("\'%1\'").arg(doc.toJson(QJsonDocument::Compact)).toUtf8();
    qDebug() << "POST Request json:" << jsonData;

    QNetworkReply* reply = networkManager->post(request, jsonData);

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, [&]() {
        loop.quit();
        });

    loop.exec();


    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();
            qDebug() << "Response data:" << responseData;
            QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
            QJsonObject jsonObject = jsonResponse.object();
            emit requestFinished(jsonObject);
        } else {
            qDebug() << "Error sending POST request:" << reply->errorString();
            qDebug() << "Response data:" << reply->readAll();
            emit requestError(reply->errorString());
        }
        reply->deleteLater();
    });
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
