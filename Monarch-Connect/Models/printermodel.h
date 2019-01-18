#ifndef PRINTERMODEL_H
#define PRINTERMODEL_H

#include <QObject>
#include "QDebug"
#include "Models/monarchmodel.h"
#include <nodes/NodeDataModel>
#include "Common/project.h"
#include "Common/taglist.h"
#include <QPushButton>

class PrinterModel : public MonarchModel
{
    Q_OBJECT

private:
    enum InPortTypes{
        STREAMPORT = 0,
        _NUMPORTS
    };

public:
    PrinterModel() : MonarchModel(), _myButton(new QPushButton("hello!"))
    {
        setup();
    }
    ~PrinterModel() override
    {

    }

public:
    //basic info about the node:
    QString caption() const  override
    {
        return "Printer";
    }

    QString name() const  override
    {
        return "Printer";
    }

    QWidget *embeddedWidget() override
    {
        return nullptr;
    }
    QWidget *configWidget() override
    {
        return _myButton;
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
    void inputDataReady(Payload data, int index) override
    {
        qDebug() << "got data";
        //print out the data
        QString dataString = data.toString();
        if(index == 0) emit(Project::getInstance().print(dataString));
    }

    Payload getOutputData(int index) override
    {
        return Payload();
    }

    //get arrays of inputs/output ports. Called only on instantiation of node.
    QVector<MonarchInputPort> getInputPortArray()  const override
    {
        QVector<PrinterModel::MonarchInputPort> r(_NUMPORTS);
        r[STREAMPORT] = {PortType::STREAM, QString("print stream"), -1};
        return r;
    }

    QVector<MonarchOutputPort> getOutputPortArray()  const override
    {
        return QVector<PrinterModel::MonarchOutputPort>();
    }

private:
    QPushButton *_myButton;
};

#endif // PRINTERMODEL_H
