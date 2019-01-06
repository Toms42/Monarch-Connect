#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <nodes/FlowScene>
#include "WidgetControllers/tagtreeinterface.h"

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


private:
    Ui::MainWindow *ui;
    TagTreeInterface *tagTreeInterface;
};

#endif // MAINWINDOW_H
