#pragma once

#include <QString>
#include <qdatetime.h>
#include "expChart.h"

class experiment {
public:
    experiment(quint32 id, QDate date, QString material, quint32 processTypeId, QString processTypeName, int authorId, QVector<int> membersId, QString name);

    quint32 getId() const;
    QDate getDate() const;
    QString getMaterial() const;
    quint32 getProcessTypeId() const;
    QString getProcessTypeName() const;
    QLineSeries* getChart();
    expChart* getChartLink();
    int getAuthorId() const;
    QVector<int> getMembersId() const;
    QRgb getProcessTypeColor(int id) const;
    void addMemberId(int id);
    QString getName() const;

private:
    quint32 id;
    QString name;
    QDate date;
    QString material;
    quint32 processTypeId;
    QString processTypeName;
    QVector<QRgb> processTypeColor;

    int authorId;
    QVector<int> membersId;

    expChart* chart = nullptr;
};
