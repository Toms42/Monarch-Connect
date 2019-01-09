#ifndef TAGTYPE_H
#define TAGTYPE_H

#include <QUuid>
#include <QVector>
#include <QString>

class TagType
{
public:
    explicit TagType(QString tag,
                     int nFields,
                     QVector<QString> &fieldNames,
                     QVector<double> &fieldScalars,
                     QVector<QString> &fieldUnits);
    explicit TagType(QString tag,
                     QString fieldName,
                     double fieldScalar,
                     QString fieldUnit);
    explicit TagType();
    int nFields() const;
    bool operator==(const TagType & other) const;
    QString getTag() const;
    QUuid getTagID() const;
    QString getFieldName(int field) const;
    QString getFieldUnit(int field) const;
    double getFieldScalar(int field) const;

    void setTag(QString name);
    void setFieldName(int field, QString name);
    void setFieldUnit(int field, QString unit);
    void setFieldScalar(int field, double scalar);
    void addField(QString fieldname, double scalar, QString unit);
    void removeField(int field);

private:
    QUuid _tagID;
    QString _tag;
    int _nFields;
    QVector<QString> _fieldNames;
    QVector<double> _fieldScalars;
    QVector<QString> _fieldUnits;
};

#endif // TAGTYPE_H
