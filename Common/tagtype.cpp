#include "tagtype.h"

TagType::TagType(QString tag,
                 int nFields,
                 QVector<QString> &fieldNames,
                 QVector<double> &fieldScalars,
                 QVector<QString> &fieldUnits,
                 QObject *parent)
    :QObject (parent)
{
    _tag = tag;
    _tagID = QUuid::createUuid();
    _nFields = nFields;
    _fieldNames = fieldNames;
    _fieldScalars = fieldScalars;
    _fieldUnits = fieldUnits;
}
TagType::TagType(QString tag,
                 QString fieldName,
                 double fieldScalar,
                 QString fieldUnit,
                 QObject *parent)
    :QObject (parent),
      _fieldNames(QVector<QString>(1)),
      _fieldScalars(QVector<double>(1)),
      _fieldUnits(QVector<QString>(1))

{
    _tag = tag;
    _tagID = QUuid::createUuid();
    _nFields = 1;
    _fieldNames[0] = fieldName;
    _fieldScalars[0] = fieldScalar;
    _fieldUnits[0] = fieldUnit;

}
TagType::~TagType()
{
}
QString TagType::getTag()
{
    return _tag;
}
QUuid TagType::getTagID()
{
    return _tagID;
}
QString TagType::getFieldName(int field)
{
    if(field >= _nFields || field < 0) return "Invalid Field";
    return _fieldNames[field];
}
QString TagType::getFieldUnit(int field)
{
    if(field >= _nFields || field < 0) return "Invalid Field";
    return _fieldUnits[field];
}
double TagType::getFieldScalar(int field)
{
    if(field >= _nFields || field < 0) return 1;
    return _fieldScalars[field];
}
