#include "article.h"
#include "mainPage.h"


void show_all_articles(Ui::VEDA1Class* ui);

void mainPage(Ui::VEDA1Class* ui) {
    if (MAIN_USER_POINTER == nullptr) {
        ui->articleAdd->setEnabled(false);
    }
    else {
        ui->articleAdd->setEnabled(true);
    }
    
    show_all_articles(ui);

    QObject::connect(ui->articleAdd, &QPushButton::pressed, [=]() {
        ui->frame_2->setParent(ui->centralWidget);
        ui->frame_2->show();
        ui->frame_2->setGeometry(QRect(60,65,886,611));
        QFrame* backdrop = new QFrame(ui->centralWidget);
        backdrop->setGeometry(ui->centralWidget->rect());
        backdrop->setStyleSheet("background-color: rgba(22, 25, 26, 200);");
        backdrop->show();
        ui->frame_2->raise();

        QObject::connect(ui->articleExit, &QPushButton::pressed, [=]() {
            delete backdrop;
            ui->frame_2->hide();
            });

        QObject::connect(ui->articlePublish, &QPushButton::pressed, [=]() {
            HTTPclient http;
            QEventLoop loop;
            QJsonObject item;

            item["authorid"] = MAIN_USER_POINTER->getId();
            item["text"] = ui->articleInp->document()->toMarkdown();

            QString endpoint = QString(SERVER + "/Article/PublishArticle");
            QObject::connect(&http, &HTTPclient::requestReply, [&](const QByteArray& reply) {
                if (reply.toInt() <= 0 && reply.size() < 5) {}
                else {
                    delete backdrop;
                    ui->frame_2->hide();
                    show_all_articles(ui);
                }
                loop.quit();
                });

            http.post(endpoint, item);
            loop.exec();
            });
        });
    QObject::connect(ui->articleInp, &QTextEdit::textChanged, [=]() {
        QString inp = ui->articleInp->document()->toMarkdown();
        ui->articleOut->document()->setMarkdown(inp);
        });
}

void show_all_articles(Ui::VEDA1Class* ui) {
    QLayoutItem* item;
    while ((item = ui->verticalLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
    
    HTTPclient http;
    QEventLoop loop;

    QString endpoint = QString(SERVER + "/Article/AllArticles");

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

            article* a = new article(ui, id, authorId, text, date);
        }
        loop.quit();
        });

    http.get(endpoint);
    loop.exec();
}