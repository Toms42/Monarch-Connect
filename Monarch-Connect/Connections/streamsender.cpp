#include "streamsender.h"
#include <nodes/NodeData>
#include <nodes/NodeDataModel>
#include <QDebug>

using QtNodes::PortDirection;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;

StreamSender::StreamSender(QObject *parent) : QObject(parent),
    _stats(this, ConnectionStats::STREAM)
{
}

void StreamSender::send(Payload payload)
{
    qDebug() << "sending";
    emit(sent(payload));
    //seen one more, last time since seeing a payload sent is 0, last value is payload
    _stats.incrTotalSeen(payload.getTagID());
    _stats.resetLastTime(payload.getTagID());
    _stats.updateLastValue(payload.getTagID(), &payload);
}


