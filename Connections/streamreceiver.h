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
    void clearFifo(void);
    void clearStats(void);

signals:
    void dataReady(Payload payload);
    void fifoOverflow(void);
    void fifoCount(size_t size);
    void statsUpdated(ConnectionStats &stats);

public slots:
    void place(Payload);

private:
    QQueue<Payload> _fifo;
    ConnectionStats _stats;
    StreamSender *_sender;

};

#endif // STREAM_H
