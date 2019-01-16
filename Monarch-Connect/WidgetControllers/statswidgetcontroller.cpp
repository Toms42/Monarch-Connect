#include "statswidgetcontroller.h"

StatsWidgetController::StatsWidgetController(QTreeWidget *tree, QObject *parent) :
    QObject(parent), _tree(tree)
{
}
/*
 *  GOTTA TEST THIS BY PUTTING TWO MONARCH MODELS AND TRYING TO
 *  SEND DATA ACROSS A STREAM A BUNCH OF TIMES
 */
void StatsWidgetController::changeView(ConnectionStats::stats *stats){
    if(stats == nullptr){
        qDebug() << "No stats sent to changeView";
        _tree->clear();
        QTreeWidgetItem *text = new QTreeWidgetItem(_tree);
        text->setText(0, "No stats available for this connection yet");
        _tree->insertTopLevelItem(0,text);
        return;
    }
    //clear current tree
    _tree->clear();
    QHash<QString, ConnectionStats::statStruct> tags = stats->_tags;
    QList<QString> keys = tags.keys();
    int counter = 0;
    //qDebug() << "Number of keys: " + QString::number(keys.length());
    for(auto key : keys){
        ConnectionStats::statStruct tagStats = tags[key];
        //qDebug() << "tag stats " + QString::number(tagStats.totalSeen);
        //add top level tree with the key name
        QTreeWidgetItem *text = new QTreeWidgetItem(_tree);
        text->setText(counter,key);
        //insert into parent tree
        _tree->insertTopLevelItem(counter, text);
        //then create children with each stat and insert into the key name tree
        QTreeWidgetItem *total = new QTreeWidgetItem(text);
        total->setText(0, "Total items seen: " + QString::number(tagStats.totalSeen));
        text->insertChild(0, total);
        QTreeWidgetItem *persec = new QTreeWidgetItem(text);
        persec->setText(0, "Items per second: " + QString::number(tagStats.itemsPerSec));
        text->insertChild(1, persec);
        QTreeWidgetItem *lasttime = new QTreeWidgetItem(text);
        lasttime->setText(0, "Time since last send: " + QString::number(tagStats.lastTime));
        text->insertChild(2, lasttime);
        text->setExpanded(true);
        _tree->insertTopLevelItem(counter, text);
        counter++;
    }
}
