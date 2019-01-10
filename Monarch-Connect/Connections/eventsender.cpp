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

EventSender::EventSender(QObject *parent) : QObject(parent)
{
}

void EventSender::send()
{
    qDebug() << "sending event";
    emit(sent());
}


