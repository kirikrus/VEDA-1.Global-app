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
    if (data.isArray()) doc = QJsonDocument(data.toArray());
    else if (data.isObject()) doc = QJsonDocument(data.toObject());

    // �������������� JSON � ������ � ���������� �������
    QByteArray jsonData = QString("\'%1\'").arg(doc.toJson(QJsonDocument::Compact)).toUtf8();
    qDebug() << "POST Request json:" << jsonData;

    QNetworkReply* reply = networkManager->post(request, jsonData);

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, [&]() {loop.quit();});

    loop.exec();
}

void HTTPclient::put(const QString& endpoint, const QJsonValue& data){
    QUrl url(endpoint);
    qDebug() << "PUT Request URL:" << url.toString();
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonDocument doc;
    if (data.isArray()) doc = QJsonDocument(data.toArray());
    else if (data.isObject()) doc = QJsonDocument(data.toObject());

    // �������������� JSON � ������ � ���������� �������
    QByteArray jsonData = QString("\'%1\'").arg(doc.toJson(QJsonDocument::Compact)).toUtf8();
    qDebug() << "PUT Request json:" << jsonData;

    QNetworkReply* reply = networkManager->put(request, jsonData);

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, [&]() {loop.quit();});

    loop.exec();
}

void HTTPclient::delet(const QString& endpoint, const int id){
    QUrl url(endpoint);
    qDebug() << "PUT Request URL:" << url.toString();
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // �������������� JSON � ������ � ���������� �������
    QByteArray jsonData = QString("[%1]").arg(id).toUtf8();
    qDebug() << "PUT Request json:" << jsonData;

    QNetworkReply* reply = networkManager->sendCustomRequest(request, "DELETE", jsonData);

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, [&]() {loop.quit();});

    loop.exec();
}

void HTTPclient::onReplyFinished(QNetworkReply* reply) {
    qDebug() << "onReplyFinished called";
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        qDebug() << "Response data:" << responseData;
        QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObject = jsonResponse.object();
        emit requestFinished(jsonObject);
    }
    else {
        qDebug() << "Error sending POST request:" << reply->errorString();
        qDebug() << "Response data:" << reply->readAll();
        emit requestError(reply->errorString());
    }
    reply->deleteLater();
}
