#ifndef PROJECT_H
#define PROJECT_H

#include <QObject>
#include <QFileInfo>
#include "Common/taglist.h"
#include "Common/flowlist.h"
#include <nodes/DataModelRegistry>
#include <QDir>

using namespace QtNodes;

class Project : public QObject
{
    Q_OBJECT
public:

    static Project &getInstance(){
        static Project instance;
        return instance;
    }

    TagList &getTagList();
    FlowList &getFlowList();
    std::shared_ptr<DataModelRegistry> getModelRegistry();

    QByteArray saveToMemory();
    void loadFromMemory(QByteArray file);
    QDir getPath();

public slots:
    void save();
    void saveAs();
    void open();

signals:
    void nameUpdated(QString name);

public slots:

private:
    explicit Project(QObject *parent = nullptr);
    Project(const Project&) = delete;
    Project &operator=(const Project&) = delete;

private:
    std::shared_ptr<DataModelRegistry> _registry; //(not saved)
    TagList _tags;
    FlowList _flows;
    QString _name;
    QFile _file;
    bool _isSaved = false;
};

#endif // PROJECT_H
