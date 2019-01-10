#include "NodeState.hpp"

#include "FlowSceneModel.hpp"
#include "NodeDataModel.hpp"
#include "NodeIndex.hpp"
#include "QUuidStdHash.hpp"

#include "Connection.hpp"

using QtNodes::Connection;
using QtNodes::ConnectionGraphicsObject;
using QtNodes::NodeDataModel;
using QtNodes::NodeDataType;
using QtNodes::NodeIndex;
using QtNodes::NodeState;
using QtNodes::PortIndex;
using QtNodes::PortDirection;

NodeState::NodeState(NodeIndex const& index)
  : _inConnections(index.model()->nodePortCount(index, PortDirection::In))
  , _outConnections(index.model()->nodePortCount(index, PortDirection::Out))
  , _reaction(NOT_REACTING)
  , _reactingPortType(PortDirection::None)
  , _resizing(false)
{}

std::vector<NodeState::ConnectionPtrVec> const&
NodeState::getEntries(PortDirection portType) const
{
  if (portType == PortDirection::In)
    return _inConnections;
  else
    return _outConnections;
}

std::vector<NodeState::ConnectionPtrVec>&
NodeState::getEntries(PortDirection portType)
{
  if (portType == PortDirection::In)
    return _inConnections;
  else
    return _outConnections;
}

NodeState::ConnectionPtrVec
NodeState::connections(PortDirection portType, PortIndex portIndex) const
{
  auto const& connections = getEntries(portType);

  return connections[portIndex];
}

void
NodeState::setConnection(PortDirection portType,
                         PortIndex portIndex,
                         ConnectionGraphicsObject& connection)
{
  auto& connections = getEntries(portType);

  connections[portIndex].push_back(&connection);
}

void
NodeState::eraseConnection(PortDirection portType,
                           PortIndex portIndex,
                           ConnectionGraphicsObject& conn)
{
  auto& ptrSet = getEntries(portType)[portIndex];
  auto iter = std::find(ptrSet.begin(), ptrSet.end(), &conn);
  if (iter != ptrSet.end()) {
    ptrSet.erase(iter);
  }
}

NodeState::ReactToConnectionState
NodeState::reaction() const
{
  return _reaction;
}

PortDirection
NodeState::reactingPortType() const
{
  return _reactingPortType;
}

NodeDataType
NodeState::reactingDataType() const
{
  return _reactingDataType;
}

void
NodeState::setReaction(ReactToConnectionState reaction,
                       PortDirection reactingPortType,
                       NodeDataType reactingDataType)
{
  _reaction = reaction;

  _reactingPortType = reactingPortType;

  _reactingDataType = std::move(reactingDataType);
}

bool
NodeState::isReacting() const
{
  return _reaction == REACTING;
}

void
NodeState::setResizing(bool resizing)
{
  _resizing = resizing;
}

bool
NodeState::resizing() const
{
  return _resizing;
}
