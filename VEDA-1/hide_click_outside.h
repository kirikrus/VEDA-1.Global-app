#pragma once
#include <qscrollarea.h>
class hide_click_outside : public QScrollArea{
public:
	hide_click_outside(QWidget* parent);
protected:
	bool eventFilter(QObject* obj, QEvent* event);
	void showEvent(QShowEvent* event);
	void hideEvent(QHideEvent* event);
};

