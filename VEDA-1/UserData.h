#include <qstring.h>
#include "HTTPclient.h"

class UserData : public QObject{
	Q_OBJECT

	QString name;
	quint32 id;

	HTTPclient* http;

public:
	UserData(quint32 id_);
	QString getUserName();
};

