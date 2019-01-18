#include "eventsender.h"
#include <nodes/NodeData>
#include <nodes/NodeDataModel>
#include <QDebug>

using QtNodes::PortDirection;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;

EventSender::EventSender(QObject *parent) : QObject(parent),
    _stats(this, ConnectionStats::EVENT)
{
}

void EventSender::send()
{
    //qDebug() << "sending event";
    emit(sent());
    //update _stats
    _stats.incrTotalSeen();
    _stats.resetLastTime();
}


