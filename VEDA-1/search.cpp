#include <qrect.h>
#include "searchPanel.h"

void searchPanelShow(Ui::VEDA1Class* ui, QRect rect, QVBoxLayout* order, QString text) {
    if (text == "") return;

	LOADING(ui)

	ui->search_out->setGeometry(rect);

    QLayoutItem* item;
    while ((item = order->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget(); 
        }
        else if (item->layout()) {
            delete item->layout(); 
        }
        delete item;
    }


    HTTPclient http;
    QEventLoop loop;
    QString endpoint;

    if (MAIN_USER_POINTER != nullptr) {
        endpoint = QString(SERVER + "/Search/Auth?jsonRequest=" + text);
        if (MAIN_USER_POINTER->is_admin())
            endpoint = QString(SERVER + "/Search/Admin?jsonRequest=" + text);
    }
    else
        endpoint = QString(SERVER + "/Search/Public?jsonRequest=" + text);
    

    QObject::disconnect(&http, &HTTPclient::requestFinished, nullptr, nullptr);
    QObject::connect(&http, &HTTPclient::requestFinished, [&](const QJsonObject& jsonResponse) {
        qDebug() << "Search data received";
        QJsonObject obj = jsonResponse["searchResult"].toObject();
        QJsonArray art = obj["articles"].toArray();
        QJsonArray exp = obj["experiments"].toArray();
        QJsonArray usr = obj["users"].toArray();

        for (auto item : art) { 
            int id = item.toInt();
            
            QList<article*> allArticles = ui->scrollArea->findChildren<article*>();
            for (article* pointer : allArticles) {
                if (pointer->getId() == id) {
                    ui->search_layout->addWidget(new searchPanel(ui, pointer, ui->search_out_order));
                    break;
                }
            }
        }

        if (MAIN_USER_POINTER != nullptr) {
            for (auto item : exp) {
                int id = item.toInt();

                auto exps = MAIN_USER_POINTER->getExperiments();
                for (int i{ 0 }; i <= exps.size();i++) {
                    if (exps[i].getId() == id) {
                        id = i;
                        break;
                    }
                }

                experiment* pointer = MAIN_USER_POINTER->getExperimentById(id);
                ui->search_layout->addWidget(new searchPanel(ui, pointer, ui->search_out_order));
            }

            for (auto item : usr) {
                int id = item.toInt();
                UserData* pointer = new UserData(id);
                ui->search_layout->addWidget(new searchPanel(ui, pointer, ui->search_out_order));
            }
        }

        QLabel* label_77 = new QLabel(ui->search_out_order);
        label_77->setText(QWidget::tr("Тут больше ничего нет =("));
        QSizePolicy sizePolicy2(QSizePolicy::Ignored, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_77->sizePolicy().hasHeightForWidth());
        label_77->setSizePolicy(sizePolicy2);
        label_77->setMinimumSize(QSize(0, 20));
        label_77->setStyleSheet(QString::fromUtf8("color: gray;"));
        label_77->setAlignment(Qt::AlignCenter);

        ui->search_layout->addWidget(label_77);

        loop.quit();
        CLOSE_LOADING
        });
    http.get(endpoint);
    loop.exec();
}