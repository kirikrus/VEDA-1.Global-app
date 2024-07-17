#include <qobject.h>
#include <qjsonobject.h>
#include <qjsondocument.h>
#include <qnetworkreply.h>
#include <qnetworkrequest.h>
#include <qnetworkaccessmanager.h>
#include <qurl.h>

class HTTPclient : public QObject {
    Q_OBJECT

public:
    HTTPclient(QObject* parent = nullptr);
    void fetchUserData(const QString& userId);

signals:
    void userDataReceived(const QString& userName);

private slots:
    void onReplyFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager* networkManager;
};

