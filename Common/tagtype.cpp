#include "tagtype.h"
TagType::TagType()
     :_fieldNames(1),
      _fieldScalars(1),
      _fieldUnits(1)
{
    _fieldNames[0] = "default";
    _nFields = 1;
    _fieldUnits[0] = "units";
    _fieldScalars[0] = 1;
    _tagID = QUuid::createUuid();
}

TagType::TagType(QString tag,
                 int nFields,
                 QVector<QString> &fieldNames,
                 QVector<double> &fieldScalars,
                 QVector<QString> &fieldUnits)
     :_fieldNames(fieldNames),
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
                 QString fieldUnit)
     :_fieldNames(1),
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
bool TagType::operator==(const TagType &other) const
{
    return _tagID == other._tagID;
}

int TagType::nFields() const
{
    return _nFields;
}

QString TagType::getTag() const
{
    return _tag;
}
QUuid TagType::getTagID() const
{
    return _tagID;
}
QString TagType::getFieldName(int field) const
{
    if(field >= _nFields || field < 0) return "Invalid Field";
    return _fieldNames[field];
}
QString TagType::getFieldUnit(int field) const
{
    if(field >= _nFields || field < 0) return "Invalid Field";
    return _fieldUnits[field];
}
double TagType::getFieldScalar(int field) const
{
    if(field >= _nFields || field < 0) return 1;
    return _fieldScalars[field];
}
void TagType::setTag(QString name)
{
    _tag = name;
    _tagID = QUuid::createUuid(); //new Uuid.
}
void TagType::setFieldName(int field, QString name)
{
    if(field >= _nFields || field < 0) return;
    _fieldNames[field] = name;
    _tagID = QUuid::createUuid(); //new Uuid.
}
void TagType::setFieldUnit(int field, QString unit)
{
    if(field >= _nFields || field < 0) return;
    _fieldUnits[field] = unit;
    _tagID = QUuid::createUuid(); //new Uuid.
}
void TagType::setFieldScalar(int field, double scalar)
{
    if(field >= _nFields || field < 0) return;
    _fieldScalars[field] = scalar;
    _tagID = QUuid::createUuid(); //new Uuid.
}
void TagType::addField(QString fieldName, double scalar, QString unit)
{
    _nFields++;
    _fieldNames.append(fieldName);
    _fieldScalars.append(scalar);
    _fieldUnits.append(unit);
    _tagID = QUuid::createUuid(); //new Uuid.
}
void TagType::removeField(int field)
{
    if(field >= _nFields || field < 0) return;
    if(_nFields < 2) return; //must always have >= 1 field.
    _nFields--;
    _fieldNames.remove(field);
    _fieldScalars.remove(field);
    _fieldUnits.remove(field);
    _tagID = QUuid::createUuid(); //new Uuid.
}
