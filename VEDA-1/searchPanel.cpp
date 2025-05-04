#include "searchPanel.h"
#include <qsizepolicy.h>
#include <qevent.h>
#include "modalUserInfo.h"
#include "Profile.h"
#include "mainPage.h"

searchPanel::searchPanel(Ui::VEDA1Class* ui, ::article* inp, QWidget* parrent) : ui(ui), article(inp), QWidget(parrent) {
    type.setText(tr("  Статья  ")); //0
    type_ = 0;
    text_str = inp->getText();
    color = "background-color: rgb(85, 156, 255);";
    paint();
}

searchPanel::searchPanel(Ui::VEDA1Class* ui, experiment* inp, QWidget* parrent) : ui(ui), exp(inp), QWidget(parrent) {
    type.setText(tr("  Эксперимент  ")); //1
    type_ = 1;
    text_str = inp->getName();
    color = "background-color: rgb(255, 85, 127);";
    paint();
}

searchPanel::searchPanel(Ui::VEDA1Class* ui, UserData* inp, QWidget* parrent) : ui(ui), user(inp), QWidget(parrent) {
    type.setText(tr("  Пользователь  ")); //2
    type_ = 2;
    text_str = inp->getUserName();
    color = "background-color: rgb(101, 186, 49);";
    paint();
}

void searchPanel::paint() {
    type.setParent(this);
    text.setParent(this);
    panel.setParent(this);
    setLayout(&HLayout);
    panel.setStyleSheet(R"(
    QWidget:hover {
        background-color: rgba(255, 255, 255, 50);
    }
)");
    setMouseTracking(true);

    panel.setMinimumSize(QSize(327, 34));
    panel.setMaximumSize(QSize(327, 34));
    setMinimumSize(QSize(327, 34));
    setMaximumSize(QSize(327, 34));

    HLayout.setSpacing(6);
    HLayout.setContentsMargins(11, 11, 11, 11);

    sizePolicy.setHeightForWidth(type.sizePolicy().hasHeightForWidth());
    type.setSizePolicy(sizePolicy);
    type.setMinimumSize(QSize(0, 20));
    type.setStyleSheet(color + "\nborder-radius: 10px;");
    type.setLineWidth(4);
    type.setTextFormat(Qt::AutoText);
    type.setScaledContents(true);
    type.setWordWrap(false);

    HLayout.addWidget(&type);

    QFontMetrics metrics(text.font());
    QString elided = metrics.elidedText(text_str.remove('\n'), Qt::ElideRight, 210);
    text.setText(elided);

    text.setObjectName(QString::fromUtf8("label_14"));
    text.setMinimumSize(QSize(0, 20));
    text.setStyleSheet("background: transparent; color: white;");
    text.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    text.setWordWrap(false);

    HLayout.addWidget(&text);
}

void searchPanel::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        LOADING(ui)
        switch (type_) { //статья
        case 0: {
            ui->search_out->hide();

            ui->tabWidget->setCurrentIndex(0);

            QString id = article->objectName();
            QWidget* container = ui->scrollArea->widget();
            QWidget* articleWidget = container->findChild<QWidget*>(id);

            if (articleWidget)
                ui->scrollArea->ensureWidgetVisible(articleWidget, 0, 100);

        }
            break;
        case 1: {// эксп
            ui->search_out->hide();
            show_profile(ui);

            int row = 0;
            for (experiment item : MAIN_USER_POINTER->getExperiments()) {
                if (item.getId() == exp->getId()) break;
                row++;
            }

            CURRENT_EXP = row;
            showChart(ui);
            show_exp_data(ui);
            show_users(ui);
            validate(ui);
            break;
        }
        case 2: //пользователь
            ui->search_out->hide();
            modalUserInfo card(user, ui);
            card.goBig();
            break;
        }
        CLOSE_LOADING
    }
}