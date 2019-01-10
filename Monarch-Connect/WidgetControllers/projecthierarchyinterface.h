#ifndef PROJECTHIERARCHYINTERFACE_H
#define PROJECTHIERARCHYINTERFACE_H

#include <QObject>
#include "Common/flowlist.h"
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "WidgetControllers/centraltabinterface.h"
#include "Common/project.h"


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

    void itemSelectionChanged();

    //show context menu: (from tree)
    void showMenu();


public slots:
    //update hierarchy: (from external sources)
    void addTopFlow();
    void loadTopFlow();
    void deleteTopFlow();
    void saveTopFlow();
    void saveTopFlowAs();

private:
    void reloadTree();
    FlowList &_flows;
    QTreeWidget &_tree;
    CentralTabInterface &_interface;
    QTreeWidgetItem *_selected = nullptr;

    enum Columns
    {
        NAME = 0,
        FILEPATH,
        _NUMCOLUMNS
    };

};

#endif // PROJECTHIERARCHYINTERFACE_H
