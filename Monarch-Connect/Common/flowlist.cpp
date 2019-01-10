#include "flowlist.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDir>
#include <QFileInfo>
#include "Common/project.h"

FlowList::FlowList(QObject *parent) : QObject(parent)
{

}

void FlowList::registerFlowWrapper(FlowSceneWrapper *wrapper)
{
    connect(wrapper, &FlowSceneWrapper::hierarchyChanged,
            this, &FlowList::hierarchyUpdated);

    auto key = wrapper->getFile();
    auto matches = _registry.value(key);
    qDebug() << "matches: " << matches;
    for(auto match : matches)
    {
        if(*match == *wrapper)
        {
            qDebug() << matches.removeAll(match) << "removed";
        }
    }
    matches.append(wrapper);
    _registry.insert(key, matches);
    qDebug() << "wrapper registered.";
    for(auto match : matches)
    {
        //possible to create self loops,
        //but that's ok.
        connect(wrapper, &FlowSceneWrapper::updated,
                match, &FlowSceneWrapper::refresh);
        connect(match, &FlowSceneWrapper::updated,
                wrapper, &FlowSceneWrapper::refresh);
    }
}

void FlowList::unregisterFlowWrapper(FlowSceneWrapper *wrapper)
{
    auto key = wrapper->getFile();
    auto matches = _registry.value(key);
    for(auto match : matches)
    {
        if(*match == *wrapper)
        {
            matches.removeAll(match);
        }
    }
    for(auto top : _topLevelWrappers)
    {
        if(*top == *wrapper)
        {
            _topLevelWrappers.removeAll(top);
        }
    }
}

void FlowList::loadTopLevelFlowWrapper(QFile &file)
{
    auto newWrap = std::make_shared<FlowSceneWrapper>
            (nullptr,file,this);
    _topLevelWrappers.append(newWrap);
    registerFlowWrapper(newWrap.get());
    emit(hierarchyUpdated());
}

void FlowList::newTopLevelFlowWrapper()
{
    auto newWrap = std::make_shared<FlowSceneWrapper>
            (nullptr,this);
    _topLevelWrappers.append(newWrap);
    connect(newWrap.get(), &FlowSceneWrapper::hierarchyChanged,
            this, &FlowList::hierarchyUpdated);
    emit(hierarchyUpdated());
}

//_topLevelWrappers getter to implement hierarchyChanged() in
//projectHierarchyInterface.cpp
QVector<std::shared_ptr<FlowSceneWrapper>> FlowList::getTopLevelWrappers(){
    return _topLevelWrappers;
}

QJsonArray FlowList::save()
{
    qDebug() << "saving flow list...";
    QJsonArray topLevelArray;
    for(auto wrap : _topLevelWrappers)
    {
        auto path = wrap->getFile();
        auto rel = Project::getInstance().getDir().relativeFilePath(path);
        qDebug() << "adding file: " << rel;
        QJsonValue jsonFilePath = rel;
        topLevelArray.append(jsonFilePath);
    }
    return topLevelArray;
}

void FlowList::load(QJsonArray topArray)
{
    _topLevelWrappers.clear();
    for(auto item : topArray)
    {
        auto fileName = item.toString();
        auto path = Project::getInstance().getDir().absoluteFilePath(fileName);
        QFile file;
        file.setFileName(path);
        loadTopLevelFlowWrapper(file);
    }
}
