#include <QString>
#include <qdatetime.h>

class experiment {
public:
    experiment(quint32 id, const QDate& date, const QString& material, quint32 processTypeId, const QString& processTypeName);

    quint32 getId() const;
    QDate getDate() const;
    QString getMaterial() const;
    quint32 getProcessTypeId() const;
    QString getProcessTypeName() const;

private:
    quint32 id;
    QDate date;
    QString material;
    quint32 processTypeId;
    QString processTypeName;
};
