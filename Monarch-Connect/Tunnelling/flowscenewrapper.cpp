#include "flowscenewrapper.h"
#include "Common/project.h"
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QIODevice>
#include <QDebug>
#include <nodes/Node>
#include <nodes/NodeDataModel>
#include "Common/project.h"
#include "Models/monarchmodel.h"

FlowSceneWrapper::FlowSceneWrapper(std::shared_ptr<FlowSceneWrapper> parent, QFile &file, QObject *parentObj)
    : QObject(parentObj),
      _scene(Project::getInstance().getModelRegistry()),
      _children(),
      _internalTunnels(),
      _externalTunnels()

{
    _file.setFileName(file.fileName());
    _parent = parent;
    _uniqueID = QUuid::createUuid();

    if(_parent)
        _parent->addChild(std::shared_ptr<FlowSceneWrapper>(this));

    reload();
    connect(&_scene, &DataFlowScene::modified,
            this, &FlowSceneWrapper::sceneChanged);
    connect(&_scene, &DataFlowScene::selectionChanged,
            this, &FlowSceneWrapper::selectionChanged);
    emit(updated(this));
    emit(hierarchyChanged());
    qDebug() << "FlowSceneWrapper loaded";
}


FlowSceneWrapper::FlowSceneWrapper(std::shared_ptr<FlowSceneWrapper> parent, QObject *parentObj)
    : QObject(parentObj),
      _scene(Project::getInstance().getModelRegistry()),
      _children(),
      _internalTunnels(),
      _externalTunnels()

{
    _parent = parent;
    _uniqueID = QUuid::createUuid();

    if(_parent)
        _parent->addChild(std::shared_ptr<FlowSceneWrapper>(this));
    connect(&_scene, &DataFlowScene::modified,
            this, &FlowSceneWrapper::sceneChanged);
    connect(&_scene, &DataFlowScene::selectionChanged,
            this, &FlowSceneWrapper::selectionChanged);
    emit(updated(this));
    emit(hierarchyChanged());
    qDebug() << "New FlowSceneWrapper created";
}

FlowSceneWrapper::~FlowSceneWrapper()
{
    qDebug() << "deleting flowSceneWrapper at " << _file.fileName();
    if(_parent)
        _parent->removeChild(std::shared_ptr<FlowSceneWrapper>(this));
    //TODO: unsafe due to recursive deletion. But was it necessary at all?
    Project::getInstance().getFlowList().unregisterFlowWrapper(this);
    _scene.clearScene();
}

void FlowSceneWrapper::save()
{
    if(!_file.exists())
    {
        saveAs();
    }

    if(_file.open(QIODevice::WriteOnly))
    {
        _file.write(_scene.saveToMemory());
        _file.close();
        _name = QFileInfo(_file).fileName();
        _isSaved = true;
        qDebug() << "saved!";
        emit(updated(this));
        emit(hierarchyChanged());
    }
    else {
        qDebug() << "could not open file";
    }
}
void FlowSceneWrapper::saveAs()
{
    qDebug() << "no file yet, prompting.";
    QString fileName = QFileDialog::getSaveFileName(nullptr,
                                                    tr("Save Flow"),
                                                    Project::getInstance().getDir().path(),
                                                    tr("Flow Files").append("(*.flow)"));
    if(!fileName.isEmpty())
    {
        if(!fileName.endsWith(".flow", Qt::CaseInsensitive))
        {
            fileName += ".flow";
        }
    }
    else {
        return;
    }

    _file.setFileName(fileName);
    Project::getInstance().getFlowList().registerFlowWrapper(this);
    if(_file.open(QIODevice::WriteOnly))
    {
        _file.write(_scene.saveToMemory());
        _file.close();
        _name = QFileInfo(_file).fileName();
        _isSaved = true;
        qDebug() << "saved!";
        emit(updated(this));
        emit(hierarchyChanged());
    }
}

void FlowSceneWrapper::addChild(std::shared_ptr<FlowSceneWrapper> wrapper)
{
    for(auto child : _children)
    {
        if(*child == *wrapper) return;
    }
    _children.append(wrapper);
    emit(hierarchyChanged());
}

void FlowSceneWrapper::removeChild(std::shared_ptr<FlowSceneWrapper> wrapper)
{
    for(int i = 0; i < _children.size(); i++)
    {
        if(*_children[i] == *wrapper)
        {
            _children.remove(i);
            i--;
        }
    }
    emit(hierarchyChanged());
}

void FlowSceneWrapper::reload()
{
    qDebug() << "loading from file: " << _file.fileName();
    if(!_file.exists())
    {
        qDebug() << "reloading when no file exists";
        return;
    }
    _scene.clearScene();
    if(!_file.open(QIODevice::ReadOnly))
    {
        qDebug() << "could not open file";
        return;
    }
    _name = QFileInfo(_file).fileName();
    _scene.loadFromMemory(_file.readAll());
    _file.close();
    _isSaved = true;
    qDebug() << "loaded!";
    emit(hierarchyChanged());
}

void FlowSceneWrapper::sceneChanged()
{
    if(_isSaved)
    {
        qDebug() << "no longer saved!";
        _isSaved = false;
        _name.prepend('~');
        emit(hierarchyChanged());
    }
}

void FlowSceneWrapper::selectionChanged()
{
    qDebug() << "selection was changed!";
    std::vector<Node*> nsel = _scene.selectedNodes();
    std::vector<ConnectionID> csel = _scene.selectedConnections();

    if(nsel.size() == 0 && csel.size() == 0)
    {
        Project::getInstance().newConfigWidget(nullptr);
        Project::getInstance().newConnectionStats(nullptr);
        _stats = nullptr;
    }

    if(nsel.size() != 0)
    {
        QWidget *widg =nsel[0]->nodeDataModel()->configWidget();
        Project::getInstance().newConfigWidget(widg);
    }
    if(csel.size() != 0)
    {
        QUuid sourceID = csel[0].lNodeID;
        Node* source = _scene.nodes().at(sourceID).get();
        auto *model = dynamic_cast<MonarchModel*>(source->nodeDataModel());
        if(model)
        {
            _stats = model->getStats(csel[0].lPortID);
            connect(_stats, &ConnectionStats::updated,
                    this, &FlowSceneWrapper::sendStats);
            Project::getInstance().newConnectionStats(_stats->getStats());
        }
    }
}

void FlowSceneWrapper::sendStats()
{
    if(!_stats) return;
    Project::getInstance().newConnectionStats(_stats->getStats());
}

void FlowSceneWrapper::refresh(FlowSceneWrapper *newWrapper)
{
    if(*newWrapper == *this)
    {
        qDebug() << "ignoring self-refresh";
        return; //ignore self updates...
    }

    qDebug() << "refreshing flowscene";

    //reload scene:
    _scene.clearScene();
    _scene.loadFromMemory(newWrapper->_scene.saveToMemory());

    //reload name and saved status:
    _name = newWrapper->_name;
    _isSaved = newWrapper->_isSaved;
}

std::shared_ptr<FlowSceneWrapper> FlowSceneWrapper::parent() const
{
    return _parent;
}
QVector<std::shared_ptr<FlowSceneWrapper>> &FlowSceneWrapper::children()
{
    return _children;
}

const TunnelList &FlowSceneWrapper::getExternalTunnels() const
{
    return _externalTunnels;
}
DataFlowScene *FlowSceneWrapper::getFlowScene()
{
    return &_scene;
}

QString FlowSceneWrapper::getFile() const
{
    return _file.fileName();
}


