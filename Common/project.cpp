#include "project.h"
#include <memory>

Project::Project(QObject *parent)
    : QObject(parent),
      _tags(this),
      _flows(this),
      _path()
{
    _registry = std::make_shared<DataModelRegistry>();
}

void Project::save()
{
    if(_path.exists() && _path.isWritable())
    {
        //save
    }
    else
    {
        //prompt user for file
    }
}

void Project::save(QFile &path)
{
    _path.setFileName(path.fileName());
    save();
}

void Project::load(QFile &path)
{
    if(path.exists())
    {
        _path.setFileName(path.fileName());
        //load
    }
    else
    {
        //error
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
