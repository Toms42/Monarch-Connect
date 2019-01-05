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
    void clearStats(void);

signals:
    void dataReady(Payload payload);
    void statsUpdated(ConnectionStats &stats);

public slots:
    void place(Payload payload);

private:
    ConnectionStats _stats;
    std::shared_ptr<StreamSender> _sender;

};

#endif // STREAM_H
