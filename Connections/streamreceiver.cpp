#include "streamreceiver.h"
#include "Connections/streamsender.h"
#include <QDebug>

StreamReceiver::StreamReceiver(QObject *parent)
    : QObject(parent),
      _stats()
{

}
void StreamReceiver::setSender(std::shared_ptr<StreamSender> sender)
{
    qDebug() << "connected: " << sender.get();
    _sender = sender;
    connect(_sender.get(), &StreamSender::sent, this, &StreamReceiver::place);
}
void StreamReceiver::clearStats(void)
{

}

void StreamReceiver::place(Payload payload)
{
    qDebug() << "receiving";
    emit(dataReady(payload));
}
