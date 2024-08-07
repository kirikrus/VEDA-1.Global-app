#include "eyeAnimation.h"
#include "qrandom.h"
#include "qtimer.h"

EyeAnimation::EyeAnimation(Ui::VEDA1Class* ui, QWidget* parent) : QWidget(parent) {
    widget_3 = new QWidget(ui->centralWidget);
    widget_3->setGeometry(QRect(0, 0, 1051, 751));
    widget_3->show();

    frame_eye = new QFrame(widget_3);
    frame_eye->setGeometry(QRect(480, 355, 111, 56));
    frame_eye->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);"));
    frame_eye->setFrameShape(QFrame::StyledPanel);
    frame_eye->setFrameShadow(QFrame::Raised);
    frame_eye->show();

    eye = new QFrame(frame_eye);
    eye->setGeometry(QRect(35, 5, 40, 40));
    eye->setStyleSheet(QString::fromUtf8("background-color: rgb(163, 236, 90);\n"
        "border-radius: 20px;"));
    eye->setFrameShape(QFrame::StyledPanel);
    eye->setFrameShadow(QFrame::Raised);
    eye->show();

    label_23 = new QLabel(widget_3);
    label_23->setGeometry(QRect(468, 323, 131, 106));
    label_23->setPixmap(QPixmap(QString::fromUtf8(":/icons/icons/big_logo.png")));
    label_23->setScaledContents(true);
    label_31 = new QLabel(widget_3);
    label_31->setGeometry(QRect(435, 260, 221, 56));
    label_31->show();

    QFont font7;
    font7.setFamilies({ QString::fromUtf8("Inter V") });
    font7.setPointSize(30);
    font7.setBold(true);

    label_31->setFont(font7);
    label_31->setStyleSheet(QString::fromUtf8("color: rgb(163, 236, 90);"));
    label_23->raise();
    label_23->show();

    frame_eye->raise();
    label_31->raise();
    widget_3->raise();

    m_eye = eye;

    // Инициализация анимации перемещения
    m_animation = new QPropertyAnimation(eye, "geometry", this);
    m_animation->setDuration(500); // Длительность анимации в миллисекундах
    m_animation->setEasingCurve(QEasingCurve::InOutSine);

    // Таймер для смены позиции зрачка
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &EyeAnimation::moveEyeRandomly);
    timer->start(500); // Интервал времени для смены позиции зрачка
}

EyeAnimation::~EyeAnimation(){
    delete widget_3;
}

void EyeAnimation::moveEyeRandomly(){
    if (label_31->text() == "Загрузка")
        label_31->setText("Загрузка.");
    else if (label_31->text() == "Загрузка.")
        label_31->setText("Загрузка..");
    else if (label_31->text() == "Загрузка..")
        label_31->setText("Загрузка...");
    else 
        label_31->setText("Загрузка");

    if (!m_eye) return;

    // Получаем размер родительского виджета (например, глаза)
    QWidget* parentWidget = m_eye->parentWidget();
    if (!parentWidget) return;

    // Генерируем случайное положение для зрачка
    int maxX = parentWidget->width() - m_eye->width();
    int maxY = parentWidget->height() - m_eye->height();
    int newX = QRandomGenerator::global()->bounded(maxX);
    int newY = QRandomGenerator::global()->bounded(maxY);

    // Устанавливаем новое положение с анимацией
    QRect newGeometry(newX, newY, m_eye->width(), m_eye->height());
    m_animation->stop(); // Останавливаем текущую анимацию, если она идет
    m_animation->setStartValue(m_eye->geometry());
    m_animation->setEndValue(newGeometry);
    m_animation->start();
}