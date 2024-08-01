#include "UserData.h"
#include <QDebug>
#include <QJsonArray>

UserData::UserData(QString login, QString password_, QObject* parent) : QObject(parent) {
    http = new HTTPclient(this);
    http_for_exp = new HTTPclient(this);

    connect(http, &HTTPclient::requestFinished, this, &UserData::onUserVerification);
    connect(http, &HTTPclient::requestError, this, &UserData::onError);
    connect(http_for_exp, &HTTPclient::requestFinished, this, &UserData::onExpDataReceived);
    connect(http_for_exp, &HTTPclient::requestError, this, &UserData::onError);

    password = password_;
    QString endpoint = QString("http://localhost:5011/User/Login?Email=%1&Password=%2").arg(login == ""?"0":login).arg(password==""?"0":password);
    http->get(endpoint);

    loop.exec();
}

UserData::UserData(int id, QObject* parent) : QObject(parent), id(id) {
    http = new HTTPclient(this);
    http_for_exp = new HTTPclient(this);

    connect(http, &HTTPclient::requestFinished, this, &UserData::onUserDataReceived);
    connect(http, &HTTPclient::requestError, this, &UserData::onError);

    QString endpoint = QString("http://localhost:5011/User/%1").arg(id);
    http->get(endpoint);

    loop.exec();
}

void UserData::relogin(){
    loop.quit();
    loop_for_exp.quit();

    QString endpoint = QString("http://localhost:5011/User/Login?Email=%1&Password=%2").arg(name == "" ? "0" : name).arg(password == "" ? "0" : password);
    http->get(endpoint);

    loop.exec();
}

void UserData::onUserVerification(const QJsonObject& jsonResponse) {
    qDebug() << "User data received";
    id = jsonResponse["userId"].toInt();

    loop.quit();

    disconnect(http, &HTTPclient::requestFinished, this, &UserData::onUserVerification);
    connect(http, &HTTPclient::requestFinished, this, &UserData::onUserDataReceived);
}

void UserData::onUserDataReceived(const QJsonObject& jsonResponse) {
    qDebug() << "User data received";
    QJsonObject userObj = jsonResponse["user"].toObject();
    name = userObj["fullName"].toString();
    email = userObj["email"].toString();
    phone = userObj["phone"].toString();
    admin = userObj["admin"].toBool();

    loop.quit();
}

void UserData::download_data(){
    QString endpoint = QString("http://localhost:5011/User/%1").arg(id);
    http->get(endpoint);

    loop.exec();

    initExp();
}

void UserData::initExp() {
    QString endpoint = QString("http://localhost:5011/Experiment/GetExperimentsOfUser/%1").arg(id);
    http_for_exp->get(endpoint);
    
    loop_for_exp.exec();
}

void UserData::onExpDataReceived(const QJsonObject& jsonResponse) {
    experiments.clear();
    qDebug() << "Exp data received";
    QJsonArray experimentsArray = jsonResponse["ExperimentsOfUser"].toArray();

    for (const QJsonValue& value : experimentsArray) {
        QJsonObject experimentObject = value.toObject();
        quint32 id = experimentObject["id"].toInt();
        QString jsonDate = experimentObject["date"].toString();
        QString expName = experimentObject["name"].toString();
        QDate date = QDate::fromString(jsonDate, "yyyy-MM-dd");
        QString material = experimentObject["material"].toString();

        QJsonObject processTypeObject = experimentObject["typeofprocess"].toObject();
        quint32 processTypeId = processTypeObject["id"].toInt();
        QString processTypeName = processTypeObject["name"].toString();

        QJsonArray membersArray = experimentObject["membersid"].toArray();
        QVector<int> memberId;
        for (const QJsonValue& value : membersArray)
            memberId.append(value.toInt());

        int authorId = experimentObject["authorid"].toInt();

        experiments.append(experiment(id, date, material, processTypeId, processTypeName,authorId, memberId, expName));
    }


    loop_for_exp.quit();
}

void UserData::onError(const QString& errorString) {
    qDebug() << "Error received:" << errorString;

    loop.quit();
    loop_for_exp.quit();
}

QString UserData::getUserName() const {return name;}

QString UserData::getEmail() const{return email;}

QString UserData::getPhone() const { return phone; }

int UserData::getId() const{return id;}

QVector<experiment> UserData::getExperiments() const {return experiments;}

experiment* UserData::getExperimentById(int id){return &experiments[id];}

bool UserData::is_admin(){return admin;}

QString UserData::getPassword() { return password; }