#pragma once

#include "GLOBAL.h"
#include "article.h"

void searchPanelShow(Ui::VEDA1Class* ui, QRect rect, QVBoxLayout* order, QString text);

class searchPanel : public QWidget{
	Q_OBJECT

public:
	searchPanel(Ui::VEDA1Class* ui, article* inp, QWidget *parrent);
	searchPanel(Ui::VEDA1Class* ui, experiment* inp, QWidget* parrent);
	searchPanel(Ui::VEDA1Class* ui, UserData* inp, QWidget* parrent);

	void paint();

protected:
	void mousePressEvent(QMouseEvent* event) override;

private:
	Ui::VEDA1Class* ui;

	QLabel type;
	QLabel text;
	QString text_str;
	QString color;
	QHBoxLayout HLayout;
	QSizePolicy sizePolicy;
	QWidget panel;

	quint8 type_;
	UserData* user = nullptr;
	experiment* exp = nullptr;
	article* article = nullptr;
};

