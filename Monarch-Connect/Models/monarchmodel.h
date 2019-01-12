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
    Q_OBJECT

public:
    enum PortType{
        STREAM,
        EVENT,
        PAYLOAD
    };

protected:

    struct MonarchInputPort{
        PortType type;
        QString name;
        int idx = -1; //internal use only: idx of corresponding receiver
    };
    struct MonarchOutputPort{
        PortType type;
        QString name;
        int idx = -1; //internal use only: idx of corresponding sender
    };

public:
    MonarchModel()
        : NodeDataModel(),
          _streamSenders(),
          _eventSenders(),
          _streamReceivers(),
          _eventReceivers(),
          _inPortList(),
          _outPortList()
    {}
    virtual ~MonarchModel()  override  {}

/*
 * PURE VIRTUAL FUNCTIONS: you must override these when creating your node.
 */
public:
    //basic info about the node:
    virtual QString caption() const  override = 0;
    virtual QString name() const  override  = 0;
    virtual QWidget *embeddedWidget() override = 0;

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
    void sendOnStream(int index, Payload payload)
    {
        int senderIdx = _outPortList[index].idx;
        _streamSenders[senderIdx]->send(payload);
    }
    //send an event. Use for event outputs only.
    void triggerEvent(int index)
    {
        int senderIdx = _outPortList[index].idx;
        _eventSenders[senderIdx]->send();
    }

    //get the currently set input/output arrays. Only useful if you modified
    //the arrays after calling setup()
    const QVector<MonarchInputPort> inPortList() const {return _inPortList;}
    const QVector<MonarchOutputPort> outPortList() const {return _outPortList;}


/*
 * IMPLEMENTED FUNCTIONS: don't override these unless you know what you're doing.
 */
public:
    QJsonObject save() const override
    {
        QJsonObject modelJson;

        modelJson["name"] = name();
        modelJson["caption"] = caption();
        modelJson["data"] = saveData();
        return modelJson;
    }

    void restore(QJsonObject const& modelJson) override
    {
        loadData(modelJson["data"].toObject());
    }

    unsigned int nPorts(PortDirection type) const override
    {
        if(type == PortDirection::In) return static_cast<unsigned int>(_inPortList.count());
        if(type == PortDirection::Out) return static_cast<unsigned int>(_outPortList.count());
        return 0;
    }

    NodeDataType dataType(PortDirection type, PortIndex index) const override
    {
        if(type == PortDirection::In)
        {
            if(index >= _inPortList.count()) return NodeDataType{"error","error"};
            auto t = typeFromEnum(_inPortList[index].type);
            t.name = _inPortList[index].name;
            return t;
        }
        if(type == PortDirection::Out)
        {
            if(index >= _outPortList.count()) return NodeDataType{"error","error"};
            auto t = typeFromEnum(_outPortList[index].type);
            t.name = _outPortList[index].name;
            return t;
        }
        return NodeDataType{"error","error"};
    }

    std::shared_ptr<NodeData> outData(PortIndex index) override
    {
        if(index >= _outPortList.count()) return nullptr;
        auto port = _outPortList[index];
        if(port.type == PortType::PAYLOAD)
        {
            auto payload = std::make_shared<Payload>(getOutputData(index));
            return std::static_pointer_cast<NodeData>(payload);
        }
        else if(port.type == PortType::STREAM)
        {
            return _streamSenders[port.idx];
        }
        else if(port.type == PortType::EVENT)
        {
            return _eventSenders[port.idx];
        }
        else return nullptr;
    }

    void setInData(std::shared_ptr<NodeData> data, PortIndex index) override
    {
        if(index >= _inPortList.count()) return;
        auto port = _inPortList[index];
        if(port.type == PortType::PAYLOAD)
        {
            inputDataReady(*std::dynamic_pointer_cast<Payload>(data), index);
        }
        else if(port.type == PortType::STREAM)
        {
            _streamReceivers[port.idx]->setSender(std::dynamic_pointer_cast<StreamSender>(data));
        }
        else if(port.type == PortType::EVENT)
        {
            _eventReceivers[port.idx]->setSender(std::dynamic_pointer_cast<EventSender>(data));
        }
        else return;
    }

    void setup() //call this in your constructor to setup the base stuff
    {
        _inPortList.clear();
        _outPortList.clear();
        _streamSenders.clear();
        _streamReceivers.clear();
        _eventSenders.clear();
        _eventReceivers.clear();

        _inPortList = getInputPortArray();
        _outPortList = getOutputPortArray();


        int sri = 0;
        int eri = 0;
        for(int i = 0; i < _inPortList.count(); i++)
        {
            auto port = _inPortList[i];
            if(port.type == PortType::STREAM)
            {
                _streamReceivers.append(std::make_shared<StreamReceiver>());
                _streamReceivers[sri]->setPortIndex(i);
                connect(_streamReceivers[sri].get(), &StreamReceiver::dataReady,
                        this, &MonarchModel::streamIn);
                port.idx = sri;
                sri++;
            }
            if(port.type == PortType::EVENT)
            {
                _eventReceivers.append(std::make_shared<EventReceiver>());
                _eventReceivers[eri]->setPortIndex(i);
                connect(_eventReceivers[sri].get(), &EventReceiver::dataReady,
                        this, &MonarchModel::eventIn);
                port.idx = eri;
                eri++;
            }
        }

        int ssi = 0;
        int esi = 0;
        for(int i = 0; i < _outPortList.count(); i++)
        {
            auto port = _outPortList[i];
            if(port.type == PortType::STREAM)
            {
                _streamSenders.append(std::make_shared<StreamSender>());
                port.idx = ssi;
                ssi++;
            }
            if(port.type == PortType::EVENT)
            {
                _eventSenders.append(std::make_shared<EventSender>());
                port.idx = esi;
                esi++;
            }
        }
    }

public:
    NodeDataType typeFromEnum(PortType type) const
    {
        switch(type)
        {
        case PortType::EVENT:   return EventSender().type();
        case PortType::STREAM:  return StreamSender().type();
        case PortType::PAYLOAD: return Payload().type();
        }
        return NodeDataType{"error","error"};
    }

private slots:
    void streamIn(Payload payload)
    {
        auto *receiver = static_cast<StreamReceiver*>(sender());
        int portIdx = receiver->getPortIndex();
        inputDataReady(payload, portIdx);
    }
    void eventIn()
    {
        auto *receiver = static_cast<EventReceiver*>(sender());
        int portIdx = receiver->getPortIndex();
        Payload payload;
        inputDataReady(payload, portIdx);
    }

private:
    QVector<std::shared_ptr<StreamSender>> _streamSenders;
    QVector<std::shared_ptr<EventSender>> _eventSenders;
    QVector<std::shared_ptr<StreamReceiver>> _streamReceivers;
    QVector<std::shared_ptr<EventReceiver>> _eventReceivers;
    QVector<MonarchInputPort> _inPortList;
    QVector<MonarchOutputPort> _outPortList;

};

#endif // MONARCHMODEL_H
