#include "VEDA1.h"
#include <qevent.h>

VEDA1::VEDA1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.bt_ru, &QPushButton::clicked, this, &VEDA1::switchToRussian);
    connect(ui.bt_en, &QPushButton::clicked, this, &VEDA1::switchToEnglish);
    connect(ui.bt_ch, &QPushButton::clicked, this, &VEDA1::switchToChina);

    switchToRussian();
}

VEDA1::~VEDA1()
{}

void VEDA1::switchToRussian()
{
    if (currentLanguage == "ru")
        return;

    qApp->removeTranslator(&translator);
    bool loaded = translator.load("Translation_ru.qm");
    qDebug() << "Russian translation loaded:" << loaded;
    qApp->installTranslator(&translator);
    currentLanguage = "ru";
    retranslateUi();
}

void VEDA1::switchToEnglish()
{
    if (currentLanguage == "en")
        return;

    qApp->removeTranslator(&translator);
    bool loaded = translator.load("Translation_en.qm");
    qDebug() << "Russian translation loaded:" << loaded;
    qApp->installTranslator(&translator);
    currentLanguage = "en";
    retranslateUi();
}

void VEDA1::switchToChina()
{
    if (currentLanguage == "ch")
        return;

    qApp->removeTranslator(&translator);
    bool loaded = translator.load("Translation_zh.qm");
    qDebug() << "Russian translation loaded:" << loaded;
    qApp->installTranslator(&translator);
    currentLanguage = "ch";
    retranslateUi();
}

void VEDA1::retranslateUi()
{
    ui.retranslateUi(this);
}