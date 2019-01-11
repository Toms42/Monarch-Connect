#ifndef STREAMSENDER_H
#define STREAMSENDER_H

#include <QObject>
#include <nodes/NodeData>
#include "Connections/payload.h"
#include <nodes/NodeDataModel>
#include "Connections/connectionstats.h"

using QtNodes::NodeData;
using QtNodes::NodeDataType;

class StreamSender : public QObject, public NodeData
{
    Q_OBJECT
public:
    NodeDataType
    type() const override
    { return NodeDataType {"Stream", "Stream"}; }

public:
    explicit StreamSender(QObject *parent = nullptr);

    void send(Payload payload);
    ConnectionStats::stats getMetrics(){return _stats.getStats();}

signals:
    void sent(Payload payload);
private:
    ConnectionStats _stats;
};

#endif // STREAMSENDER_H
