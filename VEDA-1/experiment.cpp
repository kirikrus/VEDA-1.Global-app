#include "experiment.h"

experiment::experiment(quint32 id, const QDate& date, const QString& material, quint32 processTypeId, const QString& processTypeName)
    : id(id), date(date), material(material), processTypeId(processTypeId), processTypeName(processTypeName) {}

quint32 experiment::getId() const {return id;}

QDate experiment::getDate() const {return date;}

QString experiment::getMaterial() const {return material;}

quint32 experiment::getProcessTypeId() const {return processTypeId;}

QString experiment::getProcessTypeName() const {return processTypeName;}

QLineSeries* experiment::getChart() {
    if (!chart)
        chart = new expChart(id);
    else
        return chart->getSeries();
}


