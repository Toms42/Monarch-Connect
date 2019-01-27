#ifndef CONVERTERMODEL_H
#define CONVERTERMODEL_H

#include <QObject>
#include "QDebug"
#include "Models/monarchmodel.h"
#include <nodes/NodeDataModel>
#include "Common/project.h"
#include "Common/taglist.h"
#include <QPushButton>
#include "Style/converterview.h"
#include <QTimer>
#include "gamepadmodel.h"

#define REFRESH 400

class ConverterModel:public MonarchModel
{
    Q_OBJECT
private:
    double _max,_min;
    bool dataReady;
    Payload toSend;
    QTimer *timer;
    ConverterView *_view;
    enum InPortTypes{
        PAYLOADPORTIN = 0,
        _NUMPORTSIN
     };
    enum OutPortTypes{
        STREAMPORTOUT = 0,
        _NUMPORTSOUT
     };
    enum Status{
        ON = 0,
        OFF
    };
    Status _status;

public:
    enum ContFields{
        AMPLITUDE,
        DIHEDRAL,
        ROLL,
        ANG_V,
        GLIDE_THRESH,
        _NUMFIELDS
    };

private:
    QVector<QString> contFieldNames = {
        "Amplitude",
        "Dihedral",
        "Roll",
        "Angular Velocity",
        "Glide Threshold"
    };
    QVector<QString> contFieldUnits = {
        "Degrees",
        "Degrees",
        "Degrees",
        "Degrees per Second",
        "Degrees per Second"
    };
    QVector<double> contFieldScalars = QVector<double>(ContFields::_NUMFIELDS, 10);

public:
    ConverterModel() : MonarchModel(), _view(new ConverterView()), _status(OFF){

        auto &t = Project::getInstance().getTagList();
        auto type = std::make_unique<TagType>("Cont", ContFields::_NUMFIELDS,
                                              contFieldNames,
                                              contFieldScalars,
                                              contFieldUnits);
        t.insert(std::move(type));
        toSend = Payload();
        dataReady = false;
        _max = 1;
        _min = -1;
        setup();
        connect(this, &ConverterModel::statusChanged, _view, &ConverterView::setStatus);
        connect(_view, &ConverterView::pressed, this, &ConverterModel::changeStatus);
        connect(this, &ConverterModel::dataChanged, _view, &ConverterView::setData);
        timer = new QTimer();
        connect(timer, &QTimer::timeout, this, &ConverterModel::sendPayload);
        emit(statusChanged("Off"));
        timer->start(REFRESH); //call updateTimes() every REFRESH milliseconds
    }
    ~ConverterModel() override{}

public:
    //basic info about the node:
    QString caption() const  override
    {
        return "Monarch Converter";
    }

    QString name() const  override
    {
        return "Monarch";
    }

    QWidget *embeddedWidget() override
    {
        return _view;
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

    void loadData(QJsonObject const& modelJson) override
    {
        qDebug() << modelJson["test"].toString();
    }

    //functions to access data in/out of the node.
    void inputDataReady(Payload p, int) override
    {
        toSend = p; //update what to send at clock timeout
        dataReady = true;
    }

    Payload getOutputData(int index) override
    {

    }

    //get arrays of inputs/output ports. Called only on instantiation of node.
    QVector<MonarchInputPort> getInputPortArray()  const override
    {
        return QVector<MonarchModel::MonarchInputPort> {
            {PortType::PAYLOAD, QString("x360"), -1}
        };
    }

    QVector<MonarchOutputPort> getOutputPortArray()  const override
    {
        return QVector<MonarchModel::MonarchOutputPort> {
            {PortType::STREAM, QString("stream"), -1}
        };
    }

private:
    //scale to new range
    double scaleValue(double min, double max, double input){
        double slope = (max-min);
        return min + slope*((1-input)/2);
    }
    void convertAndSend(Payload p)
    {
        auto gpID = Project::getInstance().getTagList().getTagID("Gamepad");
        if(p.getTagID() != gpID) return;

        auto contID = Project::getInstance().getTagList().getTagID("Cont");
        QVector<double> vals(ContFields::_NUMFIELDS);
        vals[ContFields::AMPLITUDE] = p.getVal(GamepadModel::GamepadFields::RIGHTY) ;
        vals[ContFields::ROLL] = p.getVal(GamepadModel::GamepadFields::RIGHTX) ;
        vals[ContFields::DIHEDRAL] = p.getVal(GamepadModel::GamepadFields::LEFTX);
        vals[ContFields::ANG_V] = p.getVal(GamepadModel::GamepadFields::LEFTY) ;
        vals[ContFields::GLIDE_THRESH] = 5;

        //scale values
        vals[ContFields::AMPLITUDE] = scaleValue(_view->_minAmplitude->text().toFloat(),
                                                 _view->_maxAmplitude->text().toFloat(),
                                                 vals[ContFields::AMPLITUDE]);

        vals[ContFields::ROLL] = scaleValue(_view->_minRoll->text().toFloat(),
                                            _view->_maxRoll->text().toFloat(),
                                            vals[ContFields::ROLL]);

        vals[ContFields::DIHEDRAL] = scaleValue(_view->_minDihedral->text().toFloat(),
                                                _view->_maxDihedral->text().toFloat(),
                                                vals[ContFields::DIHEDRAL]);

        vals[ContFields::ANG_V] = scaleValue(_view->_minAngV->text().toFloat(),
                                             _view->_maxAngV->text().toFloat(),
                                             vals[ContFields::ANG_V]);

        vals[ContFields::GLIDE_THRESH] = _view->_glideThresh->text().toFloat();


        Payload out(contID, ContFields::_NUMFIELDS, vals);
        sendOnStream(STREAMPORTOUT, out);
    }

signals:
    void statusChanged(QString data);
    void dataChanged(QString data);

private slots:
    void sendPayload(){
        if(!dataReady){
            return;
        }
        Payload p = toSend;
        if(p.getTagID() != Project::getInstance().getTagList().getTagID("Gamepad"))
        {
            return;
        }
        if(_status == ON){
            convertAndSend(p);
            emit(dataChanged(p.toString()));
            return;
        }
        else{
            auto contID = Project::getInstance().getTagList().getTagID("Cont");
            QVector<double> vals(ContFields::_NUMFIELDS);
            vals[ContFields::AMPLITUDE] = 0;
            vals[ContFields::ROLL] = 0;
            vals[ContFields::DIHEDRAL] = 0;
            vals[ContFields::ANG_V] = 0;
            vals[ContFields::GLIDE_THRESH] = 0;


            Payload out(contID, ContFields::_NUMFIELDS, vals);
            sendOnStream(STREAMPORTOUT, out);
            emit(dataChanged(out.toString()));
        }
    }
    void changeStatus(){
        if(_status == ON){
            _status = OFF;
            emit(statusChanged("Off"));
        }
        else{
            _status = ON;
            emit(statusChanged("On"));
        }
    }

};

#endif // CONVERTERMODEL_H
