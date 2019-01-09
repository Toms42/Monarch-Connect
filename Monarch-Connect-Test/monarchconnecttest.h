#ifndef MONARCHCONNECTTEST_H
#define MONARCHCONNECTTEST_H

#include <QObject>
#include <QtGui>
#include <QtTest/QTest>
#include "flowscenewrapper.h"

class MonarchConnectTest : public QObject
{
    Q_OBJECT
public:
    explicit MonarchConnectTest(QObject *parent = nullptr);

signals:

private slots:
    void example_test();
};

#endif // MONARCHCONNECTTEST_H
