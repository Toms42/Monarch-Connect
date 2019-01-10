#pragma once

#include <QtCore/QUuid>

#include "PortType.hpp"

class QPointF;

namespace QtNodes {

class NodeGraphicsObject;

/// Stores currently draggind end.
/// Remembers last hovered Node.
class ConnectionState
{
public:
  ConnectionState(PortDirection port = PortDirection::None)
    : _requiredPort(port)
  {}

  ConnectionState(const ConnectionState&) = delete;
  ConnectionState operator=(const ConnectionState&) = delete;

  ~ConnectionState();

public:
  void setRequiredPort(PortDirection end) { _requiredPort = end; }

  PortDirection requiredPort() const { return _requiredPort; }

  bool requiresPort() const { return _requiredPort != PortDirection::None; }

  void setNoRequiredPort() { _requiredPort = PortDirection::None; }

public:
  void interactWithNode(NodeGraphicsObject* node);

  void setLastHoveredNode(NodeGraphicsObject* node);

  NodeGraphicsObject* lastHoveredNode() const { return _lastHoveredNode; }

  void resetLastHoveredNode();

private:
  PortDirection _requiredPort;

  NodeGraphicsObject* _lastHoveredNode{ nullptr };
};
}
