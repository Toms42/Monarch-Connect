#include "Node.hpp"

#include <QtCore/QObject>

#include <iostream>
#include <utility>

#include "FlowScene.hpp"

#include "NodeDataModel.hpp"
#include "NodeGraphicsObject.hpp"

#include "Connection.hpp"
#include "ConnectionGraphicsObject.hpp"
#include "ConnectionState.hpp"

using QtNodes::Connection;
using QtNodes::Node;
using QtNodes::NodeData;
using QtNodes::NodeDataModel;
using QtNodes::PortIndex;
using QtNodes::PortDirection;

Node::Node(std::unique_ptr<NodeDataModel>&& dataModel, QUuid const& id)
  : _uid(id)
  , _nodeDataModel(std::move(dataModel))
{
  // propagate data: model => node
  connect(_nodeDataModel.get(),
          &NodeDataModel::dataUpdated,
          this,
          &Node::onDataUpdated);

  _inConnections.resize(nodeDataModel()->nPorts(PortDirection::In));
  _outConnections.resize(nodeDataModel()->nPorts(PortDirection::Out));
}

Node::~Node() = default;

QJsonObject
Node::save() const
{
  QJsonObject nodeJson;

  nodeJson["id"] = id().toString();

  nodeJson["model"] = _nodeDataModel->save();

  QJsonObject obj;
  obj["x"] = _pos.x();
  obj["y"] = _pos.y();
  nodeJson["position"] = obj;

  return nodeJson;
}

void
Node::restore(QJsonObject const& json)
{

  //QJsonObject positionJson = json["position"].toObject();
  //QPointF point(positionJson["x"].toDouble(), positionJson["y"].toDouble());
  //setPosition(point);

  //_nodeDataModel->restore(json["model"].toObject());
}

QUuid
Node::id() const
{
  return _uid;
}

NodeDataModel*
Node::nodeDataModel() const
{
  return _nodeDataModel.get();
}

QPointF
Node::position() const
{
  return _pos;
}

void
Node::setPosition(QPointF const& newPos)
{
  _pos = newPos;

  emit positionChanged(newPos);
}

std::vector<Connection*> const&
Node::connections(PortDirection pType, PortIndex idx) const
{
  Q_ASSERT(idx >= 0);
  Q_ASSERT(pType == PortDirection::In ? (size_t)idx < _inConnections.size()
                                 : (size_t)idx < _outConnections.size());

  return pType == PortDirection::In ? _inConnections[idx] : _outConnections[idx];
}

std::vector<Connection*>&
Node::connections(PortDirection pType, PortIndex idx)
{
  Q_ASSERT(idx >= 0);
  Q_ASSERT(pType == PortDirection::In ? (size_t)idx < _inConnections.size()
                                 : (size_t)idx < _outConnections.size());

  return pType == PortDirection::In ? _inConnections[idx] : _outConnections[idx];
}

void
Node::propagateData(std::shared_ptr<NodeData> nodeData,
                    PortIndex inPortIndex) const
{
  _nodeDataModel->setInData(nodeData, inPortIndex);
}

void
Node::onDataUpdated(PortIndex index)
{
  auto nodeData = _nodeDataModel->outData(index);
  auto& conns = connections(PortDirection::Out, index);

  for (auto const& c : conns)
    c->propagateData(nodeData);
}
