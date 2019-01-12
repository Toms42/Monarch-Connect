#ifndef PRINTERMODEL_H
#define PRINTERMODEL_H

#include <QObject>
#include "Models/monarchmodel.h"
#include <nodes/NodeDataModel>

class PrinterModel : public MonarchModel
{
    Q_OBJECT

public:
    PrinterModel();
    ~PrinterModel() override;

public:
    //basic info about the node:
    QString caption() const  override;
    QString name() const  override;
    QWidget *embeddedWidget() override;

protected:
    //load/save your internal data in the node, using json.
    QJsonObject saveData() const override;
    void loadData(QJsonObject const& modelJson) const override;

    //functions to access data in/out of the node.
    void inputDataReady(Payload data, int index) override;
    Payload getOutputData(int index) override;

    //get arrays of inputs/output ports. Called only on instantiation of node.
    QVector<MonarchInputPort> getInputPortArray()  const override;
    QVector<MonarchOutputPort> getOutputPortArray()  const override;
};

#endif // PRINTERMODEL_H
