#include "flowlist.h"

FlowList::FlowList(QObject *parent) : QObject(parent)
{

}

void FlowList::registerFlowWrapper(FlowSceneWrapper *wrapper)
{
    connect(wrapper, &FlowSceneWrapper::hierarchyChanged,
            this, &FlowList::hierarchyUpdated);

    auto key = wrapper->getFile();
    auto matches = _registry.value(key);
    for(auto match : matches)
    {
        if(*match == *wrapper)
        {
            matches.removeAll(match);
        }
    }
    matches.append(wrapper);
    for(auto match : matches)
    {
        //possible to create self loops,
        //but that's ok.
        connect(wrapper, &FlowSceneWrapper::updated,
                match, &FlowSceneWrapper::refresh);
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

void FlowList::loadTopLevelFlowWrapper(QFile file)
{
    auto newWrap = std::make_shared<FlowSceneWrapper>
            (static_cast<FlowSceneWrapper*>(nullptr),file,this);
    _topLevelWrappers.append(newWrap);
    registerFlowWrapper(newWrap.get());
}

void FlowList::newTopLevelFlowWrapper()
{
    auto newWrap = std::make_shared<FlowSceneWrapper>
            (static_cast<FlowSceneWrapper*>(nullptr),this);
    _topLevelWrappers.append(newWrap);
    connect(newWrap.get(), &FlowSceneWrapper::hierarchyChanged,
            this, &FlowList::hierarchyUpdated);
}
