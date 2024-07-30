#include "experiment.h"

experiment::experiment(quint32 id, QDate date, QString material, quint32 processTypeId, QString processTypeName, int authorId, QVector<int> membersId)
    : id(id), date(date), material(material), processTypeId(processTypeId), processTypeName(processTypeName), authorId(authorId), membersId(membersId) {
    processTypeColor.append(qRgb(65, 93, 138));
    processTypeColor.append(qRgb(160, 82, 45));
    processTypeColor.append(qRgb(34, 139, 34));
    processTypeColor.append(qRgb(94, 34, 140));
    processTypeColor.append(qRgb(140, 137, 34));
    processTypeColor.append(qRgb(161, 45, 53));
    processTypeColor.append(qRgb(65, 65, 65));
}

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

QRgb experiment::getProcessTypeColor(int id) const{return processTypeColor[id];}

void experiment::addMemberId(int id) { membersId.append(id); }


