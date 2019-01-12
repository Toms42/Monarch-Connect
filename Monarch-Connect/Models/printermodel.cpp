#include "printermodel.h"
#include "QDebug"
#include "Common/project.h"
#include "Common/taglist.h"
#include "functional"
#include "Models/monarchmodel.h"

PrinterModel::PrinterModel()
    : MonarchModel()
{
    setup();
}

QString PrinterModel::caption() const
{
    return "Debugging Printer";
}


QString PrinterModel::name() const
{
    return "Printer";
}

QWidget *PrinterModel::embeddedWidget()
{
    return nullptr;
}

//load/save your internal data in the node, using json.
QJsonObject PrinterModel::saveData() const
{
    QJsonObject test;
    test["test"] = "test data!";
    return test;
}

void PrinterModel::loadData(QJsonObject const& modelJson) const
{
    qDebug() << modelJson["test"].toString();
}

//get arrays of inputs/output ports. Called only on instantiation of node.
QVector<PrinterModel::MonarchInputPort> PrinterModel::getInputPortArray()  const
{
    return QVector<PrinterModel::MonarchInputPort>();
    //QVector<PrinterModel::MonarchInputPort> r = {
    //    {PortType::STREAM, "inputs", -1}
    //};
}

QVector<PrinterModel::MonarchOutputPort> PrinterModel::getOutputPortArray()  const
{
    return QVector<PrinterModel::MonarchOutputPort>();
}

void PrinterModel::inputDataReady(Payload data, int index)
{
    if(index == 0) qDebug() << data;
}

Payload PrinterModel::getOutputData(int)
{
    return Payload();
}







