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
    if(_path.isFile() && _path.isWritable())
    {
        //save
    }
    else
    {
        //prompt user for file
    }
}

void Project::save(QFileInfo path)
{
    _path = path;
    this->save();
}

void Project::load(QFileInfo path)
{
    if(path.isFile() &&path.exists() && path.isReadable())
    {
        _path = path;
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
