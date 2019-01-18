#ifndef GAMEPADMODEL_H
#define GAMEPADMODEL_H

#include <QObject>
#include "QDebug"
#include "Models/monarchmodel.h"
#include <nodes/NodeDataModel>
#include "Common/project.h"
#include "Common/taglist.h"
#include <QPushButton>

class GamepadModel : public MonarchModel
{
    Q_OBJECT

private:
    enum OutPortTypes{
        ValsPort = 0,
        _NUMPORTS
    };

public:
    enum GamepadFields{
        LEFTX,
        LEFTY,
        RIGHTX,
        RIGHTY,
        BUTTONL1,
        BUTTONL2,
        BUTTONL3,
        BUTTONR1,
        BUTTONR2,
        BUTTONR3,
        BUTTONA,
        BUTTONB,
        BUTTONX,
        BUTTONY,
        _NUMFIELDS
    };

private:
    QVector<QString> gamepadFieldNames = {
        "LEFTX",
        "LEFTY",
        "RIGHTX",
        "RIGHTY",
        "BUTTONL1",
        "BUTTONL2",
        "BUTTONL3",
        "BUTTONR1",
        "BUTTONR2",
        "BUTTONR3",
        "BUTTONA",
        "BUTTONB",
        "BUTTONX",
        "BUTTONY"
    };
    QVector<QString> gamepadFieldUnits = QVector<QString>(GamepadFields::_NUMFIELDS, "");
    QVector<double> gamepadFieldScalars = QVector<double>(GamepadFields::_NUMFIELDS, 1);

public:
    GamepadModel() : MonarchModel()
    {
        auto &t = Project::getInstance().getTagList();
        auto type = std::make_unique<TagType>("Gamepad", GamepadFields::_NUMFIELDS,
                                              gamepadFieldNames,
                                              gamepadFieldScalars,
                                              gamepadFieldUnits);
        t.insert(std::move(type));
        auto tag = t.getTagID("Gamepad");
        _vals = Payload(tag, GamepadFields::_NUMFIELDS,
                        QVector<double>(GamepadFields::_NUMFIELDS, 0));
        setup();
    }
    ~GamepadModel() override
    {

    }

public:
    //basic info about the node:
    QString caption() const  override
    {
        return "Gamepad";
    }

    QString name() const  override
    {
        return "Gamepad";
    }

    QWidget *embeddedWidget() override
    {
        return nullptr;
    }
    QWidget *configWidget() override
    {
        return nullptr;
    }

public:
    //load/save your internal data in the node, using json.
    QJsonObject saveData() const override
    {
        QJsonObject test;
        test["test"] = "test data!";
        return test;
    }

    void loadData(QJsonObject const& modelJson) const override
    {
        qDebug() << modelJson["test"].toString();
    }

    //functions to access data in/out of the node.
    void inputDataReady(Payload, int ) override
    {
    }

    Payload getOutputData(int index) override
    {
        if(index == ValsPort)
        {
            return _vals;
        }
    }

    //get arrays of inputs/output ports. Called only on instantiation of node.
    QVector<MonarchInputPort> getInputPortArray()  const override
    {
        return QVector<MonarchModel::MonarchInputPort>();
    }

    QVector<MonarchOutputPort> getOutputPortArray()  const override
    {
        return QVector<MonarchModel::MonarchOutputPort> {
            {PortType::PAYLOAD, QString("vals"), -1}
        };
    }

private:
    QPushButton *_myButton;
    Payload _vals;
};

#endif
