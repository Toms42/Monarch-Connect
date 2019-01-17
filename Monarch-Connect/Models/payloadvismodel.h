#ifndef PAYLOADVISMODEL_H
#define PAYLOADVISMODEL_H

#include <QObject>
#include "QDebug"
#include "Models/monarchmodel.h"
#include <nodes/NodeDataModel>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "Common/project.h"

class PayloadVisModel:public MonarchModel{
    Q_OBJECT
private:
    QTreeWidget *_view;
    enum InPortTypes{
        PAYLOADPORT = 0,
        _NUMPORTS
    };

public:
    explicit PayloadVisModel():MonarchModel(), _view(new QTreeWidget){
        setup();
    }
    ~PayloadVisModel() override{}
public:
    //basic info about the node:
    QString caption() const  override
    {
        return "Payload Visualizer";
    }

    QString name() const  override
    {
        return "Payload Visualizer";
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
    void inputDataReady(Payload data, int index) override
    {
        qDebug() << "payload visualizer got data:";
        if(index == 0) qDebug() << data;
        //print out the data
        if(index == 0){
            _view->clear();
            //set title top level
            QTreeWidgetItem *tagtitle = new QTreeWidgetItem(_view);
            auto &l = Project::getInstance().getTagList();
            QString tag = l.getTag(data.getTagID());
            tag = "\"" + tag + "\"";
            tagtitle->setText(0,tag);
            _view->addTopLevelItem(tagtitle);
            //children with the fields of the payload
            for(int i = 0; i < data.nFields(); i++){
                QTreeWidgetItem *field = new QTreeWidgetItem(tagtitle);
                field->setText(0, "\"" + data.getFieldName(i) + "\""
                               + " : " + QString::number(data.getVal(i))
                               + " " + "\"" + data.getFieldUnit(i) + "\""
                               + " (" + QString::number(data.getFieldScalar(i)) + ")");
                tagtitle->insertChild(i, field);
            }
            tagtitle->setExpanded(true);
            _view->addTopLevelItem(tagtitle);
            _view->resizeColumnToContents(0);
        }
    }

    Payload getOutputData(int index) override
    {
        return Payload();
    }

    //get arrays of inputs/output ports. Called only on instantiation of node.
    QVector<MonarchInputPort> getInputPortArray()  const override
    {
        QVector<PayloadVisModel::MonarchInputPort> r(_NUMPORTS);
        r[PAYLOADPORT] = {PortType::PAYLOAD, QString("input payload"), -1};
        return r;
    }

    QVector<MonarchOutputPort> getOutputPortArray()  const override
    {
        return QVector<PayloadVisModel::MonarchOutputPort>();
    }
};

#endif // PAYLOADVISMODEL_H
