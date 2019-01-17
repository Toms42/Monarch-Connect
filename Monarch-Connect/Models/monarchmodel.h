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
#include "Connections/connectionstats.h"

using QtNodes::PortDirection;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;

//abstract class with some handy stuff for creating nodes for Monarch
class MonarchModel : public NodeDataModel
{
    Q_OBJECT

public:
    enum PortType{
        STREAM,
        EVENT,
        PAYLOAD
    };

protected:

    struct MonarchInputPort{
    public:
        PortType type;
        QString name;
        int idx; //internal use only: idx of corresponding receiver
    };
    struct MonarchOutputPort{
    public:
        PortType type;
        QString name;
        int idx; //internal use only: idx of corresponding sender
    };

public:
    MonarchModel();
    virtual ~MonarchModel()  override;

/*
 * PURE VIRTUAL FUNCTIONS: you must override these when creating your node.
 */
public:
    //basic info about the node:
    virtual QString caption() const  override = 0;
    virtual QString name() const  override  = 0;

    //widgets to display
    virtual QWidget *embeddedWidget() override = 0;
    virtual QWidget *configWidget() override = 0;

public:
    //load/save your internal data in the node, using json.
    virtual QJsonObject saveData() const = 0;
    virtual void loadData(QJsonObject const& modelJson) const = 0;

    //functions to access data in/out of the node.
    virtual void inputDataReady(Payload data, int index) = 0;
    virtual Payload getOutputData(int index) = 0;

    //get arrays of inputs/output ports. Called only on instantiation of node.
    virtual QVector<MonarchInputPort> getInputPortArray()  const = 0;
    virtual QVector<MonarchOutputPort> getOutputPortArray()  const = 0;


/*
 * IMPLEMENTED FUNCTIONS: use these to get stuff done
 */
protected:
    //send on a stream. Use for stream outputs only.
    void sendOnStream(int index, Payload payload);
    //send an event. Use for event outputs only.
    void triggerEvent(int index);

    //get the currently set input/output arrays. Only useful if you modified
    //the arrays after calling setup()
    const QVector<MonarchInputPort> inPortList() const {return _inPortList;}
    const QVector<MonarchOutputPort> outPortList() const {return _outPortList;}

/*
 * IMPLEMENTED FUNCTIONS: don't override these unless you know what you're doing.
 */
public:
    unsigned int nPorts(PortDirection type) const override;
    QJsonObject save() const override;
    void restore(QJsonObject const& modelJson) override;
    NodeDataType dataType(PortDirection type, PortIndex index) const override;
    std::shared_ptr<NodeData> outData(PortIndex index) override;
    void setInData(std::shared_ptr<NodeData> data, PortIndex index) override;
    void setup(); //call this in your constructor to setup the base stuff
    ConnectionStats *getStats(PortIndex i);

public:
    NodeDataType typeFromEnum(PortType type) const;

private slots:
    void streamIn(Payload payload);
    void eventIn();
    void updateAllPayloads();

private:
    QVector<std::shared_ptr<StreamSender>> _streamSenders;
    QVector<std::shared_ptr<EventSender>> _eventSenders;
    QVector<std::shared_ptr<StreamReceiver>> _streamReceivers;
    QVector<std::shared_ptr<EventReceiver>> _eventReceivers;
    QVector<MonarchInputPort> _inPortList;
    QVector<MonarchOutputPort> _outPortList;

};

#endif // MONARCHMODEL_H
