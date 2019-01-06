#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Common/project.h"
#include "Common/taglist.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto tagTree = ui->widget_tagTree;
    auto &tagList = Project::getInstance().getTagList();
    tagTreeInterface = new TagTreeInterface(*tagTree, tagList, this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tagTreeInterface;
}
