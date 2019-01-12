#ifndef PRINTERMODEL_H
#define PRINTERMODEL_H

#include "Models/monarchmodel.h"

class PrinterModel : public MonarchModel
{
public:
    PrinterModel();

public:
    //basic info about the node:
    virtual QString caption() const  override;
    virtual QString name() const  override;
    QWidget *embeddedWidget() override;

protected:
    //load/save your internal data in the node, using json.
    virtual QJsonObject saveData() const override;
    virtual void loadData(QJsonObject const& modelJson) const override;

    //get arrays of inputs/output ports. Called only on instantiation of node.
    virtual QVector<MonarchInputPort> getInputPortArray()  const override;
    virtual QVector<MonarchOutputPort> getOutputPortArray()  const override;

public:
    void printData(int idx, Payload payload);
};

#endif // PRINTERMODEL_H
