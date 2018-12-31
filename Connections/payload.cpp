#include "payload.h"


Payload::Payload(QUuid tagID, int nFields, QVector<long> vals, QObject *parent)
    : QObject (parent)
{
    _tagID = tagID;
    _nFields = nFields;
    _vals = vals;
}

Payload::Payload(QUuid tagID, long val, QObject *parent)
    :QObject (parent)
{
    _tagID = tagID;
    _nFields = 1;
    _vals = QVector<long>(1);
    _vals[0] = val;
}

Payload::Payload(Payload &payload)
{
    _tagID = payload._tagID;
    _nFields = payload._nFields;
    _vals = payload._vals;
}

QUuid Payload::getTagID()
{
    return _tagID;
}
int Payload::nFields()
{
    return _nFields;
}

QString Payload::getFieldName(int field)
{

}
QString Payload::getFieldUnit(int field)
{

}
double Payload::getFieldScalar(int field)
{

}

long Payload::getValDirect(int field)
{

}

double Payload::getVal(int field)
{

}
