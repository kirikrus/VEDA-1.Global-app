#include "VEDA1.h"

VEDA1::VEDA1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connections(&ui);
}

VEDA1::~VEDA1()
{}
