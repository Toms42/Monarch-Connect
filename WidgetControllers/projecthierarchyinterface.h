#ifndef PROJECTHIERARCHYINTERFACE_H
#define PROJECTHIERARCHYINTERFACE_H

#include <QObject>
#include "Common/flowlist.h"
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "WidgetControllers/centraltabinterface.h"


class ProjectHierarchyInterface : public QObject
{
    Q_OBJECT
public:
    explicit ProjectHierarchyInterface(FlowList &flows,
                                       QTreeWidget &tree,
                                       CentralTabInterface &interface,
                                       QObject *parent = nullptr);

signals:

private slots:
    //update flowlist: (from tree)
    void itemDoubleClicked(QTreeWidgetItem *item, int column);

    //update display: (from flowlist)
    void hierarchyChanged();


public slots:
    //update hierarchy: (from external sources)

private:
    void reloadTree();
    FlowList &_flows;
    QTreeWidget &_tree;
    CentralTabInterface &_interface;

    enum Columns
    {
        NAME = 0,
        FILEPATH,
        _NUMCOLUMNS
    };

};

#endif // PROJECTHIERARCHYINTERFACE_H
