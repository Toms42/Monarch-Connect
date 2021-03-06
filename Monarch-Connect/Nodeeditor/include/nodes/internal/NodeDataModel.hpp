#pragma once

#include <QtWidgets/QWidget>

#include "Export.hpp"
#include "FlowSceneModel.hpp"
#include "NodeData.hpp"
#include "NodeGeometry.hpp"
#include "NodePainterDelegate.hpp"
#include "NodeStyle.hpp"
#include "PortType.hpp"
#include "Serializable.hpp"
#include "memory.hpp"

namespace QtNodes {

class StyleCollection;

class NODE_EDITOR_PUBLIC NodeDataModel
  : public QObject
  , public Serializable
{
  Q_OBJECT

public:
  NodeDataModel();

  virtual ~NodeDataModel() = default;

  /// Caption is used in GUI
  virtual QString caption() const = 0;

  /// It is possible to hide caption in GUI
  virtual bool captionVisible() const { return true; }

  /// Port caption is used in GUI to label individual ports
  virtual QString portCaption(PortDirection, PortIndex) const { return QString(); }

  /// It is possible to hide port caption in GUI
  virtual bool portCaptionVisible(PortDirection, PortIndex) const { return false; }

  /// Name makes this model unique
  virtual QString name() const = 0;

public:
  QJsonObject save() const override;
  void restore(QJsonObject const& /*p*/) override {}

public:
  virtual unsigned int nPorts(PortDirection portType) const = 0;

  virtual NodeDataType dataType(PortDirection portType,
                                PortIndex portIndex) const = 0;

public:
  virtual ConnectionPolicy portOutConnectionPolicy(PortIndex) const
  {
    return ConnectionPolicy::Many;
  }

  NodeStyle const& nodeStyle() const;

  void setNodeStyle(NodeStyle const& style);

public:
  /// Triggers the algorithm
  virtual void setInData(std::shared_ptr<NodeData> nodeData,
                         PortIndex port) = 0;

  virtual std::shared_ptr<NodeData> outData(PortIndex port) = 0;

  virtual QWidget* embeddedWidget() = 0;

  virtual QWidget* configWidget() = 0;

  virtual bool resizable() const { return false; }

  virtual NodeValidationState validationState() const
  {
    return NodeValidationState::Valid;
  }

  virtual QString validationMessage() const { return QString(""); }

  virtual NodePainterDelegate* painterDelegate() const { return nullptr; }

signals:

  void dataUpdated(PortIndex index);

  void dataInvalidated(PortIndex index);

  void computingStarted();

  void computingFinished();

private:
  NodeStyle _nodeStyle;
};
}
