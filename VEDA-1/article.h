#include <ui_VEDA1.h>
#include "GLOBAL.h"

class article : public QWidget {
	Q_OBJECT

public:
	article(Ui::VEDA1Class* ui, int id,int authorId,QString text, QString date, QLayout* parent);

protected:
	void mousePressEvent(QMouseEvent* event) override;

private:
	int id;
	UserData* author;
	QString text;
	QString date;
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

