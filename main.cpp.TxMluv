#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>

#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/DataModelRegistry>
#include <nodes/ConnectionStyle>

#include "models.hpp"

using QtNodes::DataModelRegistry;
using QtNodes::FlowScene;
using QtNodes::FlowView;
using QtNodes::ConnectionStyle;

static std::shared_ptr<DataModelRegistry> registerDataModels()
{
  auto ret = std::make_shared<DataModelRegistry>();

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
    MainWindow w;

    FlowScene scene(registerDataModels());
    w.show();

    return a.exec();
}
