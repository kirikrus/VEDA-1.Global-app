#include "article.h"

article::article(Ui::VEDA1Class* ui, int id, int authorId, QString text, QString date, QLayout* parent)
				: ui(ui), id(id), text(text), date(date) {

    author = new UserData(authorId);

#pragma region print
    article_ = new QWidget();
    QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    sizePolicy.setHeightForWidth(article_->sizePolicy().hasHeightForWidth());
    article_->setSizePolicy(sizePolicy);
    article_->setMinimumSize(QSize(530, 200));
    article_->setMaximumSize(QSize(530, 9000));
    article_->setStyleSheet(QString::fromUtf8("background-color: #202325;\n"
        "border-radius: 35px"));
    gridLayout = new QGridLayout(article_);
    gridLayout->setSpacing(6);
    gridLayout->setContentsMargins(11, 11, 11, 11);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    gridLayout->setSizeConstraint(QLayout::SetMinimumSize);
    gridLayout->setHorizontalSpacing(10);
    gridLayout->setVerticalSpacing(20);
    gridLayout->setContentsMargins(20, 20, 20, 20);
    textEdit = new QTextEdit(article_);
    textEdit->setObjectName(QString::fromUtf8("textEdit"));
    sizePolicy.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
    textEdit->setSizePolicy(sizePolicy);
    textEdit->setSizeIncrement(QSize(0, 0));
    textEdit->setAcceptDrops(true);
    textEdit->setStyleSheet(QString::fromUtf8("border-radius: 0;\n"
        "color: rgb(255, 255, 255);\n"
        ""));
    textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    textEdit->setAutoFormatting(QTextEdit::AutoNone);
    textEdit->setTabChangesFocus(false);
    textEdit->setLineWrapMode(QTextEdit::WidgetWidth);
    textEdit->setReadOnly(true);
    textEdit->setOverwriteMode(true);

    gridLayout->addWidget(textEdit, 3, 0, 1, 2);

    ArticlephotoUser = new QFrame(article_);
    ArticlephotoUser->setObjectName(QString::fromUtf8("ArticlephotoUser"));
    ArticlephotoUser->setMinimumSize(QSize(71, 71));
    ArticlephotoUser->setMaximumSize(QSize(71, 71));
    ArticlephotoUser->setStyleSheet(QString::fromUtf8("background-color: #fff;\n"
        "border-radius: 35px"));
    ArticlephotoUser->setFrameShape(QFrame::StyledPanel);
    ArticlephotoUser->setFrameShadow(QFrame::Raised);
    label_24 = new QLabel(ArticlephotoUser);
    label_24->setObjectName(QString::fromUtf8("label_24"));
    label_24->setGeometry(QRect(11, 11, 50, 50));
    label_24->setPixmap(QPixmap(QString::fromUtf8(":/icons/icons/user.png")));
    label_24->setScaledContents(true);

    gridLayout->addWidget(ArticlephotoUser, 0, 0, 2, 1);

    frame_19 = new QFrame(article_);
    frame_19->setObjectName(QString::fromUtf8("frame_19"));
    frame_19->setFrameShape(QFrame::StyledPanel);
    frame_19->setFrameShadow(QFrame::Raised);
    gridLayout_2 = new QGridLayout(frame_19);
    gridLayout_2->setSpacing(6);
    gridLayout_2->setContentsMargins(11, 11, 11, 11);
    gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
    gridLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
    gridLayout_2->setHorizontalSpacing(10);
    gridLayout_2->setVerticalSpacing(0);
    label_58 = new QLabel(frame_19);
    label_58->setObjectName(QString::fromUtf8("label_58"));
    QFont font1;
    font1.setFamilies({ QString::fromUtf8("Inter V") });
    font1.setPointSize(16);
    font1.setBold(false);
    QFont font4;
    font4.setFamilies({ QString::fromUtf8("Inter V") });
    font4.setPointSize(12);
    font4.setBold(false);
    QFont font5;
    font5.setFamilies({ QString::fromUtf8("Inter V") });
    font5.setPointSize(10);
    font5.setBold(false);
    label_58->setFont(font1);
    label_58->setStyleSheet(QString::fromUtf8("color: #fff\n"
        ""));

    gridLayout_2->addWidget(label_58, 0, 0, 1, 1);

    label_59 = new QLabel(frame_19);
    label_59->setObjectName(QString::fromUtf8("label_59"));
    label_59->setMinimumSize(QSize(0, 0));
    label_59->setFont(font4);
    label_59->setStyleSheet(QString::fromUtf8("color: rgb(184, 184, 184);\n"
        "padding-top: 0.5px;"));
    label_59->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignTop);

    gridLayout_2->addWidget(label_59, 0, 1, 3, 1);

    label_60 = new QLabel(frame_19);
    label_60->setObjectName(QString::fromUtf8("label_60"));
    label_60->setFont(font5);
    label_60->setStyleSheet(QString::fromUtf8("color: rgb(212, 212, 212);"));

    gridLayout_2->addWidget(label_60, 1, 0, 1, 1);


    gridLayout->addWidget(frame_19, 0, 1, 1, 1);
#pragma endregion

    label_58->setText(author->getUserName());//автор имя
    label_60->setText(author->getEmail());//автор почта
    label_59->setText(date);//время
    textEdit->document()->setMarkdown(text);

    textEdit->document()->adjustSize();
    QSize documentSize = textEdit->document()->size().toSize();
    textEdit->setMinimumSize(documentSize.width(), documentSize.height());


    parent->addWidget(article_);
}
