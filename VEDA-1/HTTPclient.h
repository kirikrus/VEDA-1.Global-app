#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <qjsonarray.h>

class HTTPclient : public QObject {
    Q_OBJECT

public:
    explicit HTTPclient(QObject* parent = nullptr);

    void get(const QString& endpoint);
    void post(const QString& endpoint, const QJsonValue& data);
    void put(const QString& endpoint, const QJsonValue& data);
    void delet(const QString& endpoint, const int id);

signals:
    void requestFinished(const QJsonObject& response);
    void requestError(const QString& errorString);

private slots:
    void onReplyFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager* networkManager;
};

