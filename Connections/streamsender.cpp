#include "streamsender.h"
#include <nodes/NodeData>
#include <nodes/NodeDataModel>

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;

StreamSender::StreamSender(QObject *parent) : QObject(parent)
{
}

void StreamSender::send(Payload payload)
{
    emit(StreamSender::sent(payload));
}


