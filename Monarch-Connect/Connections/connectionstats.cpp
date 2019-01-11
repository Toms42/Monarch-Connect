#include "Connections/connectionstats.h"
#define CLOCK_REFRESH_MS 100 //clock refresh rate for

ConnectionStats::ConnectionStats(QObject *parent, connectionType type) : QObject(parent),
    _type(type), _parent(parent), _stats(stats{type, QHash<QString, statStruct>()}) //hash the string translation of TagType to statStruct for StreamSender
{
    //if this is tracking events then initialize only one struct for all events
    if(_type == EVENT){
        _stats._tags.insert("event", statStruct{});
    }
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &ConnectionStats::updateTimes);
    timer->start(CLOCK_REFRESH_MS); //call updateTimes() every CLOCK_REFRESH_MS milliseconds
}


void ConnectionStats::updateTimes(){
    //qDebug() << "Updating items per second";
    QList<QString> keys = _stats._tags.keys();
    //loop through all structs and update all
    for(auto k = keys.begin(); k != keys.end(); k++){
        auto &it = _stats._tags[*k];
        it.lastTime += static_cast<double>(CLOCK_REFRESH_MS)/1000.0;
        it.totalTime += static_cast<double>(CLOCK_REFRESH_MS)/1000.0;
        if(it.totalTime == 0.0){
            it.itemsPerSec = 0.0;
        }
        else{
            it.itemsPerSec = (static_cast<double>(it.totalSeen)) / it.totalTime;
        }
    }
}

void ConnectionStats::incrTotalSeen(std::shared_ptr<const TagType> tagtype){
    //convert tagtype to just the string tag because it's hashable
    QString tag;
    if(tagtype == nullptr) tag = "event"; //if it's a nullptr (default param) then it's an event
    else tag = tagtype->getTag();
    switch(_type){
    case EVENT:{
        _stats._tags["events"].totalSeen += 1;
        qDebug() << "Total events sent: " + QString::number(_stats._tags[tag].totalSeen);
        qDebug() << "Time since last send (before reset): " + QString::number(_stats._tags[tag].lastTime);
        qDebug() << "Average events per second: " + QString::number(_stats._tags[tag].itemsPerSec);
        break;
    }
    case STREAM:{
        //if tag isn't in hashtable then initialize
        if(_stats._tags.find(tag) == _stats._tags.end()){
            _stats._tags.insert(tag,statStruct{});
        }
        _stats._tags[tag].totalSeen += 1;
        qDebug() << "---TAGTYPE " + tag + "---";
        qDebug() << "Total payloads sent for tag: " + QString::number(_stats._tags[tag].totalSeen);
        qDebug() << "Time since last send (before reset): " + QString::number(_stats._tags[tag].lastTime);
        qDebug() << "Average payloads per second: " + QString::number(_stats._tags[tag].itemsPerSec);
        break;
    }
    }
}

void ConnectionStats::resetLastTime(std::shared_ptr<const TagType> tagtype){
    //convert tagtype to just the string tag because it's hashable
    QString tag;
    if(tagtype == nullptr) tag = "event"; //if it's a nullptr (default param) then it's an event
    else tag = tagtype->getTag();
    //qDebug() << "Resetting time last seen sending";
    _stats._tags[tag].lastTime = 0.0;
}

//only used for streams, as events don't have values
void ConnectionStats::updateLastValue(std::shared_ptr<const TagType> tagtype, Payload *p){
    //convert tagtype to just the string tag because it's hashable
    QString tag = tagtype->getTag();
    //qDebug() << "Updating most recent value";
    _stats._tags[tag].value = p;
}


