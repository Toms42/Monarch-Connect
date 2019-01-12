#include "printermodel.h"
#include "QDebug"
#include "Common/project.h"
#include "Common/taglist.h"
#include "functional"


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

using namespace std::placeholders;
//get arrays of inputs/output ports. Called only on instantiation of node.
QVector<PrinterModel::MonarchInputPort> PrinterModel::getInputPortArray()  const
{
    QVector<PrinterModel::MonarchInputPort> inArray;
    //std::function<void(int,Payload)> f;
    //f = std::bind(&PrinterModel::printData, this, _1, _2);

    //MonarchInputPort in1 = {PortType::STREAM, std::bind(&PrinterModel::printData, this, _1, _2), -1};

}

QVector<PrinterModel::MonarchOutputPort> PrinterModel::getOutputPortArray()  const
{
    return QVector<PrinterModel::MonarchOutputPort>();
}

void PrinterModel::printData(int idx, Payload payload)
{
    qDebug() << payload;
}











