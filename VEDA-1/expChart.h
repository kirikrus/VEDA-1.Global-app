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
	int getPointId(int num) const;
	QString getParamUnit() const;

private slots:
	void onChartDataReceived(const QJsonObject& jsonResponse);
	void onError(const QString& errorString);

private:
	quint32 expId;
	QLineSeries series;
	QVector<int> points_id;
	QString param_unit;

	HTTPclient* http;
	QEventLoop loop;
};

