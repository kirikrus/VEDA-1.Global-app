#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_VEDA1.h"

void connections(Ui::VEDA1Class*);

class VEDA1 : public QMainWindow
{
    Q_OBJECT

public:
    VEDA1(QWidget *parent = nullptr);
    ~VEDA1();
    Ui::VEDA1Class ui;
};
