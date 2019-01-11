#include "streamreceiver.h"
#include "Connections/streamsender.h"
#include <QDebug>

StreamReceiver::StreamReceiver(QObject *parent)
    : QObject(parent)
{

}
void StreamReceiver::setSender(std::shared_ptr<StreamSender> sender)
{
    qDebug() << "connected: " << sender.get();
    if(_sender.get() != nullptr) //disconnect current sender if there is one
    {
        disconnect(_sender.get(), &StreamSender::sent, this, &StreamReceiver::place);
    }
    _sender = sender;
    if(sender.get() != nullptr) //connect new sender
    {
        connect(_sender.get(), &StreamSender::sent, this, &StreamReceiver::place);
    }
}

void StreamReceiver::place(Payload payload)
{
    qDebug() << "receiving";
    emit(dataReady(payload));
}

void StreamReceiver::setPortIndex(int i)
{
    _index = i;
}

int StreamReceiver::getPortIndex()
{
    return _index;
}
