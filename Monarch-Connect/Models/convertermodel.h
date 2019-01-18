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
#define REFRESH 100

class ConverterModel:public MonarchModel
{
    Q_OBJECT
private:
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
    ConverterModel() : MonarchModel(), _view(new ConverterView()), _status(OFF){
        toSend = Payload();
        dataReady = false;
        setup();
        connect(this, &ConverterModel::statusChanged, _view, &ConverterView::setStatus);
        connect(_view, &ConverterView::pressed, this, &ConverterModel::changeStatus);
        connect(this, &ConverterModel::dataChanged, _view, &ConverterView::setData);
        timer = new QTimer();
        connect(timer, &QTimer::timeout, this, &ConverterModel::sendPayload);
        timer->start(REFRESH); //call updateTimes() every REFRESH milliseconds
    }
    ~ConverterModel() override{}

public:
    //basic info about the node:
    QString caption() const  override
    {
        return "Gamepad to Stream Converter";
    }

    QString name() const  override
    {
        return "Gamepad to Stream Converter";
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

    void loadData(QJsonObject const& modelJson) const override
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
            {PortType::PAYLOAD, QString("controller input"), -1}
        };
    }

    QVector<MonarchOutputPort> getOutputPortArray()  const override
    {
        return QVector<MonarchModel::MonarchOutputPort> {
            {PortType::STREAM, QString("stream to uart"), -1}
        };
    }
signals:
    void statusChanged(QString data);
    void dataChanged(QString data);
public slots:
    void sendPayload(){
        if(!dataReady){
            return;
        }
        Payload p = toSend;
        if(_status == ON){
            sendOnStream(STREAMPORTOUT, p);
            emit(dataChanged(p.toString()));
            return;
        }
        else{
            QVector<double> zeros = QVector<double>();
            for(int i = 0; i < p.nFields(); i++){
                zeros.append(0);
            }
            Payload out = Payload(p.getTagID(), p.nFields(), zeros);
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
