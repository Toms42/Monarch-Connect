#-------------------------------------------------
#
# Project created by QtCreator 2018-12-24T19:30:35
#
#-------------------------------------------------

QT       += core gui opengl network

# Compile with c++14 standard:
CONFIG += c++14 optimize_full

# let nodeeditor know it's being statically linked
DEFINES += NODE_EDITOR_STATIC

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Monarch-Connect
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


INCLUDEPATH += "$$PWD/Nodeeditor/include/nodes/internal" \
            "$$PWD/Nodeeditor/include"

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    Models/models.cpp \
    Models/monarchmodel.cpp \
    Models/printermodel.cpp \
    Connections/payload.cpp \
    Connections/connectionstats.cpp \
    Connections/streamreceiver.cpp \
    Connections/streamsender.cpp \
    Common/project.cpp \
    Common/taglist.cpp \
    Common/flowlist.cpp \
    Common/tagtype.cpp \
    Nodeeditor/src/Connection.cpp \
    Nodeeditor/src/ConnectionBlurEffect.cpp \
    Nodeeditor/src/ConnectionGeometry.cpp \
    Nodeeditor/src/ConnectionGraphicsObject.cpp \
    Nodeeditor/src/ConnectionPainter.cpp \
    Nodeeditor/src/ConnectionState.cpp \
    Nodeeditor/src/ConnectionStyle.cpp \
    Nodeeditor/src/DataFlowModel.cpp \
    Nodeeditor/src/DataFlowScene.cpp \
    Nodeeditor/src/DataModelRegistry.cpp \
    Nodeeditor/src/FlowScene.cpp \
    Nodeeditor/src/FlowSceneModel.cpp \
    Nodeeditor/src/FlowView.cpp \
    Nodeeditor/src/FlowViewStyle.cpp \
    Nodeeditor/src/Node.cpp \
    Nodeeditor/src/NodeConnectionInteraction.cpp \
    Nodeeditor/src/NodeDataModel.cpp \
    Nodeeditor/src/NodeGeometry.cpp \
    Nodeeditor/src/NodeGraphicsObject.cpp \
    Nodeeditor/src/NodePainter.cpp \
    Nodeeditor/src/NodeState.cpp \
    Nodeeditor/src/NodeStyle.cpp \
    Nodeeditor/src/Properties.cpp \
    Nodeeditor/src/StyleCollection.cpp \
    Connections/eventreceiver.cpp \
    Connections/eventsender.cpp \
    WidgetControllers/tagtreeinterface.cpp \
    Tunnelling/flowscenewrapper.cpp \
    Tunnelling/tunnellist.cpp \
    WidgetControllers/projecthierarchyinterface.cpp \
    WidgetControllers/centraltabinterface.cpp \
    Style/DarkStyle.cpp \
    Style/framelesswindow/windowdragger.cpp \
    Style/framelesswindow/framelesswindow.cpp \
    WidgetControllers/configwidgetinterface.cpp \
    WidgetControllers/statswidgetcontroller.cpp \
    Models/testmodel.cpp \
    WidgetControllers/console.cpp \
    Models/payloadvismodel.cpp \
    Models/socketmodel.cpp \
    Style/socketview.cpp \
    Models/gamepadmodel.cpp \
    Style/xyvis.cpp \
    Style/gamepadview.cpp \
    Models/convertermodel.cpp \
    Style/converterview.cpp \
    gamepadbackend/gamepad.cpp \
    gamepadbackend/gamepadbackend.cpp \
    gamepadbackend/gamepadmanager.cpp \
    gamepadbackend/xinputbackend.cpp

HEADERS += \
    Models/models.hpp \
    Models/printermodel.h \
    Models/monarchmodel.h \
    Connections/payload.h \
    Connections/connectionstats.h \
    Connections/streamreceiver.h \
    Connections/streamsender.h \
    Common/project.h \
    Common/taglist.h \
    Common/flowlist.h \
    Common/tagtype.h \
    Nodeeditor/include/nodes/internal/Compiler.hpp \
    Nodeeditor/include/nodes/internal/Connection.hpp \
    Nodeeditor/include/nodes/internal/ConnectionGeometry.hpp \
    Nodeeditor/include/nodes/internal/ConnectionGraphicsObject.hpp \
    Nodeeditor/include/nodes/internal/ConnectionID.hpp \
    Nodeeditor/include/nodes/internal/ConnectionState.hpp \
    Nodeeditor/include/nodes/internal/ConnectionStyle.hpp \
    Nodeeditor/include/nodes/internal/DataFlowModel.hpp \
    Nodeeditor/include/nodes/internal/DataFlowScene.hpp \
    Nodeeditor/include/nodes/internal/DataModelRegistry.hpp \
    Nodeeditor/include/nodes/internal/Export.hpp \
    Nodeeditor/include/nodes/internal/FlowScene.hpp \
    Nodeeditor/include/nodes/internal/FlowSceneModel.hpp \
    Nodeeditor/include/nodes/internal/FlowView.hpp \
    Nodeeditor/include/nodes/internal/FlowViewStyle.hpp \
    Nodeeditor/include/nodes/internal/memory.hpp \
    Nodeeditor/include/nodes/internal/Node.hpp \
    Nodeeditor/include/nodes/internal/NodeData.hpp \
    Nodeeditor/include/nodes/internal/NodeDataModel.hpp \
    Nodeeditor/include/nodes/internal/NodeGeometry.hpp \
    Nodeeditor/include/nodes/internal/NodeGraphicsObject.hpp \
    Nodeeditor/include/nodes/internal/NodeIndex.hpp \
    Nodeeditor/include/nodes/internal/NodePainterDelegate.hpp \
    Nodeeditor/include/nodes/internal/NodeState.hpp \
    Nodeeditor/include/nodes/internal/NodeStyle.hpp \
    Nodeeditor/include/nodes/internal/OperatingSystem.hpp \
    Nodeeditor/include/nodes/internal/PortType.hpp \
    Nodeeditor/include/nodes/internal/QStringStdHash.hpp \
    Nodeeditor/include/nodes/internal/QUuidStdHash.hpp \
    Nodeeditor/include/nodes/internal/Serializable.hpp \
    Nodeeditor/include/nodes/internal/Style.hpp \
    Nodeeditor/include/nodes/internal/TypeConverter.hpp \
    Nodeeditor/include/nodes/Connection \
    Nodeeditor/include/nodes/ConnectionStyle \
    Nodeeditor/include/nodes/DataFlowModel \
    Nodeeditor/include/nodes/DataFlowScene \
    Nodeeditor/include/nodes/DataModelRegistry \
    Nodeeditor/include/nodes/FlowScene \
    Nodeeditor/include/nodes/FlowSceneModel \
    Nodeeditor/include/nodes/FlowView \
    Nodeeditor/include/nodes/FlowViewStyle \
    Nodeeditor/include/nodes/Node \
    Nodeeditor/include/nodes/NodeData \
    Nodeeditor/include/nodes/NodeDataModel \
    Nodeeditor/include/nodes/NodeGeometry \
    Nodeeditor/include/nodes/NodeGraphicsObject \
    Nodeeditor/include/nodes/NodeIndex \
    Nodeeditor/include/nodes/NodePainterDelegate \
    Nodeeditor/include/nodes/NodeState \
    Nodeeditor/include/nodes/NodeStyle \
    Nodeeditor/include/nodes/TypeConverter \
    Nodeeditor/src/ConnectionBlurEffect.hpp \
    Nodeeditor/src/ConnectionPainter.hpp \
    Nodeeditor/src/NodeConnectionInteraction.hpp \
    Nodeeditor/src/NodePainter.hpp \
    Nodeeditor/src/Properties.hpp \
    Nodeeditor/src/StyleCollection.hpp \
    Common/config.h \
    mainwindow.h \
    Connections/eventreceiver.h \
    Connections/eventsender.h \
    WidgetControllers/tagtreeinterface.h \
    Tunnelling/flowscenewrapper.h \
    Tunnelling/tunnellist.h \
    WidgetControllers/projecthierarchyinterface.h \
    WidgetControllers/centraltabinterface.h \
    Style/DarkStyle.h \
    Style/framelesswindow/windowdragger.h \
    Style/framelesswindow/framelesswindow.h \
    WidgetControllers/configwidgetinterface.h \
    WidgetControllers/statswidgetcontroller.h \
    Models/testmodel.h \
    WidgetControllers/console.h \
    Models/payloadvismodel.h \
    Models/socketmodel.h \
    Style/socketview.h \
    Models/gamepadmodel.h \
    Style/xyvis.h \
    Models/convertermodel.h \
    Style/converterview.h \
    Style/gamepadview.h \
    gamepadbackend/gamepad.h \
    gamepadbackend/gamepadbackend.h \
    gamepadbackend/gamepadmanager.h \
    gamepadbackend/xinputbackend.h

FORMS += \
        mainwindow.ui \
    Style/framelesswindow/framelesswindow.ui

RESOURCES += \
    resources/resources.qrc \
    Style/darkstyle.qrc \
    Style/framelesswindow.qrc

RC_ICONS = resources/icon.ico
ICON = resources/icon.icns
