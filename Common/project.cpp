#include "project.h"

Project::Project(QObject *parent)
    : QObject(parent),
      _tags(this),
      _tunnels(this),
      _flows(this),
      _path()
{

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

const TagList &Project::getTagList()
{
    return _tags;
}

const TunnelList &Project::getTunnelList()
{
    return _tunnels;
}

const FlowList &Project::getFlowList()
{
    return _flows;
}
