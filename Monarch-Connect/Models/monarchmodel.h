#ifndef MONARCHMODEL_H
#define MONARCHMODEL_H

#include <nodes/NodeData>
#include <nodes/NodeDataModel>
#include <QObject>
#include "Connections/payload.h"

using QtNodes::PortDirection;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;

//abstract class with some handy stuff for creating nodes for Monarch
class MonarchModel : public NodeDataModel
{
protected:
    enum PortType{
        STREAM,
        EVENT,
        PAYLOAD
    };

    struct MonarchPort{
        PortDirection direction;
        PortType type;
        std::function<void(Payload)> dataReadyCallback;
        int payloadNumFields = 0; //optional. 0 means don't check.
    };

public:
    MonarchModel();
    virtual ~MonarchModel() override;


public:
    //basic info about the node:
    virtual QString caption() const  override = 0;
    virtual QString name() const  override  = 0;

protected:
    //save your data in the node
    virtual QJsonObject saveData() const = 0;
    virtual QVector<MonarchPort> getPortArray()  const = 0;




public:
    //don't override these. They're implemented here.
    QJsonObject save() const override;
    unsigned int nPorts(PortDirection type) const override;
    NodeDataType dataType(PortDirection type, PortIndex index) const override;

};

#endif // MONARCHMODEL_H
