#include <QObject>
#include <QString>
#include <QEventLoop>
#include "experiment.h"


class UserData : public QObject {
    Q_OBJECT

public:
    UserData(quint32 id_, QObject* parent = nullptr);
    QString getUserName() const;
    QVector<experiment> getExperiments() const;
    experiment* getExperimentById(int id);

private slots:
    void onUserDataReceived(const QJsonObject& jsonResponse);
    void onExpDataReceived(const QJsonObject& jsonResponse);
    void onError(const QString& errorString);

private:
    void initExp();

    quint32 id;
    QString name;

    QVector<experiment> experiments;

    HTTPclient* http;
    HTTPclient* http_for_exp;
    QEventLoop loop;
    QEventLoop loop_for_exp;
};
