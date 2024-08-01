#include "article.h"
#include "mainPage.h"

void mainPage(Ui::VEDA1Class* ui) {
	HTTPclient http;
	QEventLoop loop;

	QString endpoint = QString("http://localhost:5011/Article/AllArticles");

	QObject::connect(&http, &HTTPclient::requestFinished, [&](const QJsonObject& jsonResponse) {
        qDebug() << "Articles data received";
        QJsonArray arr = jsonResponse["articles"].toArray();

        for (const QJsonValue& value : arr) {
            QJsonObject obj = value.toObject();
            quint32 id = obj["id"].toInt();
            quint32 authorId = obj["authorId"].toInt();
            QString text = obj["text"].toString();
            QString jsonDate = QString(obj["date"].toString());
            QDate date = QDate::fromString(jsonDate, "yyyy-MM-dd");

            article* a = new article(ui, id, authorId, text,date);
        }
		loop.quit();
		});

	http.get(endpoint);
	loop.exec();
}