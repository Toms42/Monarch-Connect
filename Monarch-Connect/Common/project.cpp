#include "project.h"
#include <memory>
#include <QFileDialog>
#include <QFileInfo>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

Project::Project(QObject *parent)
    : QObject(parent),
      _tags(this),
      _flows(this)
{
    _registry = std::make_shared<DataModelRegistry>();
}

QByteArray Project::saveToMemory()
{
    qDebug() << "saving monarch project...";
    QJsonObject projectJson;
    projectJson.insert("flows",_flows.save());
    QJsonDocument document(projectJson);
    return document.toJson();

}

void Project::loadFromMemory(QByteArray file)
{
    qDebug() << "loading monarch project...";
    QJsonObject const document = QJsonDocument::fromJson(file).object();
    _flows.load(document["flows"].toArray());
}

void Project::save()
{
    if(_file.exists())
    {
        if(_file.open(QIODevice::WriteOnly))
        {
            _file.write(saveToMemory());
            _file.close();
            _name = QFileInfo(_file).fileName();
            _isSaved = true;
            emit(nameUpdated(_name));
        }
    }
    else
    {
        saveAs();
    }
}

void Project::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(nullptr,
                                                    tr("Save Project"),
                                                    QDir::homePath(),
                                                    tr("Project Files").append("(*.monarch)"));
    if(!fileName.isEmpty())
    {
        if(!fileName.endsWith(".monarch", Qt::CaseInsensitive))
        {
            fileName += ".monarch";
        }
    }
    else {
        return;
    }
    _file.setFileName(fileName);
    if(_file.open(QIODevice::WriteOnly))
    {
        _file.write(saveToMemory());
        _file.close();
        _name = QFileInfo(_file).fileName();
        _isSaved = true;
        emit(nameUpdated(_name));
    }
}

void Project::open()
{
    QString fileName = QFileDialog::getOpenFileName(nullptr,
        tr("Open File"),
        QDir::homePath(),
        tr("Project Files").append("(*.monarch)").append(";;")
        .append(tr("Flow Files")).append("(*.flow)"));
    if(fileName.endsWith(".flow"))
    {
        //open flow file
        QFile file;
        file.setFileName(fileName);
        _flows.loadTopLevelFlowWrapper(file);
    }
    else if(fileName.endsWith(".monarch"))
    {
        //open monarch file
        QFile file;
        file.setFileName(fileName);
        if(!file.open(QIODevice::ReadOnly))
            return;
        _file.setFileName(fileName);
        loadFromMemory(file.readAll());
    }
}

TagList &Project::getTagList()
{
    return _tags;
}

FlowList &Project::getFlowList()
{
    return _flows;
}

std::shared_ptr<DataModelRegistry> Project::getModelRegistry()
{
    return _registry;
}
