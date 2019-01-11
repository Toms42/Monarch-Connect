#ifndef CONNECTIONSTATS_H
#define CONNECTIONSTATS_H

#include <QObject>
#include <QHash>
#include "Connections/payload.h"
#include <QTimer>
#include <QDebug>


class ConnectionStats : public QObject
{
    Q_OBJECT
public:
    enum connectionType { EVENT = 1, STREAM = 2};
    //this struct contains the stats for eventSender/streamSender
    //a streamSender would have a QVector of these
    //an eventSender has a QVector length 1 of these, and value doesn't matter
    struct statStruct{
        int totalSeen = 0;
        double itemsPerSec = 0.0; //totalSeen / totalTime
        double lastTime = 0.0;
        double totalTime = 0.0;
        Payload *value;
    };
    struct stats{
        ConnectionStats::connectionType _type;
        QHash<QUuid, statStruct> _tags;
    };
    explicit ConnectionStats(QObject *parent = nullptr, connectionType type = EVENT);
    stats getStats(){return _stats;}
    void incrTotalSeen(QUuid tag = "event"); //if a new event/payload is sent
    void updateLastValue(QUuid tag, Payload *p); //updates every time a new value sent
    void resetLastTime(QUuid tag = "event"); //sets creation_timer of tag's stats to 0

signals:

public slots:
    void updateTimes(); //updates for all statStructs lastTime, totalTime and itemsPerSec every second

private:
    connectionType _type;
    QObject *_parent;
    stats _stats;
    QTimer *timer; //track time
};

#endif // CONNECTIONSTATS_H
