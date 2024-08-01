#include <ui_VEDA1.h>
#include "UserData.h"

class article : public QWidget {
	Q_OBJECT

public:
	article(Ui::VEDA1Class* ui, int id,int authorId,QString text, QDate date, QWidget* parent = nullptr);

private:
	int id;
	UserData* author;
	QString text;
	QDate date;
	Ui::VEDA1Class* ui;

	QWidget* article_;
	QGridLayout* gridLayout;
	QTextEdit* textEdit;
	QFrame* ArticlephotoUser;
	QLabel* label_24;
	QFrame* frame_19;
	QGridLayout* gridLayout_2;
	QLabel* label_58;
	QLabel* label_59;
	QLabel* label_60;
};

