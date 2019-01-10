#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Common/project.h"
#include "Common/taglist.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //setup tagTreeInterface:
    auto tagTree = ui->widget_tagTree;
    auto &tagList = Project::getInstance().getTagList();
    tagTreeInterface = new TagTreeInterface(*tagTree, tagList, this);

    //setup centralTabInterface:
    centralTabInterface = new CentralTabInterface(*ui->tabWidget, this);
    connect(ui->actionSave, &QAction::triggered,
            centralTabInterface, &CentralTabInterface::saveEvent);
    connect(ui->actionSave_As, &QAction::triggered,
            centralTabInterface, &CentralTabInterface::saveAsEvent);
    connect(&Project::getInstance().getFlowList(), &FlowList::hierarchyUpdated,
            centralTabInterface, &CentralTabInterface::reloadNames);


    //setup projectHierarchyInterface:
    auto &flows = Project::getInstance().getFlowList();
    projectHierarchyInterface = new ProjectHierarchyInterface(flows,
                                                              *ui->projectTree,
                                                              *centralTabInterface,
                                                              this);

    //connect commands to project:
    connect(ui->actionOpen, &QAction::triggered,
            &Project::getInstance(), &Project::open);
    connect(ui->actionSave_Project, &QAction::triggered,
            &Project::getInstance(), &Project::save);
    connect(ui->actionSave_Project_As, &QAction::triggered,
            &Project::getInstance(), &Project::saveAs);
    connect(&Project::getInstance(), &Project::nameUpdated,
            this, &MainWindow::updateTitle);


}

MainWindow::~MainWindow()
{
    delete projectHierarchyInterface;
    delete centralTabInterface;
    delete tagTreeInterface;
    delete ui;
}
