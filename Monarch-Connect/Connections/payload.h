#ifndef PAYLOAD_H
#define PAYLOAD_H

#include <QUuid>
#include <QVector>
#include <nodes/NodeData>
#include <QDebug>

using QtNodes::NodeData;
using QtNodes::NodeDataType;

class Payload : public NodeData
{

public:
    Payload(QUuid tagID, int nFields, QVector<double> vals);
    Payload(QUuid tagID, double val);
    Payload();

public:
    NodeDataType
    type() const override
    { return NodeDataType {"Payload", "Payload"}; }

public:
    QUuid getTagID() const;
    int nFields() const;

    QString getFieldName(int field) const;
    QString getFieldUnit(int field) const;
    double getFieldScalar(int field) const;

    long getValDirect(int field) const;

    double getVal(int field) const;

    QString toString() const;

    friend QDebug operator<<(QDebug debug, const Payload &p);

private:
    QUuid _tagID;
    int _nFields;
    QVector<double> _vals;
};

#endif // PAYLOAD_H
