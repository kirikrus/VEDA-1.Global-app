#pragma once

#include <QObject>
#include <QString>
#include <QEventLoop>
#include "experiment.h"


class UserData : public QObject {
    Q_OBJECT

public:
    UserData(QString login, QString password, QObject* parent = nullptr);
    UserData(int id, QObject* parent = nullptr);

    void download_data();
    QString getUserName() const;
    QString getEmail() const;
    QString getPhone() const;
    int getId() const;
    QVector<experiment> getExperiments() const;
    experiment* getExperimentById(int id);
    bool is_admin();
    void relogin();
    void initExp();
    QString getPassword();
    int getOneoff();//гость
    void setOneoff(int inp);
    void update(QString name, QString phone, QString password, QPixmap avatar);
    QPixmap getAvatar(int size);
    void setAvatar(QString file);

private slots:
    void onUserDataReceived(const QJsonObject& jsonResponse);
    void onUserVerification(const QJsonObject& jsonResponse);
    void onExpDataReceived(const QJsonObject& jsonResponse);
    void onError(const QString& errorString);

private:
    int id;
    QString name;
    QString email;
    QString phone;
    QString password;
    QPixmap avatar;

    int oneoff = 0;
    bool admin = false;

    QVector<experiment> experiments;

    HTTPclient* http;
    HTTPclient* http_for_exp;
    QEventLoop loop;
    QEventLoop loop_for_exp;
};
