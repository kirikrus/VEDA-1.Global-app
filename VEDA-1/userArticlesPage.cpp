#include "article.h"
#include "userArticlesPage.h"

void show_user_articles(Ui::VEDA1Class* ui){
    QLayoutItem* item;
    while ((item = ui->verticalLayout_4->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    HTTPclient http;
    QEventLoop loop;

    QString endpoint = QString(SERVER + QString("/Article/UserArticles/%1").arg(MAIN_USER_POINTER->getId()));

    QObject::connect(&http, &HTTPclient::requestFinished, [&](const QJsonObject& jsonResponse) {
        qDebug() << "Articles data received";
        QJsonArray arr = jsonResponse["articles"].toArray();

        for (const QJsonValue& value : arr) {
            QJsonObject obj = value.toObject();
            quint32 id = obj["id"].toInt();
            quint32 authorId = obj["authorId"].toInt();
            QString text = obj["text"].toString();

            QString jsonDate = QString(obj["date"].toString());
            QString jsonTime = QString(obj["time"].toString());
            QDate date = QDate::fromString(jsonDate, "yyyy-MM-dd");
            QTime time = QTime::fromString(jsonTime, "hh:mm:ss");
            QString dateTime = date.toString("dd.MM.yy");
            if (QDate::currentDate().year() - date.year() == 0 &&
                QDate::currentDate().month() - date.month() == 0 &&
                QDate::currentDate().day() - date.day() == 0)
                dateTime = time.toString("hh:mm");

            article* a = new article(ui, id, authorId, text, dateTime, ui->verticalLayout_4);
        }
        loop.quit();
        });

    http.get(endpoint);
    loop.exec();
}
