#include "Common/config.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>

#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/DataModelRegistry>
#include <nodes/ConnectionStyle>
#include <nodes/FlowSceneModel>
#include <nodes/DataFlowScene>
#include <nodes/DataFlowModel>

#include "models.hpp"

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


static std::shared_ptr<DataModelRegistry> registerDataModels()
{
    auto ret = Project::getInstance().getModelRegistry();

    ret->registerModel<MyDataModel>();

    /*
     We could have more models registered.
     All of them become items in the context meny of the scene.

     ret->registerModel<AnotherDataModel>();
     ret->registerModel<OneMoreDataModel>();

   */

    return ret;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    registerDataModels();

    //load stylesheet:
    a.setStyle(new DarkStyle);

    FramelessWindow framelessWindow;
    framelessWindow.setWindowTitle("Monarch");
    MainWindow w;
    framelessWindow.setContent(&w);
    framelessWindow.show();

    return a.exec();
}
