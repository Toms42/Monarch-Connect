#include "Common/config.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QObject>
#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/DataModelRegistry>
#include <nodes/ConnectionStyle>
#include <nodes/FlowSceneModel>
#include <nodes/DataFlowScene>
#include <nodes/DataFlowModel>
#include <QPixmap>
#include <QSplashScreen>
#include <QThread>

#include "Models/models.hpp"

#include "Style/DarkStyle.h"
#include "Style/framelesswindow/windowdragger.h"
#include "Style/framelesswindow/framelesswindow.h"

using QtNodes::DataModelRegistry;
using QtNodes::FlowScene;
using QtNodes::FlowView;
using QtNodes::ConnectionStyle;
using QtNodes::FlowSceneModel;
using QtNodes::DataFlowScene;
using QtNodes::DataFlowModel;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //start splash
    QPixmap splashLogo(":splash.png");
    QSplashScreen splash(splashLogo);
    splash.show();
    QThread::sleep(4); //lol look at the splash


    //setup project:
    Project::getInstance().setup();

    //load stylesheet:
    a.setStyle(new DarkStyle);

    FramelessWindow framelessWindow;
    framelessWindow.setWindowTitle("Monarch");
    framelessWindow.setWindowIcon(QIcon(":icon.png")); //for window
    MainWindow w(&framelessWindow);
    framelessWindow.setContent(&w);
    QObject::connect(&w, &MainWindow::updateTitle,
                     &framelessWindow, &FramelessWindow::setWindowTitle);
    framelessWindow.show();
    a.setWindowIcon(QIcon(":icon.png")); //for taskbar

    splash.finish(&framelessWindow);
    return a.exec();
}
