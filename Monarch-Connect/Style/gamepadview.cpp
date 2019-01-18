#include "gamepadview.h"
#include <QFormLayout>
#include <QLabel>

GamepadView::GamepadView(QWidget *parent) : QWidget(parent)
{
    _leftVis = new XYvis(this);
    _rightVis = new XYvis(this);
    _selector = new QComboBox(this);
    _refreshButton = new QPushButton("Refresh List");
    _setButton = new QPushButton("Set Controller");
    _connectedID = new QLabel("N/A");
    _connectedName = new QLabel("N/A");

    connect(_refreshButton, &QPushButton::pressed,
            this, &GamepadView::refreshPressed);
    connect(_setButton, &QPushButton::pressed,
            this, &GamepadView::setPressed);

    QFormLayout *layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Refresh:")), _refreshButton);
    layout->addRow(new QLabel(tr("Gamepads:")), _selector);
    layout->addRow(new QLabel(tr("Set:")), _setButton);
    layout->addRow(new QLabel(tr("Connected ID:")), _connectedID);
    layout->addRow(new QLabel(tr("Connected Name:")), _connectedName);
    layout->addRow(_leftVis, _rightVis);
    this->setLayout(layout);
}
