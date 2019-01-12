#include "centraltabinterface.h"
#include <QTextBrowser>
#include <QDebug>
#include <nodes/FlowView>
#include "Common/project.h"

using namespace QtNodes;

CentralTabInterface::CentralTabInterface(QTabWidget &widget, QObject *parent)
    : QObject(parent),
      _tabWidget(widget),
      _tabs()
{
    _tabWidget.clear();
    addHomeTab();
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

void CentralTabInterface::addHomeTab()
{
    QTextBrowser * homeWidget = new QTextBrowser();
    QFile html;
    html.setFileName(":home.html");
    if(html.open(QIODevice::ReadOnly))
    {
        homeWidget->setHtml(html.readAll());
        homeWidget->setOpenExternalLinks(true);
        homeWidget->setOpenLinks(true);
    }
    else
    {
        homeWidget->setText("Error loading homepage");
    }
    homeWidget->setAlignment(Qt::AlignCenter);
    tab_t home = {QUuid::createUuid(), homeWidget, TABTYPE::HOME, {0}};
    _tabWidget.addTab(home.widget, "home");
    _tabs.append(home);
}

void CentralTabInterface::saveEvent()
{
    int activeIndex = _tabWidget.currentIndex();
    if(activeIndex < 0)
    {
        Project::getInstance().save();
        return;
    }
    tab_t activeTab = _tabs[activeIndex];
    if(activeTab.type == TABTYPE::FLOW)
    {
        qDebug() << "saving current scene";
        //save flow:
        activeTab.data.flowScene->save();
        QString newName = activeTab.data.flowScene->getName();
        _tabWidget.setTabText(activeIndex, newName);
    }
    else
    {
        //save project:
        Project::getInstance().save();
    }
}

void CentralTabInterface::saveAsEvent()
{
    int activeIndex = _tabWidget.currentIndex();
    if(activeIndex < 0)
    {
        Project::getInstance().saveAs();
        return;
    }
    tab_t activeTab = _tabs[activeIndex];
    if(activeTab.type == TABTYPE::FLOW)
    {
        qDebug() << "saving current scene";
        //save flow:
        activeTab.data.flowScene->saveAs();
        QString newName = activeTab.data.flowScene->getName();
        _tabWidget.setTabText(activeIndex, newName);
    }
    else
    {
        //save project:
        Project::getInstance().saveAs();
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

void CentralTabInterface::removeTab(FlowSceneWrapper *wrap)
{
    tab_t newTab;
    newTab.id = wrap->getID();

    for(int i = 0; i < _tabs.size(); i++)
    {
        auto tab = _tabs[i];
        if(tab.id == newTab.id)
        {
            _tabs.remove(i);
            _tabWidget.removeTab(i);
            delete tab.widget;
            return;
        }
    }
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

void CentralTabInterface::clear()
{
    for(int i = 0; i < _tabWidget.count(); i++)
    {
        auto tab = _tabs[i];
        if(tab.type == TABTYPE::FLOW)
        {
            _tabs.remove(i);
            _tabWidget.removeTab(i);
            delete tab.widget;
            if(i) i--;
        }
    }
}
