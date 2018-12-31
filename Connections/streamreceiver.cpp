#include "streamreceiver.h"
#include "Connections/streamsender.h"

StreamReceiver::StreamReceiver(QObject *parent)
    : QObject(parent),
      _stats(new ConnectionStats)
{

}
void StreamReceiver::setSender(std::shared_ptr<StreamSender> sender)
{
    connect(sender.get(), &StreamSender::sent, this, &StreamReceiver::place);
}
void StreamReceiver::clearStats(void)
{

}

void StreamReceiver::place(Payload payload)
{
    emit(dataReady(payload));
}
