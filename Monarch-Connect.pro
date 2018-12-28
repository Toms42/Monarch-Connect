#-------------------------------------------------
#
# Project created by QtCreator 2018-12-24T19:30:35
#
#-------------------------------------------------

QT       += core gui opengl

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


INCLUDEPATH += "$$PWD/Nodeeditor/include"

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    Nodeeditor/src/Connection.cpp \
    Nodeeditor/src/ConnectionBlurEffect.cpp \
    Nodeeditor/src/ConnectionGeometry.cpp \
    Nodeeditor/src/ConnectionGraphicsObject.cpp \
    Nodeeditor/src/ConnectionPainter.cpp \
    Nodeeditor/src/ConnectionState.cpp \
    Nodeeditor/src/ConnectionStyle.cpp \
    Nodeeditor/src/DataModelRegistry.cpp \
    Nodeeditor/src/FlowScene.cpp \
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
    main.cpp \
    mainwindow.cpp \
    Nodeeditor/src/Connection.cpp \
    Nodeeditor/src/ConnectionBlurEffect.cpp \
    Nodeeditor/src/ConnectionGeometry.cpp \
    Nodeeditor/src/ConnectionGraphicsObject.cpp \
    Nodeeditor/src/ConnectionPainter.cpp \
    Nodeeditor/src/ConnectionState.cpp \
    Nodeeditor/src/ConnectionStyle.cpp \
    Nodeeditor/src/DataModelRegistry.cpp \
    Nodeeditor/src/FlowScene.cpp \
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
    main.cpp \
    mainwindow.cpp

HEADERS += \
        mainwindow.h \
    Nodeeditor/include/Compiler.hpp \
    Nodeeditor/include/Connection.hpp \
    Nodeeditor/include/ConnectionGeometry.hpp \
    Nodeeditor/include/ConnectionGraphicsObject.hpp \
    Nodeeditor/include/ConnectionState.hpp \
    Nodeeditor/include/ConnectionStyle.hpp \
    Nodeeditor/include/DataModelRegistry.hpp \
    Nodeeditor/include/Export.hpp \
    Nodeeditor/include/FlowScene.hpp \
    Nodeeditor/include/FlowView.hpp \
    Nodeeditor/include/FlowViewStyle.hpp \
    Nodeeditor/include/memory.hpp \
    Nodeeditor/include/Node.hpp \
    Nodeeditor/include/NodeData.hpp \
    Nodeeditor/include/NodeDataModel.hpp \
    Nodeeditor/include/NodeGeometry.hpp \
    Nodeeditor/include/NodeGraphicsObject.hpp \
    Nodeeditor/include/NodePainterDelegate.hpp \
    Nodeeditor/include/NodeState.hpp \
    Nodeeditor/include/NodeStyle.hpp \
    Nodeeditor/include/OperatingSystem.hpp \
    Nodeeditor/include/PortType.hpp \
    Nodeeditor/include/QStringStdHash.hpp \
    Nodeeditor/include/QUuidStdHash.hpp \
    Nodeeditor/include/Serializable.hpp \
    Nodeeditor/include/Style.hpp \
    Nodeeditor/include/TypeConverter.hpp \
    Nodeeditor/src/ConnectionBlurEffect.hpp \
    Nodeeditor/src/ConnectionPainter.hpp \
    Nodeeditor/src/NodeConnectionInteraction.hpp \
    Nodeeditor/src/NodePainter.hpp \
    Nodeeditor/src/Properties.hpp \
    Nodeeditor/src/StyleCollection.hpp \
    mainwindow.h \
    Nodeeditor/include/Compiler.hpp \
    Nodeeditor/include/Connection.hpp \
    Nodeeditor/include/ConnectionGeometry.hpp \
    Nodeeditor/include/ConnectionGraphicsObject.hpp \
    Nodeeditor/include/ConnectionState.hpp \
    Nodeeditor/include/ConnectionStyle.hpp \
    Nodeeditor/include/DataModelRegistry.hpp \
    Nodeeditor/include/Export.hpp \
    Nodeeditor/include/FlowScene.hpp \
    Nodeeditor/include/FlowView.hpp \
    Nodeeditor/include/FlowViewStyle.hpp \
    Nodeeditor/include/memory.hpp \
    Nodeeditor/include/Node.hpp \
    Nodeeditor/include/NodeData.hpp \
    Nodeeditor/include/NodeDataModel.hpp \
    Nodeeditor/include/NodeGeometry.hpp \
    Nodeeditor/include/NodeGraphicsObject.hpp \
    Nodeeditor/include/NodePainterDelegate.hpp \
    Nodeeditor/include/NodeState.hpp \
    Nodeeditor/include/NodeStyle.hpp \
    Nodeeditor/include/OperatingSystem.hpp \
    Nodeeditor/include/PortType.hpp \
    Nodeeditor/include/QStringStdHash.hpp \
    Nodeeditor/include/QUuidStdHash.hpp \
    Nodeeditor/include/Serializable.hpp \
    Nodeeditor/include/Style.hpp \
    Nodeeditor/include/TypeConverter.hpp \
    Nodeeditor/src/ConnectionBlurEffect.hpp \
    Nodeeditor/src/ConnectionPainter.hpp \
    Nodeeditor/src/NodeConnectionInteraction.hpp \
    Nodeeditor/src/NodePainter.hpp \
    Nodeeditor/src/Properties.hpp \
    Nodeeditor/src/StyleCollection.hpp \
    mainwindow.h \
    ui_mainwindow.h

FORMS += \
        mainwindow.ui

DISTFILES += \
    resources/DefaultStyle.json \
    resources/convert.png

RESOURCES += \
    resources/resources.qrc
