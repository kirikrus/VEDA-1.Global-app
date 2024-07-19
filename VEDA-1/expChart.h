#include <qlineseries.h>
#include <QString>
#include <QObject>
#include <QEventLoop>
#include "HTTPclient.h"

class expChart : public QObject {
	Q_OBJECT

public:
	expChart(quint32 expId_, QObject* parent = nullptr);
	void initChart();
	QLineSeries* getSeries();

private slots:
	void onChartDataReceived(const QJsonObject& jsonResponse);
	void onError(const QString& errorString);

private:
	quint32 expId;
	QLineSeries series;

	HTTPclient* http;
	QEventLoop loop;
};

