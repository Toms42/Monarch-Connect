#ifndef STATSWIDGETCONTROLLER_H
#define STATSWIDGETCONTROLLER_H

#include <QObject>
#include <QTreeWidget>
#include <QTreeView>
#include <QTreeWidgetItem>
#include "Connections/connectionstats.h"

class StatsWidgetController : public QObject{
    Q_OBJECT
public:
    explicit StatsWidgetController(QTreeWidget *tree, QObject *parent = nullptr);
public slots:
    void changeView(ConnectionStats::stats *stats);
private:
    QTreeWidget *_tree;
};

#endif // STATSWIDGETCONTROLLER_H
