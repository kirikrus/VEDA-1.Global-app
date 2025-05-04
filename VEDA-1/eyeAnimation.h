#pragma once

#include <QObject>
#include <QWidget>
#include "ui_VEDA1.h"
#include <qpropertyanimation.h>

class EyeAnimation : public QWidget {
    Q_OBJECT

public:
    EyeAnimation(Ui::VEDA1Class* ui,QWidget* parent = nullptr);
    
    ~EyeAnimation();

public slots:
    void moveEyeRandomly();

private:
    QFrame* m_eye;
    QPropertyAnimation* m_animation;

    QWidget* widget_3;
    QFrame* frame_eye;
    QFrame* eye;
    QLabel* label_23;
    QLabel* label_31;
};
