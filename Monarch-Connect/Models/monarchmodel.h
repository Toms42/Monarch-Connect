#ifndef MONARCHMODEL_H
#define MONARCHMODEL_H

#include <nodes/NodeData>
#include <nodes/NodeDataModel>
#include <QObject>
#include "Connections/payload.h"
#include "Connections/streamsender.h"
#include "Connections/streamreceiver.h"
#include "Connections/eventsender.h"
#include "Connections/eventreceiver.h"

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

    struct MonarchInputPort{
        PortType type;
        std::function<void(std::shared_ptr<Payload>)> dataReadyCallback; //for all inputs
        //int payloadNumFields = 0; //0 means don't check. Filters all payloads through this port.
        int idx = -1; //internal use only: idx of corresponding receiver
    };
    struct MonarchOutputPort{
        PortType type;
        std::function<std::shared_ptr<Payload>(void)> getDataCallback; //for payload outputs
        //int payloadNumFields = 0; //0 means don't check. Filters all payloads through this port.
        int idx = -1; //internal use only: idx of corresponding sender
    };

public:
    MonarchModel();
    virtual ~MonarchModel() override;

/*
 * PURE VIRTUAL FUNCTIONS: you must override these when creating your node.
 */
public:
    //basic info about the node:
    virtual QString caption() const  override = 0;
    virtual QString name() const  override  = 0;
    QWidget *embeddedWidget() override = 0;

protected:
    //save your data in the node
    virtual QJsonObject saveData() const = 0;
    virtual QVector<MonarchInputPort> getInputPortArray()  const = 0;
    virtual QVector<MonarchOutputPort> getOutputPortArray()  const = 0;


/*
 * IMPLEMENTED FUNCTIONS: don't override these unless you know what you're doing.
 */
public:
    QJsonObject save() const override;
    unsigned int nPorts(PortDirection type) const override;
    NodeDataType dataType(PortDirection type, PortIndex index) const override;
    std::shared_ptr<NodeData> outData(PortIndex index) override;
    void setInData(std::shared_ptr<NodeData> data, PortIndex index) override;

private:
    NodeDataType typeFromEnum(PortType type) const;

private slots:
    void streamIn(Payload payload);
    void eventIn(Payload payload);

private:
    QVector<std::shared_ptr<StreamSender>> _streamSenders;
    QVector<std::shared_ptr<EventSender>> _eventSenders;
    QVector<std::shared_ptr<StreamReceiver>> _streamReceivers;
    QVector<std::shared_ptr<EventReceiver>> _eventReceivers;
    QVector<MonarchInputPort> _inPortList;
    QVector<MonarchOutputPort> _outPortList;

};

#endif // MONARCHMODEL_H
