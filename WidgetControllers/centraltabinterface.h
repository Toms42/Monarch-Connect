#ifndef CENTRALTABINTERFACE_H
#define CENTRALTABINTERFACE_H

#include <QObject>
#include <QTabWidget>
#include <QVector>
#include <QString>
#include "Tunnelling/flowscenewrapper.h"


class CentralTabInterface : public QObject
{
    Q_OBJECT
public:
    explicit CentralTabInterface(QTabWidget &widget, QObject *parent = nullptr);
    ~CentralTabInterface();

    void addTab(FlowSceneWrapper *wrap);
    void addTab(QUuid id, QWidget *widget, QString name);

signals:

private slots:
    void tabCloseRequested(int index);

public slots:
    void saveEvent();
    void reloadNames();

private:
    QTabWidget &_tabWidget;

    enum TABTYPE{
        FLOW,
        HOME,
        OTHER
    };

    struct tab_t{
        QUuid id;
        QWidget *widget;
        TABTYPE type;
        union{
            FlowSceneWrapper* flowScene;
        }data;
    };

    QVector<tab_t> _tabs;

};

#endif // CENTRALTABINTERFACE_H
