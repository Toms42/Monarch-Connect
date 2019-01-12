#ifndef PRINTERMODEL_H
#define PRINTERMODEL_H

#include <QObject>
#include "QDebug"
#include "Models/monarchmodel.h"
#include <nodes/NodeDataModel>
#include "Common/project.h"
#include "Common/taglist.h"

class PrinterModel : public MonarchModel
{
    Q_OBJECT

public:
    PrinterModel() : MonarchModel()
    {
        //setup();
    }
    ~PrinterModel() override
    {

    }

public:
    //basic info about the node:
    QString caption() const  override
    {
        return "Debugging Printer";
    }

    QString name() const  override
    {
        return "Printer";
    }

    QWidget *embeddedWidget() override
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
    void inputDataReady(Payload data, int index) override
    {
        if(index == 0) qDebug() << data;
    }

    Payload getOutputData(int index) override
    {
        return Payload();
    }

    //get arrays of inputs/output ports. Called only on instantiation of node.
    QVector<MonarchInputPort> getInputPortArray()  const override
    {
        return QVector<PrinterModel::MonarchInputPort>();
        //QVector<PrinterModel::MonarchInputPort> r = {
        //    {PortType::STREAM, "inputs", -1}
        //};
    }

    QVector<MonarchOutputPort> getOutputPortArray()  const override
    {
        return QVector<PrinterModel::MonarchOutputPort>();
    }
};

#endif // PRINTERMODEL_H
