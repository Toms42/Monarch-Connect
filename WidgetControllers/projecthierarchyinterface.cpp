#include "projecthierarchyinterface.h"
#include <QQueue>
#include <QHash>
#include <QDebug>

//TODO: subclass QTreeWidgetItem to include a pointer to the corresponding
// wrapper that it represents. read the description!
class FlowTreeItem:public QTreeWidgetItem{
public:
    //general constructor
    FlowTreeItem()
        : QTreeWidgetItem(QTreeWidgetItem::UserType){
        //call QTreeWidgetItem constructor with UserType (value is 1000) to denote a custom item
    }
    //constructor if the item has a parent
    FlowTreeItem(QTreeWidgetItem *parent)
        : QTreeWidgetItem(parent, QTreeWidgetItem::UserType){

    }
    FlowTreeItem(QTreeWidget *parent)
        : QTreeWidgetItem(parent, QTreeWidgetItem::UserType){

    }
    virtual void setFlowSceneWrapper(std::shared_ptr<FlowSceneWrapper> f){
        _flowscene = f;
    }

    virtual std::shared_ptr<FlowSceneWrapper> getFlowSceneWrapper(){
        return _flowscene;
    }
private:
    std::shared_ptr<FlowSceneWrapper> _flowscene;
};

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

//update flow list: (from tree)
void ProjectHierarchyInterface::itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    //NOTE: I didn't use column, so this seems sus
    FlowTreeItem *wrappedItem;
    std::shared_ptr<FlowSceneWrapper> wrapper;
    // get the corresponding wrapper from the treewidgetitem
    if(item->type() == QTreeWidgetItem::UserType){
        wrappedItem = static_cast<FlowTreeItem *>(item);
        wrapper = wrappedItem->getFlowSceneWrapper();
        // open it using the centraltabinterface's "addTab"
        _interface.addTab(wrapper.get());
    }
}

//cast a QVector<FlowSceneWrapper *> to QVector<std::shared_ptr<FlowSceneWrapper>>
//since current->children() returns QVector<FlowSceneWrapper *>
//and FlowList uses QVector<std::shared_ptr<FlowSceneWrapper>>
QVector<std::shared_ptr<FlowSceneWrapper>>
castVector(QVector<FlowSceneWrapper*> input){
    QVector<std::shared_ptr<FlowSceneWrapper>> output;

    for(auto i = input.begin(); i != input.end(); i++){
        std::shared_ptr<FlowSceneWrapper> si(*i);
        output.append(si);
    }
    return output;
}

//update display: (from flowlist)
void ProjectHierarchyInterface::hierarchyChanged()
{
    _tree.clear();
    //iterative BFS
    //keep track of the wrappers with a set
    QSet<QUuid> seen;
    QQueue<std::shared_ptr<FlowSceneWrapper>> queue;
    //root flows
    QVector<std::shared_ptr<FlowSceneWrapper>> root =
            _flows.getTopLevelWrappers();
    //neighbors of current wrapper
    QVector<std::shared_ptr<FlowSceneWrapper>> neighbors;
    //current wrapper being looked at in BFS
    std::shared_ptr<FlowSceneWrapper> current;
    std::shared_ptr<FlowSceneWrapper> child;
    //keep track of the parent item to each node
    //maps wrappers to their parent wrapper's TreeWidgetItem
    QHash<QUuid, FlowTreeItem *> parent;
    //subclassed treewidgetitem that will store the wrapper
    FlowTreeItem *item;
    //name and file from the wrapper for the item
    QString name;
    QString file;

    //search through all the root nodes and their trees
    for(auto i = root.begin(); i != root.end(); i++){
        //BFS
        current = (*i);
        if(!(current->isRoot())){
            qDebug() << "BFS ERROR: Top level wrapper has parent";
        }
        queue.enqueue(current);
        //search through the tree stemming from this root
        while(!queue.empty()){
            current = queue.dequeue();
            /*create treewidgetitem for the current wrapper
             *based on the parent item
             *provided it's not a root node*/
            if(current != (*i)){
                if(parent.find(current->getID()) == parent.end()){
                    qDebug() << "BFS ERROR: Can't find parent";
                }
                else{
                    item = new FlowTreeItem(parent.value(current->getID()));
                }
            }
            else{
                //parent of the root node is the tree
                item = new FlowTreeItem(&_tree);
            }
            //set name and file (i'm gonna assume col 0 is name, 1 is file for now)
            name = current->getName();
            file = current->getFile();
            item->setText(0, name);
            item->setText(1, file);
            //insert the current node into the seen set
            if(!seen.contains(current->getID())){
                seen.insert(current->getID());
            }
            neighbors = castVector(current->children());
            for(auto n = neighbors.begin(); n != neighbors.end(); n++){
                child = (*n);
                if(!seen.contains(child->getID())){
                    //visit child later
                    queue.enqueue(child);
                    //note the child's parent wrapper's item
                    parent.insert(child->getID(),item);
                }
            }

        }
    }

    //steps:
    //1) clear view
    //2) recursively traverse the FlowList, starting at each root
    //3) insert treewidgetitems into the tree for each wrapper
    //4) set name/filepath column of each widget
    //oof gotta do some tree traversal

}
