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

    TOKEN_ADD

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

    // ѕреобразование JSON в строку и добавление кавычек
    QByteArray jsonData = QString("\'%1\'").arg(doc.toJson(QJsonDocument::Compact)).toUtf8();
    qDebug() << "POST Request json:" << jsonData;

    TOKEN_ADD

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

    // ѕреобразование JSON в строку и добавление кавычек
    QByteArray jsonData = QString("\'%1\'").arg(doc.toJson(QJsonDocument::Compact)).toUtf8();
    qDebug() << "PUT Request json:" << jsonData;

    TOKEN_ADD

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

    // ѕреобразование JSON в строку и добавление кавычек
    QByteArray jsonData = QString("[%1]").arg(id).toUtf8();
    qDebug() << "PUT Request json:" << jsonData;

    TOKEN_ADD

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

        if (authToken == nullptr) {
            QVariant headerToken = reply->rawHeader("tasty-cookies");
            if (headerToken.isValid()) {
                authToken = headerToken.toString();
                qDebug() << "Token extracted and stored:" << authToken;
            }
        }
        emit requestFinished(jsonObject, authToken);
    }
    else {
        qDebug() << "Error sending POST request:" << reply->errorString();
        qDebug() << "Response data:" << reply->readAll();
        
        switch (reply->error()) {
        case QNetworkReply::AuthenticationRequiredError:
            //MAIN_USER_POINTER->relogin();
            break;
        }

        emit requestError(reply->errorString());
    }
    reply->deleteLater();
}
