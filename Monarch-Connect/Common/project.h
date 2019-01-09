#ifndef PROJECT_H
#define PROJECT_H

#include <QObject>
#include <QFileInfo>
#include "Common/taglist.h"
#include "Common/flowlist.h"
#include <nodes/DataModelRegistry>

using namespace QtNodes;

class Project : public QObject
{
    Q_OBJECT
public:

    static Project &getInstance(){
        static Project instance;
        return instance;
    }

    void save();
    void save(QFile path);
    void load(QFile path);

    TagList &getTagList();
    FlowList &getFlowList();
    std::shared_ptr<DataModelRegistry> getModelRegistry();

signals:

public slots:

private:
    explicit Project(QObject *parent = nullptr);
    Project(const Project&) = delete;
    Project &operator=(const Project&) = delete;

private:
    std::shared_ptr<DataModelRegistry> _registry; //(not saved)
    TagList _tags;
    FlowList _flows;
    QFile _path;
};

#endif // PROJECT_H
