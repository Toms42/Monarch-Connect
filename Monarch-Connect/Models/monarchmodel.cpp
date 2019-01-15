#include "monarchmodel.h"

MonarchModel::MonarchModel()
    : NodeDataModel(),
      _streamSenders(),
      _eventSenders(),
      _streamReceivers(),
      _eventReceivers(),
      _inPortList(),
      _outPortList()
{
}

MonarchModel::~MonarchModel()
{
}

void MonarchModel::setup()
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
        auto *port = &_inPortList[i];
        if(port->type == PortType::STREAM)
        {
            _streamReceivers.append(std::make_shared<StreamReceiver>());
            _streamReceivers[sri]->setPortIndex(i);
            port->idx = sri;
            connect(_streamReceivers[sri].get(), &StreamReceiver::dataReady,
                    this, &MonarchModel::streamIn);
            sri++;
        }
        if(port->type == PortType::EVENT)
        {
            _eventReceivers.append(std::make_shared<EventReceiver>());
            _eventReceivers[eri]->setPortIndex(i);
            port->idx = eri;
            connect(_eventReceivers[sri].get(), &EventReceiver::dataReady,
                    this, &MonarchModel::eventIn);
            eri++;
        }
    }

    int ssi = 0;
    int esi = 0;
    for(int i = 0; i < _outPortList.count(); i++)
    {
        auto *port = &_outPortList[i];
        if(port->type == PortType::STREAM)
        {
            _streamSenders.append(std::make_shared<StreamSender>());
            port->idx = ssi;
            ssi++;
        }
        if(port->type == PortType::EVENT)
        {
            _eventSenders.append(std::make_shared<EventSender>());
            port->idx = esi;
            esi++;
        }
    }
    //qDebug() << "added ports:";
    //nPorts(PortDirection::In);
    //qDebug() << "setup done";
}

QJsonObject MonarchModel::save() const
{
    QJsonObject modelJson;

    modelJson["name"] = name();
    modelJson["caption"] = caption();
    modelJson["data"] = saveData();
    return modelJson;
}
void MonarchModel::restore(QJsonObject const& modelJson)
{
    loadData(modelJson["data"].toObject());
}

unsigned int MonarchModel::nPorts(PortDirection type) const
{
    //qDebug() << "nPorts: " << _inPortList.count() << ", " << _outPortList.count();
    if(type == PortDirection::In) return static_cast<unsigned int>(_inPortList.count());
    if(type == PortDirection::Out) return static_cast<unsigned int>(_outPortList.count());
    return 0;
}

NodeDataType MonarchModel::dataType(PortDirection type, PortIndex index) const
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

std::shared_ptr<NodeData> MonarchModel::outData(PortIndex index)
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

void MonarchModel::setInData(std::shared_ptr<NodeData> data, PortIndex index)
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

void MonarchModel::streamIn(Payload payload)
{
    auto *receiver = static_cast<StreamReceiver*>(sender());
    int portIdx = receiver->getPortIndex();
    inputDataReady(payload, portIdx);
}

void MonarchModel::eventIn()
{
    auto *receiver = static_cast<EventReceiver*>(sender());
    int portIdx = receiver->getPortIndex();
    Payload payload;
    inputDataReady(payload, portIdx);
}

void MonarchModel::triggerEvent(int index)
{
    int senderIdx = _outPortList[index].idx;
    _eventSenders[senderIdx]->send();
}

void MonarchModel::sendOnStream(int index, Payload payload)
{
    int senderIdx = _outPortList[index].idx;
    _streamSenders[senderIdx]->send(payload);
}

NodeDataType MonarchModel::typeFromEnum(PortType type) const
{
    switch(type)
    {
    case PortType::EVENT:   return EventSender().type();
    case PortType::STREAM:  return StreamSender().type();
    case PortType::PAYLOAD: return Payload().type();
    }
    return NodeDataType{"error","error"};
}

ConnectionStats::stats *MonarchModel::getStats(PortIndex i)
{
    if(i < 0 || i >= _outPortList.count()) return nullptr;
    if(_outPortList[i].type == STREAM)
    {
        return _streamSenders[_outPortList[i].idx]->getMetrics();
    }
    else if(_outPortList[i].type == EVENT)
    {
        return _eventSenders[_outPortList[i].idx]->getMetrics();
    }
}

