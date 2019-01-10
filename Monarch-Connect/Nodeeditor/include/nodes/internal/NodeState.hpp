#pragma once

#include <unordered_map>
#include <vector>

#include <QtCore/QUuid>

#include "Export.hpp"

#include "NodeData.hpp"
#include "PortType.hpp"
#include "memory.hpp"

namespace QtNodes {

class NodeIndex;
class ConnectionGraphicsObject;

/// Contains vectors of connected input and output connections.
/// Stores bool for reacting on hovering connections
class NODE_EDITOR_PUBLIC NodeState
{

public:
  enum ReactToConnectionState
  {
    REACTING,
    NOT_REACTING
  };

public:
  explicit NodeState(NodeIndex const& index);

public:
  using ConnectionPtrVec = std::vector<ConnectionGraphicsObject*>;

  /// Returns vector of connections ID.
  /// Some of them can be empty (null)
  std::vector<ConnectionPtrVec> const& getEntries(PortDirection) const;

  std::vector<ConnectionPtrVec>& getEntries(PortDirection);

  ConnectionPtrVec connections(PortDirection portType, PortIndex portIndex) const;

  void setConnection(PortDirection portType,
                     PortIndex portIndex,
                     ConnectionGraphicsObject& connection);

  void eraseConnection(PortDirection portType,
                       PortIndex portIndex,
                       ConnectionGraphicsObject& connection);

  ReactToConnectionState reaction() const;

  PortDirection reactingPortType() const;

  NodeDataType reactingDataType() const;

  void setReaction(ReactToConnectionState reaction,
                   PortDirection reactingPortType = PortDirection::None,

                   NodeDataType reactingDataType = NodeDataType());

  bool isReacting() const;

  void setResizing(bool resizing);

  bool resizing() const;

private:
  std::vector<ConnectionPtrVec> _inConnections;
  std::vector<ConnectionPtrVec> _outConnections;

  ReactToConnectionState _reaction;
  PortDirection _reactingPortType;
  NodeDataType _reactingDataType;

  bool _resizing;
};
}
