#include "projecthierarchyinterface.h"

//TODO: subclass QTreeWidgetItem to include a pointer to the corresponding
// wrapper that it represents. read the description!

ProjectHierarchyInterface::ProjectHierarchyInterface(FlowList &flows,
                                                     QTreeWidget &tree,
                                                     CentralTabInterface &interface,
                                                     QObject *parent)
    :QObject (parent),
      _flows(flows),
      _tree(tree),
      _interface(interface)

{
    hierarchyChanged();
}

void ProjectHierarchyInterface::itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    // get the corresponding wrapper from the treewidgetitem
    // open it using the centraltabinterface's "addTab"
}

//update display: (from flowlist)
void ProjectHierarchyInterface::hierarchyChanged()
{
    //steps:
    //1) clear view
    //2) recursively traverse the FlowList, starting at each root
    //3) insert treewidgetitems into the tree for each wrapper
    //4) set name/filepath column of each widget
    //oof gotta do some tree traversal
}
