#ifndef TAGTYPE_H
#define TAGTYPE_H

#include <QObject>
#include <QUuid>
#include <QVector>
#include <QString>

class TagType : public QObject
{
    Q_OBJECT
public:
    explicit TagType(QString tag,
                     int nFields,
                     QVector<QString> &fieldNames,
                     QVector<double> &fieldScalars,
                     QVector<QString> &fieldUnits,
                     QObject *parent = nullptr);
    explicit TagType(QString tag,
                     QString fieldName,
                     double fieldScalar,
                     QString fieldUnit,
                     QObject *parent = nullptr);
    ~TagType();
    QString getTag();
    QUuid getTagID();
    QString getFieldName(int field);
    QString getFieldUnit(int field);
    double getFieldScalar(int field);


signals:

public slots:

private:
    QUuid _tagID;
    QString _tag;
    int _nFields;
    QVector<QString> _fieldNames;
    QVector<double> _fieldScalars;
    QVector<QString> _fieldUnits;
};

#endif // TAGTYPE_H
