#include "modalUserInfo.h"
#include "admin.h"

void show_all_users(Ui::VEDA1Class* ui){
    QVector<int> memberId;

    HTTPclient http;
    QEventLoop loop;
    QString endpoint = SERVER + "/Admin/AllUsersId";
    http.get(endpoint);

    QObject::connect(&http, &HTTPclient::requestFinished, [&](const QJsonObject& jsonResponse) {
        QJsonArray membersArray = jsonResponse["usersid"].toArray();
            for (const QJsonValue& value : membersArray)
                memberId.append(value.toInt());
            loop.quit();
        });

    loop.exec();

    QLayoutItem* item;
    while ((item = ui->verticalLayout_3->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    for (int id : memberId)
        ui->verticalLayout_3->addWidget(new modalUserInfo(new UserData(id), ui,nullptr, ui->scrollAreaWidgetContents_3));
}

void show_admin_panel(Ui::VEDA1Class* ui) {
    show_all_users(ui);
}