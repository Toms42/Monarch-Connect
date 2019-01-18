#ifndef GAMEPADMODEL_H
#define GAMEPADMODEL_H

#include <QObject>
#include "QDebug"
#include "Models/monarchmodel.h"
#include <nodes/NodeDataModel>
#include "Common/project.h"
#include "Common/taglist.h"
#include <QPushButton>
#include "Style/gamepadview.h"
#include "gamepadbackend/gamepad.h"
#include "gamepadbackend/gamepadmanager.h"

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

        _view = new GamepadView();
        _gpmanager = new QGamepadManager();

        setup();

        connect(&_pollTimer, &QTimer::timeout,
                this, &GamepadModel::sample);
        connect(_view, &GamepadView::refreshPressed,
                this, &GamepadModel::onRefresh);
        connect(_view, &GamepadView::setPressed,
                this, &GamepadModel::onSet);
        sendZero();
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
        return _view;
    }
    QWidget *configWidget() override
    {
        return nullptr;
    }

private slots:
    void onRefresh()
    {
        qDebug() << "scanning usb controllers";
        _view->selector()->clear();
        QList<int> gps = _gpmanager->getConnectedGamepads();
        for(auto id : gps)
        {
            qDebug() << "adding one";
            QString name = QGamepad(id, this, _gpmanager).getName();
            if(name == "")
            {
                name = QString("USB Controller %1").arg(QString::number(id));
            }
            _view->selector()->addItem(name, QVariant(id));
        }
    }

    void onSet()
    {
        int id = _view->selector()->currentData().toInt();
        _gp = new QGamepad(id, this,  _gpmanager);
        if(_gp == nullptr || !_gpmanager->isGamepadConnected(id) || !_gp->isConnected())
        {
            _gp = nullptr;
            _view->connectedID()->setText("N/A");
            _view->connectedName()->setText("N/A");
            _pollTimer.stop();
            sendZero();
            return;
        }
        _view->connectedID()->setText(QString::number(_gp->getDeviceId()));
        _view->connectedName()->setText(_gp->getName());
        _pollTimer.start(20);
    }

    void sample()
    {
        //qDebug() << "sampling";
        if(_gp == nullptr || !_gpmanager->isGamepadConnected(_gp->getDeviceId()) || !_gp->isConnected())
        {
            _gp = nullptr;
            _view->connectedID()->setText("N/A");
            _view->connectedName()->setText("N/A");
            _pollTimer.stop();
            sendZero();
            return;
        }
        QVector<double> newVals(GamepadFields::_NUMFIELDS);
        newVals[LEFTX] = _gp->getAxisLeftX();
        newVals[LEFTY] = _gp->getAxisLeftY();
        newVals[RIGHTX] = _gp->getAxisRightX();
        newVals[RIGHTY] = _gp->getAxisRightY();
        newVals[BUTTONL1] = _gp->getButtonL1() ? 1 : 0;
        newVals[BUTTONL2] = _gp->getButtonL2() ? 1 : 0;
        newVals[BUTTONL3] = _gp->getButtonL3() ? 1 : 0;
        newVals[BUTTONR1] = _gp->getButtonR1() ? 1 : 0;
        newVals[BUTTONR2] = _gp->getButtonR2() ? 1 : 0;
        newVals[BUTTONR3] = _gp->getButtonR3() ? 1 : 0;
        newVals[BUTTONA] = _gp->getButtonA() ? 1 : 0;
        newVals[BUTTONB] = _gp->getButtonB() ? 1 : 0;
        newVals[BUTTONX] = _gp->getButtonX() ? 1 : 0;
        newVals[BUTTONY] = _gp->getButtonY() ? 1 : 0;

        _view->leftVis()->setCoords(newVals[LEFTX], newVals[LEFTY]);
        _view->rightVis()->setCoords(newVals[RIGHTX], newVals[RIGHTY]);

        auto &t = Project::getInstance().getTagList();
        auto tag = t.getTagID("Gamepad");
        _vals = Payload(tag, _NUMFIELDS, newVals);
        emit(dataUpdated(ValsPort));
    }

public:
    //load/save your internal data in the node, using json.
    QJsonObject saveData() const override
    {
        QJsonObject test;
        test["test"] = "test data!";
        return test;
    }

    void loadData(QJsonObject const& modelJson) override
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
    void sendZero()
    {
        QVector<double> newVals(GamepadFields::_NUMFIELDS, 0);
        auto &t = Project::getInstance().getTagList();
        auto tag = t.getTagID("Gamepad");
        _vals = Payload(tag, _NUMFIELDS, newVals);
        _view->leftVis()->setCoords(0,0);
        _view->rightVis()->setCoords(0,0);
        emit(dataUpdated(ValsPort));
    }
    Payload _vals;
    GamepadView *_view;
    QGamepadManager *_gpmanager;
    QGamepad *_gp = nullptr;
    QTimer _pollTimer;
};

#endif
