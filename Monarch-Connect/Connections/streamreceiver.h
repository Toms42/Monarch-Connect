#ifndef STREAM_H
#define STREAM_H

#include <QObject>
#include <QQueue>
#include "Connections/payload.h"
#include "Connections/connectionstats.h"
#include "Connections/streamsender.h"

class StreamReceiver : public QObject
{
    Q_OBJECT
public:
    explicit StreamReceiver(QObject *parent = nullptr);
    void setSender(std::shared_ptr<StreamSender> sender);
    void setPortIndex(int i);
    int getPortIndex();

signals:
    void dataReady(Payload payload);

public slots:
    void place(Payload payload);

private:
    std::shared_ptr<StreamSender> _sender;
    int _index;
};

#endif // STREAM_H
