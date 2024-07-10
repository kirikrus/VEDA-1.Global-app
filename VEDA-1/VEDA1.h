#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_VEDA1.h"

class VEDA1 : public QMainWindow
{
    Q_OBJECT

public:
    VEDA1(QWidget *parent = nullptr);
    ~VEDA1();

private:
    Ui::VEDA1Class ui;
};
