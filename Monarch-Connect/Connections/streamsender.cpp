#include "streamsender.h"
#include <nodes/NodeData>
#include <nodes/NodeDataModel>
#include <QDebug>

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
    qDebug() << "sending";
    emit(sent(payload));
}


