#ifndef GAMEPADVIEW_H
#define GAMEPADVIEW_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QList>
#include <QLabel>
#include "style/xyvis.h"

class GamepadView : public QWidget
{
    Q_OBJECT
public:
    explicit GamepadView(QWidget *parent = nullptr);

private:
    XYvis *_leftVis = nullptr;
    XYvis *_rightVis = nullptr;
    QComboBox *_selector = nullptr;
    QPushButton *_refreshButton = nullptr;
    QPushButton *_setButton = nullptr;
    QLabel *_connectedID = nullptr;
    QLabel *_connectedName = nullptr;

public:
    XYvis *leftVis() {return _leftVis;}
    XYvis *rightVis() {return _rightVis;}
    QComboBox *selector() {return _selector;}
    QPushButton *refreshButton() {return _refreshButton;}
    QPushButton *setButton() {return _setButton;}
    QLabel *connectedID() {return _connectedID;}
    QLabel *connectedName() {return _connectedName;}
signals:
    void refreshPressed();
    void setPressed();

public slots:
};

#endif // GAMEPADVIEW_H
