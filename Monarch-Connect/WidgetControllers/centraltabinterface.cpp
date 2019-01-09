#include "centraltabinterface.h"
#include <QLabel>
#include <QDebug>
#include <nodes/FlowView>

using namespace QtNodes;

CentralTabInterface::CentralTabInterface(QTabWidget &widget, QObject *parent)
    : QObject(parent),
      _tabWidget(widget),
      _tabs()
{
    _tabWidget.clear();
    QLabel* homeWidget = new QLabel("Welcome!");
    tab_t home = {QUuid::createUuid(), homeWidget, TABTYPE::HOME, {0}};
    _tabWidget.addTab(home.widget, "home");
    _tabs.append(home);
    connect(&_tabWidget, &QTabWidget::tabCloseRequested,
            this, &CentralTabInterface::tabCloseRequested);
}
CentralTabInterface::~CentralTabInterface()
{
    _tabWidget.clear();
    for(auto tab : _tabs)
    {
        delete tab.widget;
    }
}

void CentralTabInterface::saveEvent()
{
    int activeIndex = _tabWidget.currentIndex();
    tab_t activeTab = _tabs[activeIndex];
    if(activeTab.type == TABTYPE::FLOW)
    {
        qDebug() << "saving current scene";
        //save flow:
        activeTab.data.flowScene->save();
        QString newName = activeTab.data.flowScene->getName();
        _tabWidget.setTabText(activeIndex, newName);
    }
}

void CentralTabInterface::reloadNames()
{
    for(int i = 0; i < _tabWidget.count(); i++)
    {
        tab_t tab = _tabs[i];
        if(tab.type == TABTYPE::FLOW)
        {
            QString newName = tab.data.flowScene->getName();
            _tabWidget.setTabText(i, newName);
        }
    }
}

void CentralTabInterface::addTab(FlowSceneWrapper *wrap)
{
    tab_t newTab;
    newTab.id = wrap->getID();

    for(int i = 0; i < _tabs.size(); i++)
    {
        auto tab = _tabs[i];
        if(tab.id == newTab.id)
        {
            _tabWidget.setCurrentIndex(i);
            return;
        }
    }

    FlowView *view = new FlowView(wrap->getFlowScene());
    newTab.widget = view;
    newTab.type = TABTYPE::FLOW;
    newTab.data.flowScene = wrap;
    _tabs.append(newTab);
    _tabWidget.addTab(newTab.widget, wrap->getName());
    _tabWidget.setCurrentIndex(_tabWidget.count() - 1);
}

void CentralTabInterface::addTab(QUuid id, QWidget *widget, QString name)
{
    tab_t newTab;
    newTab.id = id;
    for(int i = 0; i < _tabs.size(); i++)
    {
        auto tab = _tabs[i];
        if(tab.id == newTab.id)
        {
            _tabWidget.setCurrentIndex(i);
            return;
        }
    }
    newTab.widget = widget;
    newTab.type = TABTYPE::OTHER;
    _tabs.append(newTab);
    _tabWidget.addTab(newTab.widget, name);
    _tabWidget.setCurrentIndex(_tabWidget.count() - 1);
}

void CentralTabInterface::tabCloseRequested(int index)
{
    tab_t tab = _tabs[index];
    _tabs.remove(index);
    _tabWidget.removeTab(index);

    delete tab.widget;
}
