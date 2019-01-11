#ifndef EVENTRECEIVER_H
#define EVENTRECEIVER_H

#include <QObject>
#include <QQueue>
#include "Connections/payload.h"
#include "Connections/connectionstats.h"
#include "Connections/eventsender.h"

class EventReceiver : public QObject
{
    Q_OBJECT
public:
    explicit EventReceiver(QObject *parent = nullptr);
    void setSender(std::shared_ptr<EventSender> sender);
    void setPortIndex(int i);
    int getPortIndex();

signals:
    void dataReady();

public slots:
    void place();

private:
    std::shared_ptr<EventSender> _sender;
    int _index;

};

#endif // EVENTRECEIVER_H
