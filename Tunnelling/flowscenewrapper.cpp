#include "flowscenewrapper.h"
#include "Common/project.h"
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QIODevice>
#include <QDebug>

FlowSceneWrapper::FlowSceneWrapper(FlowSceneWrapper *parent, QFile &file, QObject *parentObj)
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
        _parent->addChild(this);
    reload();
    connect(&_scene, &DataFlowScene::modified,
            this, &FlowSceneWrapper::sceneChanged);
}


FlowSceneWrapper::FlowSceneWrapper(FlowSceneWrapper *parent, QObject *parentObj)
    : QObject(parentObj),
      _scene(Project::getInstance().getModelRegistry()),
      _children(),
      _internalTunnels(),
      _externalTunnels()

{
    _parent = parent;
    _uniqueID = QUuid::createUuid();

    if(_parent)
        _parent->addChild(this);
}

FlowSceneWrapper::~FlowSceneWrapper()
{
    if(_parent)
        _parent->removeChild(this);
}

void FlowSceneWrapper::save()
{
    if(!(_file.exists() && _file.isWritable()))
    {
        QString fileName = QFileDialog::getSaveFileName(nullptr,
                                                        tr("Open Flow"),
                                                        QDir::homePath(),
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
        if(_file.exists())
        {
            //make sure user is ok w/ overwriting the file:
            QMessageBox confirmation;
            confirmation.setText(tr("File already exists!"));
            confirmation.setInformativeText(tr("Do you want to replace it?"));
            confirmation.setStandardButtons(QMessageBox::Cancel | QMessageBox::Save);
            confirmation.setDefaultButton(QMessageBox::Save);
            int response = confirmation.exec();
            if(response != QMessageBox::Save)
            {
                return;
            }
        }
    }

    if(_file.open(QIODevice::WriteOnly))
    {
        _file.write(_scene.saveToMemory());
        _name = QFileInfo(_file).fileName();
        _isSaved = true;
        qDebug() << "saved!";
        _file.close();
        emit(updated(this));
        emit(hierarchyChanged());
    }
    else {
        qDebug() << "could not open file";
    }
}
void FlowSceneWrapper::save(QFile &file)
{
    if(file.exists() && file.isWritable())
    {
        _file.setFileName(file.fileName());
    }
    save();
}

void FlowSceneWrapper::addChild(FlowSceneWrapper *wrapper)
{
    if(_children.contains(wrapper)) return;
    _children.append(wrapper);
    emit(hierarchyChanged());
}

void FlowSceneWrapper::removeChild(FlowSceneWrapper *wrapper)
{
    _children.removeAll(wrapper);
    emit(hierarchyChanged());
}

void FlowSceneWrapper::reload()
{
    if(!_file.exists() || !_file.isReadable())
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
    _scene.loadFromMemory(_file.readAll());
    _file.close();
    qDebug() << "loaded!";
    emit(updated(this));
    emit(hierarchyChanged());
}

void FlowSceneWrapper::sceneChanged()
{
    qDebug() << "scene was changed!";
    if(_isSaved)
    {
        _isSaved = false;
        _name.prepend('~');
    }
    if(!_blocking)
    {
        emit(updated(this));
    }
    emit(hierarchyChanged());
}

void FlowSceneWrapper::refresh(FlowSceneWrapper *newWrapper)
{
    if(*newWrapper == *this) return; //ignore self updates...

    qDebug() << "refreshing flowscene";
    _blocking = true;

    //reload scene:
    _scene.clearScene();
    _scene.loadFromMemory(newWrapper->_scene.saveToMemory());

    //reload name and saved status:
    _name = newWrapper->_name;
    _isSaved = newWrapper->_isSaved;

    _blocking = false;
}

FlowSceneWrapper *FlowSceneWrapper::parent() const
{
    return _parent;
}
QVector<FlowSceneWrapper*> &FlowSceneWrapper::children()
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






