#include "Connection.hpp"

#include <cmath>
#include <utility>

#include <QtGlobal>
#include <QtWidgets/QtWidgets>

#include "FlowScene.hpp"
#include "FlowView.hpp"
#include "Node.hpp"

#include "NodeDataModel.hpp"
#include "NodeGeometry.hpp"
#include "NodeGraphicsObject.hpp"

#include "ConnectionGeometry.hpp"
#include "ConnectionGraphicsObject.hpp"
#include "ConnectionState.hpp"

using QtNodes::Connection;
using QtNodes::ConnectionGeometry;
using QtNodes::ConnectionGraphicsObject;
using QtNodes::ConnectionID;
using QtNodes::ConnectionState;
using QtNodes::Node;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::PortIndex;
using QtNodes::PortDirection;
using QtNodes::TypeConverter;

Connection::Connection(Node& nodeIn,
                       PortIndex portIndexIn,
                       Node& nodeOut,
                       PortIndex portIndexOut,
                       TypeConverter typeConverter)
  : _uid(QUuid::createUuid())
  , _outNode(&nodeOut)
  , _inNode(&nodeIn)
  , _outPortIndex(portIndexOut)
  , _inPortIndex(portIndexIn)
  , _connectionState()
  , _converter(std::move(typeConverter))
{
  setNodeToPort(nodeIn, PortDirection::In, portIndexIn);
  setNodeToPort(nodeOut, PortDirection::Out, portIndexOut);
}

Connection::~Connection()
{
  // TODO when call destructor for connection objects, which recive this data,
  // already deleted

  // propagateEmptyData();
}

QJsonObject
Connection::save() const
{
  QJsonObject connectionJson;

  if (_inNode && _outNode) {
    connectionJson["in_id"] = _inNode->id().toString();
    connectionJson["in_index"] = _inPortIndex;

    connectionJson["out_id"] = _outNode->id().toString();
    connectionJson["out_index"] = _outPortIndex;

    if (_converter) {
      auto getTypeJson = [this](PortDirection type) {
        QJsonObject typeJson;
        NodeDataType nodeType = this->dataType(type);
        typeJson["id"] = nodeType.id;
        typeJson["name"] = nodeType.name;

        return typeJson;
      };

      QJsonObject converterTypeJson;

      converterTypeJson["in"] = getTypeJson(PortDirection::In);
      converterTypeJson["out"] = getTypeJson(PortDirection::Out);

      connectionJson["converter"] = converterTypeJson;
    }
  }

  return connectionJson;
}

ConnectionID
Connection::id() const
{
  ConnectionID ret;
  ret.lNodeID = getNode(PortDirection::Out)->id();
  ret.rNodeID = getNode(PortDirection::In)->id();

  ret.lPortID = getPortIndex(PortDirection::Out);
  ret.rPortID = getPortIndex(PortDirection::In);

  return ret;
}

void
Connection::setNodeToPort(Node& node, PortDirection portType, PortIndex portIndex)
{
  auto& nodeWeak = getNodePtrRef(portType);

  nodeWeak = &node;

  if (portType == PortDirection::Out)
    _outPortIndex = portIndex;
  else
    _inPortIndex = portIndex;

  _connectionState.setNoRequiredPort();

  updated(*this);
}

PortIndex
Connection::getPortIndex(PortDirection portType) const
{
  PortIndex result = INVALID;

  switch (portType) {
    case PortDirection::In:
      result = _inPortIndex;
      break;

    case PortDirection::Out:
      result = _outPortIndex;

      break;

    default:
      break;
  }

  return result;
}

Node*
Connection::getNode(PortDirection portType) const
{
  switch (portType) {
    case PortDirection::In:
      return _inNode;
      break;

    case PortDirection::Out:
      return _outNode;
      break;

    default:
      // not possible
      break;
  }
  Q_UNREACHABLE();
}

Node*&
Connection::getNodePtrRef(PortDirection portType)
{
  switch (portType) {
    case PortDirection::In:
      return _inNode;
      break;

    case PortDirection::Out:
      return _outNode;
      break;

    default:
      // not possible
      break;
  }
  Q_UNREACHABLE();
}

NodeDataType
Connection::dataType(PortDirection portType) const
{
  if (_inNode && _outNode) {
    auto const& model = (portType == PortDirection::In) ? _inNode->nodeDataModel()
                                                   : _outNode->nodeDataModel();
    PortIndex index = (portType == PortDirection::In) ? _inPortIndex : _outPortIndex;

    return model->dataType(portType, index);
  } else {
    Node* validNode;
    PortIndex index = INVALID;

    if ((validNode = _inNode)) {
      index = _inPortIndex;
      portType = PortDirection::In;
    } else if ((validNode = _outNode)) {
      index = _outPortIndex;
      portType = PortDirection::Out;
    }

    if (validNode) {
      auto const& model = validNode->nodeDataModel();

      return model->dataType(portType, index);
    }
  }

  Q_UNREACHABLE();
}

void
Connection::setTypeConverter(TypeConverter converter)
{
  _converter = std::move(converter);
}

void
Connection::propagateData(std::shared_ptr<NodeData> nodeData) const
{
  if (_inNode) {
    if (_converter) {
      nodeData = _converter(nodeData);
    }

    _inNode->propagateData(nodeData, _inPortIndex);
  }
}

void
Connection::propagateEmptyData() const
{
  std::shared_ptr<NodeData> emptyData;

  propagateData(emptyData);
}
