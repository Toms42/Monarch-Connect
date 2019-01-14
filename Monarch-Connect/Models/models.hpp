#pragma once

#include <QtCore/QObject>

#include <nodes/NodeData>
#include <nodes/NodeDataModel>
#include <QPushButton>
#include <QDebug>
#include "Connections/streamsender.h"
#include "Connections/streamreceiver.h"
#include "Common/project.h"
#include "Connections/payload.h"

#include <memory>

using QtNodes::PortDirection;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class MyNodeData : public NodeData
{
public:

    NodeDataType
    type() const override
    { return NodeDataType {"MyNodeData", "My Node Data"}; }
};

//------------------------------------------------------------------------------

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class MyDataModel : public NodeDataModel
{
    Q_OBJECT

public:
    MyDataModel()
        : NodeDataModel(),
        _button(new QPushButton()),
        _stream(new StreamSender()),
        _data(),
        _listener()
    {
        auto &t = Project::getInstance().getTagList();
        auto type = std::make_unique<TagType>("test", "foo", 10, "bar");
        t.insert(std::move(type));
        _button->setText("press");
        connect(_button, SIGNAL(pressed()),
                this, SLOT(button_pressed()));
        connect(&_listener, &StreamReceiver::dataReady,
                this, &MyDataModel::streamIn);
    }
    virtual
    ~MyDataModel() override {}

public:

    QString
    caption() const override
    {
        return QString("My Data Model");
    }

    QString
    name() const override
    {
        return QString("MyDataModel");
    }

public:

    QJsonObject
    save() const override
    {
        QJsonObject modelJson;

        modelJson["name"] = name();

        return modelJson;
    }

public:

    unsigned int
    nPorts(PortDirection) const override
    {
        return 2;
    }

    NodeDataType
    dataType(PortDirection type, PortIndex index) const override
    {
        if(type == PortDirection::In)
        {
            switch(index)
            {
            case 0:
                return StreamSender().type();
            case 1:
                return MyNodeData().type();
            }
        }
        else if(type == PortDirection::Out)
        {
            switch(index)
            {
            case 1:
                return StreamSender().type();
            case 0:
                return MyNodeData().type();
            }
        }
        return NodeDataType{"error", "error"};
    }

    std::shared_ptr<NodeData>
    outData(PortIndex index) override
    {
        switch(index)
        {
        case 1:
            return std::static_pointer_cast<NodeData>(_stream);
        case 0:
            return std::static_pointer_cast<NodeData>(_data);
        }
        return nullptr;
    }

    void
    setInData(std::shared_ptr<NodeData> data, PortIndex index) override
    {
        qDebug() << "input data updated";
        switch(index)
        {
        case 0:
            _listener.setSender(std::static_pointer_cast<StreamSender>(data));
            break;
        case 1:
            _data = std::static_pointer_cast<MyNodeData>(data);
            emit(dataUpdated(1));
            return ;
        }
    }

    QWidget *
    embeddedWidget() override { return _button; }

    QWidget *configWidget() override
    {
        return nullptr;
    }
public slots:
    void button_pressed()
    {
        auto &t = Project::getInstance().getTagList();
        QUuid id = t.getTagID("test");
        Payload p(id, 100);
        _stream->send(p);
        //_ports--;
        //qDebug() << "pressed: " << _ports << "\n";
        //emit(portRemoved(PortType::Out, _ports - 1));
    }
    void streamIn(Payload payload)
    {
        qDebug() << "got: ";
        qDebug() << payload.getFieldName(0)
                 << ": "
                 << payload.getVal(0)
                 << payload.getFieldUnit(0);
    }
protected:
    QPushButton *_button;
    std::shared_ptr<StreamSender> _stream;
    std::shared_ptr<MyNodeData> _data;
    StreamReceiver _listener;
};
