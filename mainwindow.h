#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <nodes/FlowScene>

namespace Ui {
class MainWindow;
}
using QtNodes::FlowScene;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void
    setScene(FlowScene *scene);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
