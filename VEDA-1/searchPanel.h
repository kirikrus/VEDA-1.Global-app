#include <qwidget.h>
#include <ui_VEDA1.h>

class searchPanel : public QWidget{
	Q_OBJECT

public:
	searchPanel();

protected:
	void mousePressEvent(QMouseEvent* event) override;

private:
	Ui::VEDA1Class* ui;

	QLabel name;
	QLabel ava;
	QLabel status;
	QWidget panel;

	//void goBig();
};

