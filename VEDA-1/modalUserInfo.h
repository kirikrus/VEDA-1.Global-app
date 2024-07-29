#include "GLOBAL.h"
#include <QWidget>
#include <qlabel.h>
#include <qlayout.h>
#include <ui_VEDA1.h>

class modalUserInfo : public QWidget {
	Q_OBJECT

public:
	modalUserInfo(UserData* user_, Ui::VEDA1Class* ui, QWidget* parent = nullptr);

	~modalUserInfo();

protected:
	void mousePressEvent(QMouseEvent* event) override;

private:
	Ui::VEDA1Class* ui;

	UserData* user;
	QLabel name;
	QLabel ava;
	QLabel status;
	QWidget panel;

	void goBig();
};

