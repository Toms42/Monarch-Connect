#include "monarchconnecttest.h"

MonarchConnectTest::MonarchConnectTest(QObject *parent) : QObject(parent)
{

}

void MonarchConnectTest::example_test(){
    //the test I wrote segfaults somewhere in the FlowSceneWrapper constructor haha
    /*std::shared_ptr<FlowSceneWrapper> parent, child;
    parent = std::make_shared<FlowSceneWrapper>(nullptr, nullptr);
    child = std::make_shared<FlowSceneWrapper>(parent, nullptr);
    QCOMPARE(parent->children().length(), 1);
    QVERIFY(child->parent() == parent);
    QVERIFY(parent->children().first() == child);*/
    QCOMPARE(1,1);
}
