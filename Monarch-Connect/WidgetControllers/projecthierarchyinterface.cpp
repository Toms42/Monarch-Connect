#include "projecthierarchyinterface.h"
#include <QQueue>
#include <QHash>
#include <QDebug>
#include <QMenu>
#include <QFileDialog>

//TODO: subclass QTreeWidgetItem to include a pointer to the corresponding
// wrapper that it represents. read the description!
class FlowTreeItem : public QTreeWidgetItem{
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
    _tree.setColumnCount(Columns::_NUMCOLUMNS);

    connect(&_tree, &QTreeWidget::itemDoubleClicked,
            this, &ProjectHierarchyInterface::itemDoubleClicked);
    connect(&_flows, &FlowList::hierarchyUpdated,
            this, &ProjectHierarchyInterface::hierarchyChanged);
    connect(&_tree, &QTreeWidget::itemSelectionChanged,
            this, &ProjectHierarchyInterface::itemSelectionChanged);
    _tree.setContextMenuPolicy(Qt::CustomContextMenu); //on right click _tree emits ContextMenuRequested
    connect(&_tree,&QTreeWidget::customContextMenuRequested,
            this, &ProjectHierarchyInterface::showMenu);
    hierarchyChanged();
}

//show the context menu (from tree)
void ProjectHierarchyInterface::showMenu(){
    qDebug() << "showing menu";
    QMenu *_menu = new QMenu("Actions", &_tree);
    QAction *newFlowAction = new QAction("New Top Level Flow", _menu);
    QAction *delFlowAction = new QAction("Delete Selected Flow", _menu);
    QAction *saveSelAction = new QAction("Save Selected", _menu);
    QAction *saveSelAsAction = new QAction("Save Selected As...", _menu);
    QAction *saveProAction = new QAction("Save Project", _menu);
    QAction *saveProAsAction = new QAction("Save Project As...", _menu);
    connect(newFlowAction, &QAction::triggered, this, &ProjectHierarchyInterface::addTopFlow);
    connect(delFlowAction, &QAction::triggered, this, &ProjectHierarchyInterface::deleteTopFlow);
    connect(saveProAction, &QAction::triggered, &Project::getInstance(), &Project::save);
    connect(saveProAsAction, &QAction::triggered, &Project::getInstance(), &Project::saveAs);
    connect(saveSelAsAction, &QAction::triggered, this, &ProjectHierarchyInterface::saveTopFlowAs);
    connect(saveSelAction, &QAction::triggered, this, &ProjectHierarchyInterface::saveTopFlow);
    _menu->addAction(newFlowAction);
    _menu->addAction(delFlowAction);
    _menu->addAction(saveSelAction);
    _menu->addAction(saveSelAsAction);
    _menu->addAction(saveProAction);
    _menu->addAction(saveProAsAction);
    _menu->exec(QCursor::pos());
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
        if(wrapper)
            _interface.addTab(wrapper.get());
        else {
            qDebug() << "oops, no wrapper for clicked item!";
        }
    }
}

void ProjectHierarchyInterface::itemSelectionChanged()
{
    if(_tree.selectedItems().count() > 0)
    {
        _selected = _tree.selectedItems()[0];
    }
    else{
        _selected = nullptr;
    }
}

void ProjectHierarchyInterface::addTopFlow()
{
    _flows.newTopLevelFlowWrapper();
}

void ProjectHierarchyInterface::loadTopFlow()
{
    QString fileName = QFileDialog::getOpenFileName(nullptr,
                                                    tr("Open Flow"),
                                                    QDir::homePath(),
                                                    tr("Flow Files").append(" (*.flow)"));
    if(!fileName.endsWith(".flow"))
    {
        return;
    }
    QFile file;
    file.setFileName(fileName);

    _flows.loadTopLevelFlowWrapper(file);
}

void ProjectHierarchyInterface::deleteTopFlow()
{
    if(!_selected) return;
    if(!((static_cast<FlowTreeItem *>(_selected))->getFlowSceneWrapper()->isRoot())) return;
    if(_selected->type() == QTreeWidgetItem::UserType)
    {
        auto toDelete = static_cast<FlowTreeItem *>(_selected);
        _interface.removeTab(toDelete->getFlowSceneWrapper().get());
        _flows.deleteTopLevelFlowWrapper(toDelete->getFlowSceneWrapper().get());
        _selected = nullptr;
    }

}

void ProjectHierarchyInterface::saveTopFlow(){
    if(!_selected) return;
    if(_selected->type() == QTreeWidgetItem::UserType){
        (static_cast<FlowTreeItem *>(_selected)->getFlowSceneWrapper())->save();
    }
}

void ProjectHierarchyInterface::saveTopFlowAs(){
    if(!_selected) return;
    if(_selected->type() == QTreeWidgetItem::UserType){
        (static_cast<FlowTreeItem *>(_selected)->getFlowSceneWrapper())->saveAs();
    }
}



//update display: (from flowlist)
void ProjectHierarchyInterface::hierarchyChanged()
{
    qDebug() << "updating hierarchy";
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

    QHash<QUuid, FlowTreeItem *> inserted;
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
            if(!current->isRoot()){
                if(!inserted.contains(current->parent()->getID())){
                    qDebug() << "BFS ERROR: Can't find parent";
                }
                else{
                    auto parent = inserted.value(current->parent()->getID());
                    item = new FlowTreeItem(parent);
                    parent->addChild(item);
                    inserted.insert(current->getID(), item);
                }
            }
            else{
                //parent of the root node is the tree
                item = new FlowTreeItem(&_tree);
                _tree.addTopLevelItem(item);
                inserted.insert(current->getID(), item);
            }

            //set name and file
            item->setText(NAME, current->getName());
            item->setText(FILEPATH, current->getFile());
            item->setFlowSceneWrapper(current);

            //insert the current node into the seen set
            if(!seen.contains(current->getID())){
                seen.insert(current->getID());
            }
            neighbors = current->children();
            for(auto neighbor : neighbors){
                if(!seen.contains(neighbor->getID())){
                    //visit neighbor later
                    queue.enqueue(neighbor);
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
