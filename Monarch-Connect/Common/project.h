#ifndef PROJECT_H
#define PROJECT_H

#include <QObject>
#include <QFileInfo>
#include "Common/taglist.h"
#include "Common/flowlist.h"
#include "Connections/connectionstats.h"
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

    void setup();

    TagList &getTagList();
    FlowList &getFlowList();
    std::shared_ptr<DataModelRegistry> getModelRegistry();

    QByteArray saveToMemory();
    void loadFromMemory(QByteArray file);
    QDir getDir();

public slots:
    void save();
    void saveAs();
    void open();

signals:
    //from project:
    void nameUpdated(QString name);
    void clearAll();

    //forwarded from flowscenewrappers:
    void newConfigWidget(QWidget *widget);
    void newConnectionStats(ConnectionStats::stats *stats);

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
