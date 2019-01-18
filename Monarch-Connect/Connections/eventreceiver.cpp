#include "eventreceiver.h"
#include "Connections/eventsender.h"
#include <QDebug>

EventReceiver::EventReceiver(QObject *parent)
    : QObject(parent)
{

}
void EventReceiver::setSender(std::shared_ptr<EventSender> sender)
{
    //qDebug() << "connected: " << sender.get();
    if(_sender.get() != nullptr) //disconnect current sender if there is one
    {
        disconnect(_sender.get(), &EventSender::sent, this, &EventReceiver::place);
    }
    _sender = sender;
    if(sender.get() != nullptr) //connect new sender
    {
        connect(_sender.get(), &EventSender::sent, this, &EventReceiver::place);
    }
}
void EventReceiver::place()
{
    //qDebug() << "receiving";
    emit(dataReady());
}

void EventReceiver::setPortIndex(int i)
{
    _index = i;
}

int EventReceiver::getPortIndex()
{
    return _index;
}
