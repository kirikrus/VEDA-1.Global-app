#include "UserData.h"
#include <QWidget>
#include <qlabel.h>
#include <qlayout.h>

class modalUserInfo : public QWidget {
	Q_OBJECT

public:
	modalUserInfo(UserData* user_, QWidget* parent = nullptr);

	~modalUserInfo();

private:
	UserData* user;
	QLabel name;
	QLabel ava;
	QLabel status;
	QWidget panel;

	void goBig();
};

