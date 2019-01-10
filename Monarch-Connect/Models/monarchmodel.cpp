#include "monarchmodel.h"

MonarchModel::MonarchModel()
    : _streamSenders(),
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

QJsonObject MonarchModel::save() const
{
    QJsonObject modelJson;

    modelJson["name"] = name();
    modelJson["data"] = saveData();
    return modelJson;
}

unsigned int MonarchModel::nPorts(PortDirection type) const
{
    if(type == PortDirection::In) return static_cast<unsigned int>(_inPortList.count());
    if(type == PortDirection::Out) return static_cast<unsigned int>(_outPortList.count());
    return 0;
}

NodeDataType MonarchModel::dataType(PortDirection type, PortIndex index) const
{
    if(type == PortDirection::In)
    {
        if(index >= _inPortList.count()) return NodeDataType{"error","error"};
        return typeFromEnum(_inPortList[index].type);
    }
    if(type == PortDirection::Out)
    {
        if(index >= _outPortList.count()) return NodeDataType{"error","error"};
        return typeFromEnum(_outPortList[index].type);
    }
    return NodeDataType{"error","error"};
}

std::shared_ptr<NodeData> MonarchModel::outData(PortIndex index)
{
    if(index >= _outPortList.count()) return nullptr;
    auto port = _outPortList[index];
    if(port.type == PortType::PAYLOAD)
    {
        return port.getDataCallback();
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
        port.dataReadyCallback(std::dynamic_pointer_cast<Payload>(data));

        //propagate all Payload outputs:
        for(int i = 0; i < _outPortList.count(); i++)
        {
            if(_outPortList[i].type == PortType::PAYLOAD)
            {
                emit(dataUpdated(i));
            }
        }
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
    //get sender:
    //QObject* obj = sender();
}

void MonarchModel::eventIn(Payload payload)
{

}

NodeDataType MonarchModel::typeFromEnum(PortType type) const
{
    switch(type)
    {
    case PortType::EVENT:   return EventSender().type();
    case PortType::STREAM:  return StreamSender().type();
    case PortType::PAYLOAD: return Payload().type();
    }
}

