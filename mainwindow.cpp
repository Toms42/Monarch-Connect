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

    //setup projectHierarchyInterface:
    auto &flows = Project::getInstance().getFlowList();
    projectHierarchyInterface = new ProjectHierarchyInterface(flows,
                                                              *ui->projectTree,
                                                              *centralTabInterface,
                                                              this);
    connect(ui->button_newTopFlow, &QPushButton::pressed,
            projectHierarchyInterface, &ProjectHierarchyInterface::addTopFlow);
    connect(ui->button_loadTopFlow, &QPushButton::pressed,
            projectHierarchyInterface, &ProjectHierarchyInterface::loadTopFlow);
    connect(ui->button_deleteTopFlow, &QPushButton::pressed,
            projectHierarchyInterface, &ProjectHierarchyInterface::deleteTopFlow);


}

MainWindow::~MainWindow()
{
    delete projectHierarchyInterface;
    delete centralTabInterface;
    delete tagTreeInterface;
    delete ui;
}
