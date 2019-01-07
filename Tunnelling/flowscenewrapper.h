#ifndef FLOWSCENEWRAPPER_H
#define FLOWSCENEWRAPPER_H

#include <QObject>
#include <memory>
#include <nodes/DataFlowScene>
#include <QFile>
#include "Common/tunnellist.h"

using namespace QtNodes;

class FlowSceneWrapper : public QObject
{
    Q_OBJECT
public:
    //will load from file
    explicit FlowSceneWrapper(FlowSceneWrapper *parent, QFile &file, QObject *parentObj = nullptr);

    //will create a new *temporary* flowscene (unsaved).
    explicit FlowSceneWrapper(FlowSceneWrapper *parent, QObject *parentObj= nullptr);
    ~FlowSceneWrapper();

public:
    void save();
    void save(QFile &file);
    void reload();

    FlowSceneWrapper *parent() const;
    QVector<FlowSceneWrapper*> &children();
    bool isRoot() const {return _parent == nullptr;}

    void addChild(FlowSceneWrapper* wrapper);
    void removeChild(FlowSceneWrapper *wrapper);

    const TunnelList &getExternalTunnels() const;
    DataFlowScene *getFlowScene();

    bool operator==(const FlowSceneWrapper &other)
    { return _uniqueID == other._uniqueID;}

    QString getFile() const;
signals:
    void updated(FlowSceneWrapper *newWrapper);
    void saved();
    void hierarchyChanged();

public slots:
    void refresh(FlowSceneWrapper *newWrapper);
    void sceneChanged();

private:
    QUuid _uniqueID;
    QString _name = "~New Flow";
    bool _isSaved = false;
    bool _blocking = false; //blocks sceneChanged signal to avoid loops
    DataFlowScene _scene;
    QFile _file;
    FlowSceneWrapper *_parent;

    //these things are handled by nodes inside the scene:
    QVector<FlowSceneWrapper*> _children;
    TunnelList _internalTunnels;
    TunnelList _externalTunnels;

};

#endif // FLOWSCENEWRAPPER_H
