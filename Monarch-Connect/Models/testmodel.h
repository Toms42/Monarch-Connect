#ifndef TESTMODEL_H
#define TESTMODEL_H

#include <QObject>
#include "QDebug"
#include "Models/monarchmodel.h"
#include <nodes/NodeDataModel>
#include "Common/project.h"
#include "Common/taglist.h"
#include <QPushButton>

class TestModel:public MonarchModel
{
    Q_OBJECT
private:
    QPushButton *button;
    enum InPortTypes{
        STREAMPORTIN = 0,
        _NUMPORTSIN
    };

    enum OutPortTypes{
        STREAMPORTOUT = 0,
        PAYLOADOUT = 1,
        _NUMPORTSOUT
    };

public:
    TestModel():MonarchModel(), button(new QPushButton("test stream")){
        setup();

        auto &t = Project::getInstance().getTagList();
        auto type = std::make_unique<TagType>("michael's tag", "hi", 100, "michaels");
        t.insert(std::move(type));
        connect(button, &QPushButton::pressed,
                this, &TestModel::send_stuff);
    }

    ~TestModel() override{

    }

    QString caption() const override{
        return "Test node";
    }

    QString name() const override{
        return "Test node";
    }

    QWidget *embeddedWidget() override{
        return button;
    }

    QWidget *configWidget() override{
        return nullptr;
    }

    QJsonObject saveData() const override{
        QJsonObject data;
        data["test"] = "test data";
        return data;
    }

    void loadData(QJsonObject const& modelJson) override{
        qDebug() << modelJson["test"].toString();
    }

    void inputDataReady(Payload data, int index) override{

    }

    Payload getOutputData(int index) override{
        auto t = Project::getInstance().getTagList().getTagID("michael's tag");
        Payload mypayload(t, 35);
        //emit(sent());
        return mypayload;
    }

    //get arrays for input and output ports
    QVector<MonarchInputPort> getInputPortArray()  const override{
        QVector<MonarchInputPort> ports(_NUMPORTSIN);
        ports[STREAMPORTIN] = {PortType::STREAM, QString("input"), -1};
        return ports;
    }

    //get arrays for input and output ports
    QVector<MonarchOutputPort> getOutputPortArray()  const override{
        QVector<MonarchOutputPort> ports(_NUMPORTSOUT);
        ports[STREAMPORTOUT] = {PortType::STREAM, QString("output stream"), -1};
        ports[PAYLOADOUT] = {PortType::PAYLOAD, QString("output payload"), -1};
        return ports;
    }

public slots:
    void send_stuff()
    {
        auto t = Project::getInstance().getTagList().getTagID("michael's tag");
        Payload mypayload(t, 35);
        sendOnStream(STREAMPORTOUT, mypayload);
    }


};

#endif // TESTMODEL_H
