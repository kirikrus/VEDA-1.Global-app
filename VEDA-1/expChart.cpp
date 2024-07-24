#include "expChart.h"
#include <QDebug>
#include <QJsonArray>

struct PointWithId {
    QPointF point;
    int id;
};

expChart::expChart(quint32 expId_, QObject* parent) : QObject(parent), expId(expId_){
    http = new HTTPclient(this);

    QObject::connect(http, &HTTPclient::requestFinished, this, &expChart::onChartDataReceived);
    QObject::connect(http, &HTTPclient::requestError, this, &expChart::onError);

    initChart();
}

void expChart::initChart() {
    QString endpoint = QString("http://localhost:5011/Experiment/GetExperimentData/%1").arg(expId);
    http->get(endpoint);

    loop.exec();
}

QLineSeries* expChart::getSeries(){return &series;}

int expChart::getPointId(int num) const{
    if (points_id.size() == 0) return -1;
    return points_id[num];
}

QString expChart::getParamUnit() const{return param_unit;}

void expChart::onChartDataReceived(const QJsonObject& jsonResponse) {
    qDebug() << "Chart data received";
    QJsonArray experimentsArray = jsonResponse["DataOfExperiment"].toArray();


    for (const QJsonValue& value : experimentsArray) {
        QJsonObject experimentObject = value.toObject();
        double time = experimentObject["timepoint"].toDouble();
        double value = experimentObject["value"].toDouble();
        int id = experimentObject["id"].toInt();

        QJsonObject processTypeObject = experimentObject["parameter"].toObject();
        param_unit = processTypeObject["unit"].toString();

        points_id.append(id);
        series.append(time, value);
    }

    sortLineSeries();

    loop.quit();
}

void expChart::sortLineSeries() {
    QList<QPointF> points = series.points();

    std::vector<PointWithId> pointsWithIds;
    for (int i = 0; i < points.size(); ++i) pointsWithIds.push_back({ points[i], points_id[i] });

    std::sort(pointsWithIds.begin(), pointsWithIds.end(), [](const PointWithId& a, const PointWithId& b) {return a.point.x() < b.point.x();});

    // Очищаем серию и QVector, затем добавляем отсортированные значения
    series.clear();
    points_id.clear();
    for (const PointWithId& pointWithId : pointsWithIds) {
        series.append(pointWithId.point);
        points_id.append(pointWithId.id);
    }
}

void expChart::onError(const QString& errorString) {
    qDebug() << "Error received:" << errorString;

    loop.quit();
}
