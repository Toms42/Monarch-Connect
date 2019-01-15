#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <nodes/FlowScene>
#include "WidgetControllers/tagtreeinterface.h"
#include "WidgetControllers/centraltabinterface.h"
#include "WidgetControllers/projecthierarchyinterface.h"
#include "WidgetControllers/configwidgetinterface.h"
#include "WidgetControllers/statswidgetcontroller.h"
#include <QString>

namespace Ui {
class MainWindow;
}
using QtNodes::FlowScene;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void updateTitle(const QString &title);

private:
    Ui::MainWindow *ui;
    TagTreeInterface *tagTreeInterface;
    CentralTabInterface *centralTabInterface;
    ProjectHierarchyInterface *projectHierarchyInterface;
    ConfigWidgetInterface *configWidgetInterface;
    StatsWidgetController *statsWidgetController;

};

#endif // MAINWINDOW_H
