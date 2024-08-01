#include "Profile.h"
#include "qchart.h"
#include "modalUserInfo.h"
#include "MSGconstructor.h"

#include <qchartview.h>
#include <qlineedit.h>
#include <qstandarditemmodel.h>
#include <qvalueaxis.h>

void show_users(Ui::VEDA1Class* ui);
void showChart(Ui::VEDA1Class*);
void show_exp_data(Ui::VEDA1Class* ui);

void validate(Ui::VEDA1Class* ui) {
    if (MAIN_USER_POINTER == nullptr) {
        ui->articleAdd->setVisible(false);
    }
    else {
        ui->articleAdd->setEnabled(true);
    }
    if (CURRENT_EXP != -1)
        if (MAIN_USER_POINTER->getExperimentById(CURRENT_EXP)->getAuthorId() == MAIN_USER_POINTER->getId() || MAIN_USER_POINTER->is_admin()) {
            ui->add_member->show();
            ui->expChange->show();
        }
        else {
            ui->expPage->setDisabled(true);
            ui->add_member->hide();
            ui->expChange->hide();
        }
    if (!MAIN_USER_POINTER->is_admin())
        ui->adminPage->hide();
    else
        ui->adminPage->show();
    ui->expCreate->hide();
}

void show_auth(Ui::VEDA1Class* ui) {

#pragma region print
    QFrame* backdrop = new QFrame(ui->centralWidget);

    backdrop->setGeometry(ui->centralWidget->rect());
    backdrop->setStyleSheet("background-color: rgba(22, 25, 26, 200);");
    backdrop->show();

    QWidget* widget;
    QLabel* label_2;
    QLineEdit* inp_email;
    QLineEdit* inp_password;
    QLabel* label_8;
    QLabel* label_9;
    QLabel* label_10;
    QLabel* label_11;
    QLabel* label_21;
    QPushButton* pushButton;

    widget = new QWidget(ui->centralWidget);
    widget->setObjectName(QString::fromUtf8("widget"));
    widget->setGeometry(QRect(245, 125, 571, 443));
    widget->setStyleSheet(QString::fromUtf8("background-color: #202325;\n"
        "border-radius: 36px\n"
        ""));
    label_2 = new QLabel(widget);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setGeometry(QRect(30, 30, 201, 386));
    label_2->setSizeIncrement(QSize(0, 0));
    label_2->setPixmap(QPixmap(QString::fromUtf8(":/icons/icons/back_auth.png")));
    label_2->setScaledContents(true);
    inp_email = new QLineEdit(widget);
    inp_email->setObjectName(QString::fromUtf8("inp_email"));
    inp_email->setGeometry(QRect(295, 115, 210, 43));
    inp_email->setStyleSheet(QString::fromUtf8("background-color: rgb(217, 217, 217);\n"
        "border-radius: 14px"));
    inp_email->setInputMethodHints(Qt::ImhEmailCharactersOnly);
    inp_email->setAlignment(Qt::AlignCenter);
    inp_password = new QLineEdit(widget);
    inp_password->setObjectName(QString::fromUtf8("inp_password"));
    inp_password->setGeometry(QRect(295, 200, 210, 43));
    inp_password->setStyleSheet(QString::fromUtf8("background-color: rgb(217, 217, 217);\n"
        "border-radius: 14px"));
    inp_password->setInputMethodHints(Qt::ImhNone);
    inp_password->setAlignment(Qt::AlignCenter);
    label_8 = new QLabel(widget);
    label_8->setObjectName(QString::fromUtf8("label_8"));
    label_8->setGeometry(QRect(345, 20, 136, 51));
    QFont font6;
    font6.setFamilies({ QString::fromUtf8("Inter V") });
    font6.setPointSize(30);
    font6.setBold(true);
    label_8->setFont(font6);
    label_8->setStyleSheet(QString::fromUtf8("color: white\n"
        ""));
    label_9 = new QLabel(widget);
    label_9->setObjectName(QString::fromUtf8("label_9"));
    label_9->setGeometry(QRect(295, 95, 16, 16));
    QFont font7;
    font7.setFamilies({ QString::fromUtf8("Inter V") });
    font7.setPointSize(16);
    font7.setBold(true);
    label_9->setFont(font7);
    label_9->setStyleSheet(QString::fromUtf8("color: rgb(242, 54, 54);"));
    label_10 = new QLabel(widget);
    label_10->setObjectName(QString::fromUtf8("label_10"));
    label_10->setGeometry(QRect(295, 180, 16, 16));
    label_10->setFont(font7);
    label_10->setStyleSheet(QString::fromUtf8("color: rgb(242, 54, 54);"));
    label_11 = new QLabel(widget);
    label_11->setObjectName(QString::fromUtf8("label_11"));
    label_11->setGeometry(QRect(310, 95, 200, 16));
    QFont font5;
    font5.setFamilies({ QString::fromUtf8("Inter V") });
    font5.setPointSize(12);
    font5.setBold(false);
    label_11->setFont(font5);
    label_11->setStyleSheet(QString::fromUtf8("color: white"));
    label_21 = new QLabel(widget);
    label_21->setObjectName(QString::fromUtf8("label_21"));
    label_21->setGeometry(QRect(310, 180, 71, 16));
    label_21->setFont(font5);
    label_21->setStyleSheet(QString::fromUtf8("color: white"));
    pushButton = new QPushButton(widget);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));
    pushButton->setGeometry(QRect(295, 370, 210, 43));
    QFont font8;
    font8.setFamilies({ QString::fromUtf8("Inter V") });
    font8.setPointSize(20);
    font8.setBold(false);
    pushButton->setFont(font8);
    pushButton->setStyleSheet(QString::fromUtf8("QPushButton{\nbackground-color: rgb(163, 236, 90);\nborder-radius: 14px;\n}\nQPushButton:hover{\nbackground-color: rgb(203, 255, 130);\n}"));
    inp_email->setPlaceholderText(QCoreApplication::translate("VEDA1Class", "email@stankin.ru", nullptr));
    inp_password->setPlaceholderText(QCoreApplication::translate("VEDA1Class", "***********", nullptr));
    label_8->setText(QCoreApplication::translate("VEDA1Class", "\320\222\321\205\320\276\320\264", nullptr));
    label_9->setText(QCoreApplication::translate("VEDA1Class", "*", nullptr));
    label_10->setText(QCoreApplication::translate("VEDA1Class", "*", nullptr));
    label_11->setText(QCoreApplication::translate("VEDA1Class", "\320\237\320\276\321\207\321\202\320\260", nullptr));
    label_21->setText(QCoreApplication::translate("VEDA1Class", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
    pushButton->setText(QCoreApplication::translate("VEDA1Class", "\320\222\320\276\320\271\321\202\320\270", nullptr));
    widget->raise();
    widget->show();
#pragma endregion
    
    QObject::connect(pushButton, &QPushButton::pressed, [=]() {
        QString login = inp_email->text();
        QString password = inp_password->text();
        
        MAIN_USER_POINTER = new UserData(login, password);
        if (MAIN_USER_POINTER->getId() >= 1) {
            delete widget;
            delete backdrop;
            USER_ENTERED = true;
            MAIN_USER_POINTER->download_data();

            show_profile(ui);
            validate(ui);
        }
        else {
            QString err = MAIN_USER_POINTER->getId() == -1 ? QString::fromLocal8Bit("Такой Email не зарегестрирован... \n =(")
                                                           : QString::fromLocal8Bit("Неверный пароль! \n =(");
            msg(QMessageBox::Critical, QString::fromLocal8Bit("Упс..."), err, QMessageBox::Ok);
            delete MAIN_USER_POINTER;
        }
        });
}

void show_experiments(Ui::VEDA1Class *ui) {
    QVector<experiment> experiments = MAIN_USER_POINTER->getExperiments();

    ui->tableExp->setColumnCount(4);
    ui->tableExp->setRowCount(experiments.size());
    // установка заголовков таблицы
    QStringList headers;
    headers << "\320\255\320\272\321\201\320\277\320\265\321\200\320\270\320\274\320\265\320\275\321\202"//Эксперимент
            << "\320\234\320\260\321\202\320\265\321\200\320\270\320\260\320\273"//Материал
            << "\320\237\321\200\320\276\321\206\320\265\321\201\321\201"//Процесс
            << "\320\224\320\260\321\202\320\260";//Дата

    ui->tableExp->setHorizontalHeaderLabels(headers);

    for (int i = 0; i < experiments.size(); ++i) {
        if (experiments[i].getName() == "") 
            ui->tableExp->setItem(i, 0, new QTableWidgetItem(QString::fromLocal8Bit("Эксперимент №") + QString::number(experiments[i].getId())));
        else
            ui->tableExp->setItem(i, 0, new QTableWidgetItem(experiments[i].getName()));
        ui->tableExp->setItem(i, 1, new QTableWidgetItem(experiments[i].getMaterial()));

        QString tag = experiments[i].getProcessTypeName();
        int tagId = experiments[i].getProcessTypeId();
        QRgb tagColor = experiments[i].getProcessTypeColor(tagId);
        QLabel* processLabel = new QLabel(tag);//для красивой отрисовки тега процесса
        processLabel->setObjectName(QString::fromUtf8("label_11"));
        processLabel->setGeometry(QRect(175, 80, 86, 16));

        processLabel->setStyleSheet("border-radius: 8px;\n" +
            QString("background-color: rgb(%1, %2, %3);").arg(QColor(tagColor).red()).arg(QColor(tagColor).green()).arg(QColor(tagColor).blue()) +
            "color: rgb(255, 255, 255);\n"
            "margin-top: 5px;\n"
            "margin-left: 40px;");
        processLabel->setAlignment(Qt::AlignCenter);
        processLabel->setMaximumSize(QSize(115,21));
        ui->tableExp->setCellWidget(i, 2, processLabel);
        
        ui->tableExp->setItem(i, 3, new QTableWidgetItem(experiments[i].getDate().toString("dd.MM.yy")));
    }

    ui->tableExp->setColumnWidth(0, 332);
    ui->tableExp->setColumnWidth(1, 332);
    ui->tableExp->setColumnWidth(2, 155);
    ui->tableExp->setColumnWidth(3, 75);

    QObject::disconnect(ui->tableExp, &QTableWidget::cellClicked, nullptr, nullptr);
    QObject::connect(ui->tableExp, &QTableWidget::cellClicked, [=](int row, int) {
        CURRENT_EXP = row;
        showChart(ui);
        show_exp_data(ui);
        show_users(ui);
        validate(ui);
        });
}

void show_users(Ui::VEDA1Class* ui) {
    auto users = MAIN_USER_POINTER->getExperimentById(CURRENT_EXP)->getMembersId();
    
    QLayoutItem* item;
    while ((item = ui->verticalLayout_2->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    if (MAIN_USER_POINTER->getId() == MAIN_USER_POINTER->getExperimentById(CURRENT_EXP)->getAuthorId() || MAIN_USER_POINTER->is_admin()) {
        ui->add_member->show();
    }
    else {
        ui->add_member->hide();
    }

    for (int id : users) 
        ui->verticalLayout_2->addWidget(new modalUserInfo(new UserData(id), ui, MAIN_USER_POINTER->getExperimentById(CURRENT_EXP), ui->scrollAreaWidgetContents_2));
}

void showChart(Ui::VEDA1Class *ui){
    if (ui->chart->scene()) {
        QGraphicsScene* oldScene = ui->chart->scene();
        QList<QGraphicsItem*> items = oldScene->items();
        for (QGraphicsItem* item : items)
            oldScene->removeItem(item); 
        oldScene->clear();
        ui->chart->setScene(nullptr);
        delete oldScene;
    }

    experiment* exp = MAIN_USER_POINTER->getExperimentById(CURRENT_EXP);

    QLineSeries* series = exp->getChart();
    
    QChart* chart = new QChart;
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    

//стилизация
    chart->setTitle(QString::fromLocal8Bit("Эксперимент №") + QString::number(exp->getId()));
    chart->setTitleBrush(QBrush(QColor("#d4d4d4")));

    chart->setMinimumSize(ui->chart->size());

    QPen pen(QColor("#A3EC5A"));
    pen.setWidth(1);
    series->setPen(pen);

    chart->setBackgroundBrush(QBrush(QColor("#202325")));
    chart->setPlotAreaBackgroundVisible(false);
    
    QValueAxis* axisX = dynamic_cast<QValueAxis*>(chart->axisX());
    QValueAxis* axisY = dynamic_cast<QValueAxis*>(chart->axisY());

    QFont labelsFont;
    labelsFont.setPixelSize(12);
    labelsFont.setFamily("Inter V");
    axisX->setLabelsFont(labelsFont);
    axisY->setLabelsFont(labelsFont);
    labelsFont.setPixelSize(16);
    labelsFont.setBold(true);
    chart->setTitleFont(labelsFont);

    axisX->setLineVisible(false);
    axisY->setLineVisible(false);

    QBrush axisBrush(QColor("#d4d4d4"));
    axisX->setLabelsBrush(axisBrush);
    axisY->setLabelsBrush(axisBrush);

    axisX->setGridLineVisible(false);
    axisY->setGridLineColor(QColor("#363b3e"));

    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setStyleSheet("background-color: #202325;""color: rgb(212, 212, 212);");
//---

    ui->chart->setScene(new QGraphicsScene());
    ui->chart->scene()->addWidget(chartView);
}

void show_exp_data(Ui::VEDA1Class* ui) {
    experiment* exp = MAIN_USER_POINTER->getExperimentById(CURRENT_EXP);
    QLineSeries* series = exp->getChart();


    QAbstractItemModel* oldModel = ui->dataGraphTable->model();//чистим память
    if (oldModel) delete oldModel;

    QStandardItemModel* model = new QStandardItemModel(0, 3, ui->dataGraphTable); //3 столбца

    model->setHorizontalHeaderLabels({ "ID", 
        QString::fromLocal8Bit("Время"), 
         exp->getChartLink()->getParamUnit()});

    ui->dataGraphTable->setColumnWidth(0, 50);
    ui->dataGraphTable->setColumnWidth(1, 130);
    ui->dataGraphTable->setColumnWidth(2, 130);

    //установка данных в модели
    int id = 0;
    for (const QPointF& point : series->points()) {
        QList<QStandardItem*> rowItems;
        rowItems.append(new QStandardItem(QString::number(id)));
        rowItems.append(new QStandardItem(QString::number(point.x())));
        rowItems.append(new QStandardItem(QString::number(point.y())));
        model->appendRow(rowItems);
        id++;
    }

    ui->dataGraphTable->setModel(model);
    ui->dataGraphTable->show();
}

void show_profile(Ui::VEDA1Class *ui) {
    if (!USER_ENTERED) {
        show_auth(ui);
        return;
    }
    ui->tabWidget->setCurrentIndex(1);

    show_experiments(ui);
}

void data_Editer(Ui::VEDA1Class* ui, QString type_of_method) {
    HTTPclient http;
    QJsonArray data;
    QJsonObject item;

    if (type_of_method == "POST") {
        item["value"] = ui->inp_num_add->value();
        item["timepoint"] = ui->inp_time_add->value();
        item["parameterid"] = (int)MAIN_USER_POINTER->getExperimentById(CURRENT_EXP)->getProcessTypeId();
        item["experimentid"] = (int)MAIN_USER_POINTER->getExperimentById(CURRENT_EXP)->getId();
        data.append(item);

        QString endpoint = "http://localhost:5011/Experiment/PutNewData";
        http.post(endpoint, data);
    }
    else if (type_of_method == "PUT") {
        item["value"] = ui->inp_num_put->value();
        item["timepoint"] = ui->inp_time_put->value();
        item["id"] = (int)MAIN_USER_POINTER->getExperimentById(CURRENT_EXP)->getChartLink()->getPointId(ui->inp_id_put->value());
        data.append(item);

        QString endpoint = "http://localhost:5011/Experiment/UpdateData";
        http.put(endpoint, data);
    }
    else if (type_of_method == "DELETE") {
        int id = (int)MAIN_USER_POINTER->getExperimentById(CURRENT_EXP)->getChartLink()->getPointId(ui->inp_id_del->value() );
        if (id == -1) return;

        QString err = QString::fromLocal8Bit("Вы хотите удалить точку № %1?").arg(ui->inp_id_del->value());
        bool yes = msg(QMessageBox::Question, "", err, QMessageBox::Yes | QMessageBox::No);

        if (yes) {
            QString endpoint = "http://localhost:5011/Experiment/DeleteData";
            http.delet(endpoint, id);
        }
        else return;
    }

    showChart(ui);
    show_exp_data(ui);
}