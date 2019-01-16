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
    connect(ui->button_newFlow, &QPushButton::pressed,
            projectHierarchyInterface, &ProjectHierarchyInterface::addTopFlow);
    connect(ui->button_deleteFlow, &QPushButton::pressed,
            projectHierarchyInterface, &ProjectHierarchyInterface::deleteTopFlow);

    //connect commands to project:
    connect(ui->actionOpen, &QAction::triggered,
            &Project::getInstance(), &Project::open);
    connect(ui->actionSave_Project, &QAction::triggered,
            &Project::getInstance(), &Project::save);
    connect(ui->actionSave_Project_As, &QAction::triggered,
            &Project::getInstance(), &Project::saveAs);
    connect(&Project::getInstance(), &Project::nameUpdated,
            this, &MainWindow::updateTitle);
    connect(&Project::getInstance(), &Project::clearAll,
            centralTabInterface, &CentralTabInterface::clear);

    //setup configwidgetinterface:
    configWidgetInterface = new ConfigWidgetInterface(*ui->config_layout, this);
    connect(&Project::getInstance(), &Project::newConfigWidget,
            configWidgetInterface, &ConfigWidgetInterface::changeWidget);

    //setup statsWidgetController:
    QTreeWidget *streamExplorer = ui->treeWidget_5;
    statsWidgetController = new StatsWidgetController(streamExplorer,this);
    connect(&Project::getInstance(), &Project::newConnectionStats,
            statsWidgetController, &StatsWidgetController::changeView);

    //setup console
    QPlainTextEdit *plainText = ui->plainTextEdit;
    console = new Console(plainText, this);
    connect(&Project::getInstance(), &Project::print,
            console, &Console::changeOutput);

}

MainWindow::~MainWindow()
{
    delete projectHierarchyInterface;
    delete centralTabInterface;
    delete tagTreeInterface;
    delete ui;
    delete configWidgetInterface;
    delete statsWidgetController;
    delete console;
}
