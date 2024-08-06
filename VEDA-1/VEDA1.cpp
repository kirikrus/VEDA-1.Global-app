#include "VEDA1.h"
#include "mainPage.h"

VEDA1::VEDA1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connections(&ui);
    mainPage(&ui);
}

VEDA1::~VEDA1()
{}
