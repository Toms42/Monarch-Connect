#include "tagtype.h"
TagType::TagType(QObject *parent)
    :QObject (parent),
      _fieldNames(1),
      _fieldScalars(1),
      _fieldUnits(1)
{
    _fieldNames[0] = "default";
    _nFields = 1;
    _fieldUnits[0] = "units";
    _fieldScalars[0] = 1;
}

TagType::TagType(QString tag,
                 int nFields,
                 QVector<QString> &fieldNames,
                 QVector<double> &fieldScalars,
                 QVector<QString> &fieldUnits,
                 QObject *parent)
    :QObject (parent),
      _fieldNames(fieldNames),
      _fieldScalars(fieldScalars),
      _fieldUnits(fieldUnits)
{
    _tag = tag;
    _tagID = QUuid::createUuid();
    _nFields = nFields;
}
TagType::TagType(QString tag,
                 QString fieldName,
                 double fieldScalar,
                 QString fieldUnit,
                 QObject *parent)
    :QObject (parent),
      _fieldNames(1),
      _fieldScalars(1),
      _fieldUnits(1)

{
    _tag = tag;
    _tagID = QUuid::createUuid();
    _nFields = 1;
    _fieldNames[0] = fieldName;
    _fieldScalars[0] = fieldScalar;
    _fieldUnits[0] = fieldUnit;

}
/*
TagType::TagType(const TagType &tag)
{
    _tagID = tag._tagID;
    _tag = tag._tag;
    _nFields = tag._nFields;
    _fieldNames = tag._fieldNames;
    _fieldScalars = tag._fieldScalars;
    _fieldUnits = tag._fieldUnits;
}
*/
bool TagType::operator==(const TagType &other) const
{
    return _tagID == other._tagID;
}
/*
TagType &TagType::operator=(const TagType & t)
{
}

TagType::~TagType()
{
}*/
QString TagType::getTag()
{
    return _tag;
}
QString TagType::getTag() const
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
