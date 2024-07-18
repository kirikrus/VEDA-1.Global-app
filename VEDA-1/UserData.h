#include <QObject>
#include <QString>
#include "HTTPclient.h"
#include <QEventLoop>

class UserData : public QObject {
    Q_OBJECT

public:
    UserData(quint32 id_, QObject* parent = nullptr);
    QString getUserName() const;

private slots:
    void onUserDataReceived(const QJsonObject& jsonResponse);
    void onError(const QString& errorString);

private:
    quint32 id;
    QString name;
    HTTPclient* http;
    QEventLoop loop;
};
