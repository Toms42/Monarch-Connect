#ifndef FLOWLIST_H
#define FLOWLIST_H

#include <QObject>
#include "Tunnelling/flowscenewrapper.h"
#include <QDebug>

using namespace QtNodes;

class FlowList : public QObject
{
    Q_OBJECT


public:
    explicit FlowList(QObject *parent = nullptr);

    void registerFlowWrapper(FlowSceneWrapper *wrapper);
    void unregisterFlowWrapper(FlowSceneWrapper *wrapper);
    void loadTopLevelFlowWrapper(QFile &file);
    void newTopLevelFlowWrapper();
    //_topLevelWrappers getter to implement hierarchyChanged() in
    //projectHierarchyInterface.cpp
    QVector<std::shared_ptr<FlowSceneWrapper>> getTopLevelWrappers();
    QJsonArray save();
    void load(QJsonArray topArray);

signals:
    void refreshWrapper(FlowSceneWrapper *newWrapper);
    void hierarchyUpdated();

public slots:
    void updateHierarchy() {
        qDebug() << "hierarchy updated";
        emit(hierarchyUpdated());
    }

private:
    QVector<std::shared_ptr<FlowSceneWrapper>> _topLevelWrappers;
    QHash<QString, QVector<FlowSceneWrapper*>> _registry;
};

#endif // FLOWLIST_H
