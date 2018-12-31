#ifndef PAYLOAD_H
#define PAYLOAD_H

#include <QObject>
#include <QUuid>
#include <QVector>

class Payload : public QObject
{
    Q_OBJECT
public:
    Payload(QUuid tagID, int nFields, QVector<long> vals, QObject *parent = nullptr);
    Payload(QUuid tagID, long val, QObject *parent = nullptr);
    Payload(Payload &payload);

    QUuid getTagID();
    int nFields();

    QString getFieldName(int field);
    QString getFieldUnit(int field);
    double getFieldScalar(int field);

    long getValDirect(int field);

    double getVal(int field);

private:
    QUuid _tagID;
    int _nFields;
    QVector<long> _vals;
};

#endif // PAYLOAD_H
