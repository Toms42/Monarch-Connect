#include "payload.h"
#include "Common/project.h"

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
    return Project::getInstance().getTagList().getTagType(_tagID).getFieldName(field);
}
QString Payload::getFieldUnit(int field)
{
    return Project::getInstance().getTagList().getTagType(_tagID).getFieldUnit(field);
}
double Payload::getFieldScalar(int field)
{
    return Project::getInstance().getTagList().getTagType(_tagID).getFieldScalar(field);
}

long Payload::getValDirect(int field)
{
    if(field < 0 || field >= _nFields) return 0;
    return _vals[field];
}

double Payload::getVal(int field)
{
    if(field < 0 || field >= _nFields) return 0;
    return static_cast<double>(_vals[field])*getFieldScalar(field);
}
