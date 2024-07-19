#include "Profile.h"
#include <qlineedit.h>
#include "UserData.h"
#include "qchart.h"
#include <qchartview.h>
#include <qvalueaxis.h>

bool USER_ENTERED = false;
UserData* MAIN_USER_POINTER;

void showChart(Ui::VEDA1Class*,int);

void show_auth(Ui::VEDA1Class* ui) {
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

    //inp_email->setText(user.getUserName());
    
}

void show_experiments(Ui::VEDA1Class *ui, UserData *user) {
    QVector<experiment> experiments = user->getExperiments();

    ui->tableExp->setColumnCount(4);
    ui->tableExp->setRowCount(experiments.size());
    // установка заголовков таблицы
    QStringList headers;
    headers << "\320\255\320\272\321\201\320\277\320\265\321\200\320\270\320\274\320\265\320\275\321\202"//Эксперимент
            << "\320\234\320\260\321\202\320\265\321\200\320\270\320\260\320\273"//Материал
            << "\320\237\321\200\320\276\321\206\320\265\321\201\321\201"//Процесс
            << "\320\224\320\260\321\202\320\260";//Дата

    ui->tableExp->setHorizontalHeaderLabels(headers);

    QTableWidgetItem d(experiments[1].getMaterial());

    for (int i = 0; i < experiments.size(); ++i) {
        ui->tableExp->setItem(i, 0, new QTableWidgetItem(QString::fromLocal8Bit("Эксперимент №") + QString::number(experiments[i].getId())));
        ui->tableExp->setItem(i, 1, new QTableWidgetItem(experiments[i].getMaterial()));

        QLabel* processLabel = new QLabel(experiments[i].getProcessTypeName());//для красивой отрисовки тега процесса
        processLabel->setObjectName(QString::fromUtf8("label_11"));
        processLabel->setGeometry(QRect(175, 80, 86, 16));
        QString rgb = "color: rgb(255, 255, 255);\n";
        processLabel->setStyleSheet("background-color: rgb(65, 93, 138);\n"
            "border-radius: 8px;\n" + rgb +
            "margin-top: 5px;\n"
            "margin-left: 40px;");
        processLabel->setAlignment(Qt::AlignCenter);
        processLabel->setMaximumSize(QSize(115,21));
        ui->tableExp->setCellWidget(i, 2, processLabel);
        
        ui->tableExp->setItem(i, 3, new QTableWidgetItem(experiments[i].getDate().toString("dd.MM.yy")));
    }

    ui->tableExp->setColumnWidth(0, 250);
    ui->tableExp->setColumnWidth(1, 225);
    ui->tableExp->setColumnWidth(2, 150);
    ui->tableExp->setColumnWidth(3, 75);

   QObject::connect(ui->tableExp, &QTableWidget::cellClicked, [=](int row, int) {
        showChart(ui,row);
        });
}

void showChart(Ui::VEDA1Class *ui,int row){
    if (ui->chart->scene()) {
        QList<QGraphicsItem*> items = ui->chart->scene()->items();
        for (QGraphicsItem* item : items)
            ui->chart->scene()->removeItem(item);
        ui->chart->scene()->clear();
        delete ui->chart->scene();
    }

    experiment exp = MAIN_USER_POINTER->getExperiments()[row];
    QLineSeries* series = exp.getChart();
    
    QChart* chart = new QChart;
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    

//стилизация
    chart->setTitle(QString::fromLocal8Bit("Эксперимент №") + QString::number(exp.getId()));
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
    ui->chart->show();
}

void show_profile(Ui::VEDA1Class *ui) {
    if (!USER_ENTERED) {
        //show_auth(ui);
    }
    ui->tabWidget->setCurrentIndex(1);
    UserData user(1);
    MAIN_USER_POINTER = new UserData(1);
    show_experiments(ui, &user);
}