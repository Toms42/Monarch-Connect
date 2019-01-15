#ifndef FLOWSCENEWRAPPER_H
#define FLOWSCENEWRAPPER_H

#include <QObject>
#include <memory>
#include <nodes/DataFlowScene>
#include <QFile>
#include "tunnellist.h"
#include "Connections/connectionstats.h"

using namespace QtNodes;

class FlowSceneWrapper : public QObject
{
    Q_OBJECT
public:
    //will load from file
    explicit FlowSceneWrapper(std::shared_ptr<FlowSceneWrapper> parent, QFile &file, QObject *parentObj = nullptr);

    //will create a new *temporary* flowscene (unsaved).
    explicit FlowSceneWrapper(std::shared_ptr<FlowSceneWrapper> parent, QObject *parentObj= nullptr);
    ~FlowSceneWrapper();

public:
    void save();
    void saveAs();
    void reload();

    std::shared_ptr<FlowSceneWrapper> parent() const;
    QVector<std::shared_ptr<FlowSceneWrapper>> &children();
    bool isRoot() const {return _parent == nullptr;}

    void addChild(std::shared_ptr<FlowSceneWrapper> wrapper);
    void removeChild(std::shared_ptr<FlowSceneWrapper> wrapper);

    const TunnelList &getExternalTunnels() const;
    DataFlowScene *getFlowScene();

    bool operator==(const FlowSceneWrapper &other)
    { return _uniqueID == other._uniqueID;}

    QString getFile() const;

    QUuid getID() const {return _uniqueID;}
    QString getName() const {return _name;}

signals:
    void updated(FlowSceneWrapper *newWrapper);
    void saved();
    void hierarchyChanged();

public slots:
    void refresh(FlowSceneWrapper *newWrapper);
    void sceneChanged();
    void selectionChanged();
    void sendStats();

private:
    QUuid _uniqueID;
    QString _name = "~New Flow";
    bool _isSaved = false;
    bool _blocking = false; //blocks sceneChanged signal to avoid loops
    DataFlowScene _scene;
    QFile _file;
    std::shared_ptr<FlowSceneWrapper> _parent = nullptr;
    ConnectionStats *_stats = nullptr;

    //these things are handled by nodes inside the scene:
    QVector<std::shared_ptr<FlowSceneWrapper>> _children;
    TunnelList _internalTunnels;
    TunnelList _externalTunnels;

};

#endif // FLOWSCENEWRAPPER_H
