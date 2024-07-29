#include "experiment.h"

experiment::experiment(quint32 id, QDate date, QString material, quint32 processTypeId, QString processTypeName, int authorId, QVector<int> membersId)
    : id(id), date(date), material(material), processTypeId(processTypeId), processTypeName(processTypeName), authorId(authorId), membersId(membersId) {}

quint32 experiment::getId() const {return id;}

QDate experiment::getDate() const {return date;}

QString experiment::getMaterial() const {return material;}

quint32 experiment::getProcessTypeId() const {return processTypeId;}

QString experiment::getProcessTypeName() const {return processTypeName;}

QLineSeries* experiment::getChart() {
    if (!chart) delete chart;
    chart = new expChart(id);
    return chart->getSeries();
}

expChart* experiment::getChartLink(){return chart;}

int experiment::getAuthorId() const{return authorId;}

QVector<int> experiment::getMembersId() const { return membersId; }


