#include "NodeGraphicsObject.hpp"

#include <cstdlib>
#include <iostream>

#include <QtWidgets/QGraphicsEffect>
#include <QtWidgets/QtWidgets>

#include "ConnectionGraphicsObject.hpp"
#include "ConnectionState.hpp"

#include "FlowScene.hpp"
#include "NodePainter.hpp"

#include "FlowSceneModel.hpp"
#include "NodeConnectionInteraction.hpp"
#include "NodeIndex.hpp"

#include "StyleCollection.hpp"

using QtNodes::ConnectionPolicy;
using QtNodes::FlowScene;
using QtNodes::Node;
using QtNodes::NodeDataType;
using QtNodes::NodeGeometry;
using QtNodes::NodeGraphicsObject;
using QtNodes::NodeIndex;
using QtNodes::NodeState;
using QtNodes::PortDirection;

NodeGraphicsObject::NodeGraphicsObject(FlowScene& scene, NodeIndex const& node)
  : _scene(scene)
  , _nodeIndex(node)
  , _geometry(node, *this)
  , _state(node)
  , _locked(false)
{
  _scene.addItem(this);

  setFlag(QGraphicsItem::ItemDoesntPropagateOpacityToChildren, true);
  setFlag(QGraphicsItem::ItemIsMovable, true);
  setFlag(QGraphicsItem::ItemIsFocusable, true);
  setFlag(QGraphicsItem::ItemIsSelectable, true);
  setFlag(QGraphicsItem::ItemSendsScenePositionChanges, true);

  setCacheMode(QGraphicsItem::DeviceCoordinateCache);

  auto const& nodeStyle = flowScene().model()->nodeStyle(index());

  {
    auto effect = new QGraphicsDropShadowEffect;
    effect->setOffset(4, 4);
    effect->setBlurRadius(20);
    effect->setColor(nodeStyle.ShadowColor);

    setGraphicsEffect(effect);
  }

  setOpacity(nodeStyle.Opacity);

  setAcceptHoverEvents(true);

  setZValue(0.);

  embedQWidget();

  // connect to the move signals
  auto onMoveSlot = [this] {
    // ask the model to move it
    if (!flowScene().model()->moveNode(index(), pos())) {
      // set the location back
      setPos(flowScene().model()->nodeLocation(index()));
      moveConnections();
    }
  };
  connect(this, &QGraphicsObject::xChanged, this, onMoveSlot);
  connect(this, &QGraphicsObject::yChanged, this, onMoveSlot);
}

NodeGraphicsObject::~NodeGraphicsObject()
{
  // TODO I think it is dangerous - user have to delete widget if he allocated
  // it
  //if (_proxyWidget) {
  //  delete _proxyWidget->widget();
  //}
  // TODO here can be problem, when item have a parent, then parent remove item
  // when it will be removed
  _scene.removeItem(this);
}

NodeIndex
NodeGraphicsObject::index() const
{
  return _nodeIndex;
}

FlowScene&
NodeGraphicsObject::flowScene()
{
  return _scene;
}

FlowScene const&
NodeGraphicsObject::flowScene() const
{
  return _scene;
}

NodeGeometry&
NodeGraphicsObject::geometry()
{
  return _geometry;
}

NodeGeometry const&
NodeGraphicsObject::geometry() const
{
  return _geometry;
}

NodeState&
NodeGraphicsObject::nodeState()
{
  return _state;
}

NodeState const&
NodeGraphicsObject::nodeState() const
{
  return _state;
}

void
NodeGraphicsObject::embedQWidget()
{
  if (auto w = flowScene().model()->nodeWidget(index())) {
    _proxyWidget = new QGraphicsProxyWidget(this);

    _proxyWidget->setWidget(w);

    _proxyWidget->setPreferredWidth(5);

    geometry().recalculateSize();

    _proxyWidget->setPos(geometry().widgetPosition());

    update();

    _proxyWidget->setOpacity(1.0);
    _proxyWidget->setFlag(QGraphicsItem::ItemIgnoresParentOpacity);
  }
}

QRectF
NodeGraphicsObject::boundingRect() const
{
  return geometry().boundingRect();
}

void
NodeGraphicsObject::moveConnections() const
{
  for (PortDirection portType : { PortDirection::In, PortDirection::Out }) {
    auto const& connectionEntries = nodeState().getEntries(portType);

    for (auto const& connections : connectionEntries) {
      for (auto& con : connections)
        con->move();
    }
  };
}

void
NodeGraphicsObject::reactToPossibleConnection(PortDirection reactingPortType,
                                              NodeDataType reactingDataType,
                                              QPointF const& scenePoint)
{
  QTransform const t = sceneTransform();

  QPointF p = t.inverted().map(scenePoint);

  geometry().setDraggingPosition(p);

  update();

  _state.setReaction(NodeState::REACTING, reactingPortType, reactingDataType);
}

void
NodeGraphicsObject::resetReactionToConnection()
{
  _state.setReaction(NodeState::NOT_REACTING);
  update();
}

void
NodeGraphicsObject::lock(bool locked)
{
  _locked = locked;
  setFlag(QGraphicsItem::ItemIsMovable, !locked);
  setFlag(QGraphicsItem::ItemIsFocusable, !locked);
  setFlag(QGraphicsItem::ItemIsSelectable, !locked);
}

void
NodeGraphicsObject::paint(QPainter* painter,
                          QStyleOptionGraphicsItem const* option,
                          QWidget*)
{
  painter->setClipRect(option->exposedRect);

  NodePainter::paint(painter, *this);
}

QVariant
NodeGraphicsObject::itemChange(GraphicsItemChange change, const QVariant& value)
{
  if (change == ItemPositionChange && scene()) {
    moveConnections();
  }

  return QGraphicsItem::itemChange(change, value);
}

void
NodeGraphicsObject::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
  if (_locked)
    return;

  // deselect all other items after this one is selected
  if (!isSelected() && !(event->modifiers() & Qt::ControlModifier)) {
    _scene.clearSelection();
  }

//  if(isSelected())
//  {
//      qDebug() << "selected";
//      emit(selectionUpdated());
//  }

  for (PortDirection portToCheck : { PortDirection::In, PortDirection::Out }) {
    // TODO do not pass sceneTransform
    PortIndex portIndex = geometry().checkHitScenePoint(
      portToCheck, event->scenePos(), sceneTransform());
    if (portIndex != INVALID) {
      std::vector<ConnectionGraphicsObject*> connections =
        nodeState().connections(portToCheck, portIndex);

      // start dragging existing connection
      if (!connections.empty() &&
          flowScene().model()->nodePortConnectionPolicy(
            index(), portIndex, portToCheck) == ConnectionPolicy::One) {
        Q_ASSERT(connections.size() == 1);

        auto con = *connections.begin();

        // start connecting anew, except start with the port that this
        // connection was already connected to
        Q_ASSERT(_scene._temporaryConn == nullptr);
        if (portToCheck == PortDirection::In) {
          _scene._temporaryConn =
            new ConnectionGraphicsObject(con->node(PortDirection::Out),
                                         con->portIndex(PortDirection::Out),
                                         NodeIndex{},
                                         INVALID,
                                         _scene);
          _scene._temporaryConn->geometry().setEndPoint(PortDirection::In,
                                                        event->scenePos());
        } else {
          _scene._temporaryConn =
            new ConnectionGraphicsObject(NodeIndex{},
                                         INVALID,
                                         con->node(PortDirection::In),
                                         con->portIndex(PortDirection::In),
                                         _scene);
          _scene._temporaryConn->geometry().setEndPoint(PortDirection::Out,
                                                        event->scenePos());
        }
        _scene._temporaryConn->grabMouse();

        // remove it
        flowScene().model()->removeConnection(con->node(PortDirection::Out),
                                              con->portIndex(PortDirection::Out),
                                              con->node(PortDirection::In),
                                              con->portIndex(PortDirection::In));

      } else // initialize new Connection
      {
        if (portToCheck == PortDirection::In) {
          Q_ASSERT(_scene._temporaryConn == nullptr);
          _scene._temporaryConn = new ConnectionGraphicsObject(
            NodeIndex{}, INVALID, _nodeIndex, portIndex, _scene);
          _scene._temporaryConn->geometry().setEndPoint(PortDirection::Out,
                                                        event->scenePos());
        } else {
          Q_ASSERT(_scene._temporaryConn == nullptr);
          _scene._temporaryConn = new ConnectionGraphicsObject(
            _nodeIndex, portIndex, NodeIndex{}, INVALID, _scene);
          _scene._temporaryConn->geometry().setEndPoint(PortDirection::In,
                                                        event->scenePos());
        }

        _scene._temporaryConn->grabMouse();
      }
    }
  }

  auto pos = event->pos();

  if (flowScene().model()->nodeResizable(index()) &&
      geometry().resizeRect().contains(QPoint(pos.x(), pos.y()))) {
    nodeState().setResizing(true);
  }
}

void
NodeGraphicsObject::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
  if (nodeState().resizing()) {
    auto diff = event->pos() - event->lastPos();

    if (auto w = flowScene().model()->nodeWidget(index())) {
      auto oldSize = w->size();

      oldSize += QSize(diff.x(), diff.y());

      w->setFixedSize(oldSize);

      // We have to recalculdate size before set widgetPosition in proxyWidget
      geometry().recalculateSize();

      _proxyWidget->setMinimumSize(oldSize);
      _proxyWidget->setMaximumSize(oldSize);
      _proxyWidget->setPos(geometry().widgetPosition());

      moveConnections();

      event->accept();
    }
  } else {
    QGraphicsObject::mouseMoveEvent(event);

    if (event->lastPos() != event->pos())
      moveConnections();

    event->ignore();
  }

  // TODO I think we have to set scene rect not here, but in view
  // QRectF r = scene()->sceneRect();
  // r = r.united(mapToScene(boundingRect()).boundingRect());
  // scene()->setSceneRect(r);
}

void
NodeGraphicsObject::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
  nodeState().setResizing(false);

  QGraphicsObject::mouseReleaseEvent(event);

  // position connections precisely after fast node move
  moveConnections();
}

void
NodeGraphicsObject::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
  // bring all the colliding nodes to background
  QList<QGraphicsItem*> overlapItems = collidingItems();

  for (QGraphicsItem* item : overlapItems) {
    if (item->zValue() > 0.0) {
      item->setZValue(0.0);
    }
  }
  // bring this node forward
  setZValue(1.0);

  geometry().setHovered(true);
  update();
  flowScene().model()->nodeHovered(index(), event->screenPos(), true);
  event->accept();
}

void
NodeGraphicsObject::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
  geometry().setHovered(false);
  update();
  flowScene().model()->nodeHovered(index(), event->screenPos(), false);
  event->accept();
}

void
NodeGraphicsObject::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
  auto pos = event->pos();

  if (flowScene().model()->nodeResizable(index()) &&
      geometry().resizeRect().contains(QPoint(pos.x(), pos.y()))) {
    setCursor(QCursor(Qt::SizeFDiagCursor));
  } else {
    setCursor(QCursor());
  }

  event->accept();
}

void
NodeGraphicsObject::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
  QGraphicsItem::mouseDoubleClickEvent(event);

  flowScene().model()->nodeDoubleClicked(index(), event->screenPos());
}

void
NodeGraphicsObject::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
  QGraphicsItem::contextMenuEvent(event);

  flowScene().model()->nodeContextMenu(index(), event->screenPos());
}
