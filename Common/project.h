#ifndef PROJECT_H
#define PROJECT_H

#include <QObject>
#include <QFileInfo>
#include "Common/taglist.h"
#include "Common/tunnellist.h"
#include "Common/flowlist.h"

class Project : public QObject
{
    Q_OBJECT
public:

    static Project &getInstance(){
        static Project instance;
        return instance;
    }

    void save();
    void save(QFileInfo path);
    void load(QFileInfo path);

    TagList &getTagList();
    TunnelList &getTunnelList();
    FlowList &getFlowList();

signals:

public slots:

private:
    explicit Project(QObject *parent = nullptr);
    ~Project();
    Project(const Project&) = delete;
    Project &operator=(const Project&) = delete;

private:
    TagList _tags;
    TunnelList _tunnels;
    FlowList _flows;
    QFileInfo _path;
};

#endif // PROJECT_H
