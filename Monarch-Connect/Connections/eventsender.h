#ifndef EVENTSENDER_H
#define EVENTSENDER_H

#include <QObject>
#include <nodes/NodeData>
#include "Connections/payload.h"
#include <nodes/NodeDataModel>
#include "Connections/connectionstats.h"

using QtNodes::NodeData;
using QtNodes::NodeDataType;

class EventSender : public QObject, public NodeData
{
    Q_OBJECT
public:
    NodeDataType
    type() const override
    { return NodeDataType {"Event", "Event"}; }

public:
    explicit EventSender(QObject *parent = nullptr);

    void send();
    ConnectionStats *getMetrics(){return &_stats;}

signals:
    void sent();
private:
    ConnectionStats _stats;
};

#endif // EVENTSENDER_H
