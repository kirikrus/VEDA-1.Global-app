#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <qjsonarray.h>

#define TOKEN_ADD       if (!authToken.isEmpty()) {\
                            request.setRawHeader("Authorization", "Bearer " + authToken.toUtf8());\
                        }

class HTTPclient : public QObject {
    Q_OBJECT

public:
    explicit HTTPclient(QObject* parent = nullptr);

    void get(const QString& endpoint);
    void post(const QString& endpoint, const QJsonValue& data);
    void put(const QString& endpoint, const QJsonValue& data);
    void delet(const QString& endpoint, const int id);
    void deleteWithCondition(const QString& endpoint, const QJsonValue& data);

signals:
    void requestFinished(const QJsonObject& response, QString authToken = nullptr);
    void requestError(const QString& errorString);
    void requestReply(const QByteArray);

private slots:
    void onReplyFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager* networkManager;
    static inline QString authToken;
};

