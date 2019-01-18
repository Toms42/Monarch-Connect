QT       += core gui testlib opengl network gamepad
# Compile with c++14 standard:
CONFIG += c++14

#enable coverage analysis
#QMAKE_CXXFLAGS += --coverage
#LIBS += -lgcov

#minimal optimization (for better coverage analysis)
#QMAKE_CXXFLAGS -= -O1
#QMAKE_CXXFLAGS -= -O2
#QMAKE_CXXFLAGS -= -O3
#QMAKE_CXXFLAGS *= -O0
#QMAKE_LFLAGS -= -O1
#QMAKE_LFLAGS -= -O2
#QMAKE_LFLAGS -= -O3
#QMAKE_LFLAGS *= -O0

# let nodeeditor know it's being statically linked
DEFINES += NODE_EDITOR_STATIC
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = Monarch-Connect-Test
CONFIG   += console
CONFIG   += testcase
CONFIG   -= app_bundle

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += \
    "../Monarch-Connect/resources" \
    "../Monarch-Connect" \
    "../Monarch-Connect/Models" \
    "../Monarch-Connect/Style" \
    "../Monarch-Connect/Common" \
    "../Monarch-Connect/Connections" \
    "../Monarch-Connect/Nodeeditor" \
    "../Monarch-Connect/Tunnelling" \
    "../Monarch-Connect/WidgetControllers" \
    "../Monarch-Connect/Nodeeditor/src" \
    "../Monarch-Connect/Nodeeditor/include" \
    "../Monarch-Connect/Nodeeditor/include/nodes/internal"

SOURCES += \
        main.cpp \
        monarchconnecttest.cpp \
    ../Monarch-Connect/mainwindow.cpp \
    ../Monarch-Connect/Models/models.cpp \
    ../Monarch-Connect/Connections/payload.cpp \
    ../Monarch-Connect/Connections/connectionstats.cpp \
    ../Monarch-Connect/Connections/streamreceiver.cpp \
    ../Monarch-Connect/Connections/streamsender.cpp \
    ../Monarch-Connect/Common/project.cpp \
    ../Monarch-Connect/Common/taglist.cpp \
    ../Monarch-Connect/Common/flowlist.cpp \
    ../Monarch-Connect/Common/tagtype.cpp \
    ../Monarch-Connect/Nodeeditor/src/Connection.cpp \
    ../Monarch-Connect/Nodeeditor/src/ConnectionBlurEffect.cpp \
    ../Monarch-Connect/Nodeeditor/src/ConnectionGeometry.cpp \
    ../Monarch-Connect/Nodeeditor/src/ConnectionGraphicsObject.cpp \
    ../Monarch-Connect/Nodeeditor/src/ConnectionPainter.cpp \
    ../Monarch-Connect/Nodeeditor/src/ConnectionState.cpp \
    ../Monarch-Connect/Nodeeditor/src/ConnectionStyle.cpp \
    ../Monarch-Connect/Nodeeditor/src/DataFlowModel.cpp \
    ../Monarch-Connect/Nodeeditor/src/DataFlowScene.cpp \
    ../Monarch-Connect/Nodeeditor/src/DataModelRegistry.cpp \
    ../Monarch-Connect/Nodeeditor/src/FlowScene.cpp \
    ../Monarch-Connect/Nodeeditor/src/FlowSceneModel.cpp \
    ../Monarch-Connect/Nodeeditor/src/FlowView.cpp \
    ../Monarch-Connect/Nodeeditor/src/FlowViewStyle.cpp \
    ../Monarch-Connect/Nodeeditor/src/Node.cpp \
    ../Monarch-Connect/Nodeeditor/src/NodeConnectionInteraction.cpp \
    ../Monarch-Connect/Nodeeditor/src/NodeDataModel.cpp \
    ../Monarch-Connect/Nodeeditor/src/NodeGeometry.cpp \
    ../Monarch-Connect/Nodeeditor/src/NodeGraphicsObject.cpp \
    ../Monarch-Connect/Nodeeditor/src/NodePainter.cpp \
    ../Monarch-Connect/Nodeeditor/src/NodeState.cpp \
    ../Monarch-Connect/Nodeeditor/src/NodeStyle.cpp \
    ../Monarch-Connect/Nodeeditor/src/Properties.cpp \
    ../Monarch-Connect/Nodeeditor/src/StyleCollection.cpp \
    ../Monarch-Connect/Connections/eventreceiver.cpp \
    ../Monarch-Connect/Connections/eventsender.cpp \
    ../Monarch-Connect/WidgetControllers/tagtreeinterface.cpp \
    ../Monarch-Connect/Tunnelling/flowscenewrapper.cpp \
    ../Monarch-Connect/Tunnelling/tunnellist.cpp \
    ../Monarch-Connect/WidgetControllers/projecthierarchyinterface.cpp \
    ../Monarch-Connect/WidgetControllers/centraltabinterface.cpp \
    ../Monarch-Connect/Models/monarchmodel.cpp \
    ../Monarch-Connect/Models/printermodel.cpp \
    ../Monarch-Connect/WidgetControllers/configwidgetinterface.cpp \
    ../Monarch-Connect/WidgetControllers/statswidgetcontroller.cpp \
    ../Monarch-Connect/Models/testmodel.cpp \
    ../Monarch-Connect/WidgetControllers/console.cpp \
    ../Monarch-Connect/Models/payloadvismodel.cpp \
    ../Monarch-Connect/Models/socketmodel.cpp \
    ../Monarch-Connect/Style/socketview.cpp \
    ../Monarch-Connect/Style/xyvis.cpp \
    ../Monarch-Connect/Models/gamepadmodel.cpp \
    ../Monarch-Connect/Models/convertermodel.cpp \
    ../Monarch-Connect/Style/converterview.cpp \
    ../Monarch-Connect/Style/gamepadview.cpp

HEADERS += \
    monarchconnecttest.h \
    ../Monarch-Connect/Models/models.hpp \
    ../Monarch-Connect/Connections/payload.h \
    ../Monarch-Connect/Connections/connectionstats.h \
    ../Monarch-Connect/Connections/streamreceiver.h \
    ../Monarch-Connect/Connections/streamsender.h \
    ../Monarch-Connect/Common/project.h \
    ../Monarch-Connect/Common/taglist.h \
    ../Monarch-Connect/Common/flowlist.h \
    ../Monarch-Connect/Common/tagtype.h \
    ../Monarch-Connect/Nodeeditor/include/nodes/internal/Compiler.hpp \
    ../Monarch-Connect/Nodeeditor/include/nodes/internal/Connection.hpp \
    ../Monarch-Connect/Nodeeditor/include/nodes/internal/ConnectionGeometry.hpp \
    ../Monarch-Connect/Nodeeditor/include/nodes/internal/ConnectionGraphicsObject.hpp \
    ../Monarch-Connect/Nodeeditor/include/nodes/internal/ConnectionID.hpp \
    ../Monarch-Connect/Nodeeditor/include/nodes/internal/ConnectionState.hpp \
    ../Monarch-Connect/Nodeeditor/include/nodes/internal/ConnectionStyle.hpp \
    ../Monarch-Connect/Nodeeditor/include/nodes/internal/DataFlowModel.hpp \
    ../Monarch-Connect/Nodeeditor/include/nodes/internal/DataFlowScene.hpp \
    ../Monarch-Connect/Nodeeditor/include/nodes/internal/DataModelRegistry.hpp \
    ../Monarch-Connect/Nodeeditor/include/nodes/internal/Export.hpp \
    ../Monarch-Connect/Nodeeditor/include/nodes/internal/FlowScene.hpp \
    ../Monarch-Connect/Nodeeditor/include/nodes/internal/FlowSceneModel.hpp \
    ../Monarch-Connect/Nodeeditor/include/nodes/internal/FlowView.hpp \
    ../Monarch-Connect/Nodeeditor/include/nodes/internal/FlowViewStyle.hpp \
    ../Monarch-Connect/Nodeeditor/include/nodes/internal/memory.hpp \
    ../Monarch-Connect/Nodeeditor/include/nodes/internal/Node.hpp \
    ../Monarch-Connect/Nodeeditor/include/nodes/internal/NodeData.hpp \
    ../Monarch-Connect/Nodeeditor/include/nodes/internal/NodeDataModel.hpp \
    ../Monarch-Connect/Nodeeditor/include/nodes/internal/NodeGeometry.hpp \
    ../Monarch-Connect/Nodeeditor/include/nodes/internal/NodeGraphicsObject.hpp \
    ../Monarch-Connect/Nodeeditor/include/nodes/internal/NodeIndex.hpp \
    ../Monarch-Connect/Nodeeditor/include/nodes/internal/NodePainterDelegate.hpp \
    ../Monarch-Connect/Nodeeditor/include/nodes/internal/NodeState.hpp \
    ../Monarch-Connect/Nodeeditor/include/nodes/internal/NodeStyle.hpp \
    ../Monarch-Connect/Nodeeditor/include/nodes/internal/OperatingSystem.hpp \
    ../Monarch-Connect/Nodeeditor/include/nodes/internal/PortType.hpp \
    ../Monarch-Connect/Nodeeditor/include/nodes/internal/QStringStdHash.hpp \
    ../Monarch-Connect/Nodeeditor/include/nodes/internal/QUuidStdHash.hpp \
    ../Monarch-Connect/Nodeeditor/include/nodes/internal/Serializable.hpp \
    ../Monarch-Connect/Nodeeditor/include/nodes/internal/Style.hpp \
    ../Monarch-Connect/Nodeeditor/include/nodes/internal/TypeConverter.hpp \
    ../Monarch-Connect/Nodeeditor/include/nodes/Connection \
    ../Monarch-Connect/Nodeeditor/include/nodes/ConnectionStyle \
    ../Monarch-Connect/Nodeeditor/include/nodes/DataFlowModel \
    ../Monarch-Connect/Nodeeditor/include/nodes/DataFlowScene \
    ../Monarch-Connect/Nodeeditor/include/nodes/DataModelRegistry \
    ../Monarch-Connect/Nodeeditor/include/nodes/FlowScene \
    ../Monarch-Connect/Nodeeditor/include/nodes/FlowSceneModel \
    ../Monarch-Connect/Nodeeditor/include/nodes/FlowView \
    ../Monarch-Connect/Nodeeditor/include/nodes/FlowViewStyle \
    ../Monarch-Connect/Nodeeditor/include/nodes/Node \
    ../Monarch-Connect/Nodeeditor/include/nodes/NodeData \
    ../Monarch-Connect/Nodeeditor/include/nodes/NodeDataModel \
    ../Monarch-Connect/Nodeeditor/include/nodes/NodeGeometry \
    ../Monarch-Connect/Nodeeditor/include/nodes/NodeGraphicsObject \
    ../Monarch-Connect/Nodeeditor/include/nodes/NodeIndex \
    ../Monarch-Connect/Nodeeditor/include/nodes/NodePainterDelegate \
    ../Monarch-Connect/Nodeeditor/include/nodes/NodeState \
    ../Monarch-Connect/Nodeeditor/include/nodes/NodeStyle \
    ../Monarch-Connect/Nodeeditor/include/nodes/TypeConverter \
    ../Monarch-Connect/Nodeeditor/src/ConnectionBlurEffect.hpp \
    ../Monarch-Connect/Nodeeditor/src/ConnectionPainter.hpp \
    ../Monarch-Connect/Nodeeditor/src/NodeConnectionInteraction.hpp \
    ../Monarch-Connect/Nodeeditor/src/NodePainter.hpp \
    ../Monarch-Connect/Nodeeditor/src/Properties.hpp \
    ../Monarch-Connect/Nodeeditor/src/StyleCollection.hpp \
    ../Monarch-Connect/Common/config.h \
    ../Monarch-Connect/mainwindow.h \
    ../Monarch-Connect/Connections/eventreceiver.h \
    ../Monarch-Connect/Connections/eventsender.h \
    ../Monarch-Connect/WidgetControllers/tagtreeinterface.h \
    ../Monarch-Connect/Tunnelling/flowscenewrapper.h \
    ../Monarch-Connect/Tunnelling/tunnellist.h \
    ../Monarch-Connect/WidgetControllers/projecthierarchyinterface.h \
    ../Monarch-Connect/WidgetControllers/centraltabinterface.h \
    ../Monarch-Connect/Models/monarchmodel.h \
    ../Monarch-Connect/Models/printermodel.h \
    ../Monarch-Connect/WidgetControllers/configwidgetinterface.h \
    ../Monarch-Connect/WidgetControllers/statswidgetcontroller.h \
    ../Monarch-Connect/Models/testmodel.h \
    ../Monarch-Connect/WidgetControllers/console.h \
    ../Monarch-Connect/Models/payloadvismodel.h \
    ../Monarch-Connect/Models/socketmodel.h \
    ../Monarch-Connect/Style/socketview.h \
    ../Monarch-Connect/Style/xyvis.h \
    ../Monarch-Connect/Models/gamepadmodel.h \
    ../Monarch-Connect/Models/convertermodel.h \
    ../Monarch-Connect/Style/converterview.h \
    ../Monarch-Connect/Style/gamepadview.h


FORMS += \
        ../Monarch-Connect/mainwindow.ui

DISTFILES += \
    ../Monarch-Connect/resources/DefaultStyle.json \
    ../Monarch-Connect/resources/convert.png

RESOURCES += \
    ../Monarch-Connect/resources/resources.qrc \
    ../Monarch-Connect/resources/resources.qrc
