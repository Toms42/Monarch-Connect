#include "project.h"

Project::Project(QObject *parent)
    : QObject(parent),
      _tags(new TagList(this)),
      _tunnels(new TunnelList(this)),
      _flows(new FlowList(this)),
      _path(QFileInfo())
{

}

Project::~Project()
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

TagList &Project::getTagList()
{
    return _tags;
}

TunnelList &Project::getTunnelList()
{
    return _tunnels;
}

FlowList &Project::getFlowList()
{
    return _flows;
}
