#ifndef STREAMSENDER_H
#define STREAMSENDER_H

#include <QObject>
#include <nodes/NodeData>
#include "Connections/payload.h"
#include <nodes/NodeDataModel>

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

signals:
    void sent(Payload payload);
};

#endif // STREAMSENDER_H
