#include "converterview.h"

ConverterView::ConverterView(QWidget *parent) : QWidget(parent)
{
    _power = new QPushButton("On/Off");
    _data = new QLineEdit();
    _status = new QLineEdit();
    _status->setReadOnly(true);
    _status->setPlaceholderText("Shows whether data is sending or not");
    _data->setReadOnly(true);
    _data->setPlaceholderText("Data");
    _status->setPlaceholderText("Status");
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(new QLabel(tr("Status:")), 0, 0);
    layout->addWidget(_status, 0, 1);

    layout->addWidget(new QLabel(tr("Data:")), 1, 0);
    layout->addWidget(_data, 1, 1);

    layout->addWidget(_power, 2, 0);

    _minAmplitude = new QLineEdit("0.0");
    _maxAmplitude = new QLineEdit("45.0");
    _minRoll = new QLineEdit("-25.0");
    _maxRoll = new QLineEdit("25.0");
    _minDihedral = new QLineEdit("45");
    _maxDihedral = new QLineEdit("135");
    _minAngV = new QLineEdit("0");
    _maxAngV = new QLineEdit("1000");
    _glideThresh = new QLineEdit("35");

    layout->addWidget(new QLabel("Amplitude:"), 3, 0);
    layout->addWidget(_minAmplitude, 3, 1);
    layout->addWidget(_maxAmplitude, 3, 2);

    layout->addWidget(new QLabel("Roll:"), 4, 0);
    layout->addWidget(_minRoll, 4, 1);
    layout->addWidget(_maxRoll, 4, 2);

    layout->addWidget(new QLabel("Dihedral:"), 5, 0);
    layout->addWidget(_minDihedral, 5, 1);
    layout->addWidget(_maxDihedral, 5, 2);

    layout->addWidget(new QLabel("Ang. V:"), 6, 0);
    layout->addWidget(_minAngV, 6, 1);
    layout->addWidget(_maxAngV, 6, 2);

    layout->addWidget(new QLabel("Glide Thres:"), 7, 0);
    layout->addWidget(_glideThresh, 7, 1);


    this->setLayout(layout);
    connect(_power, &QPushButton::pressed, this, &ConverterView::pressed);
}

void ConverterView::setData(QString data){
    _data->setPlaceholderText(data);
}

void ConverterView::setStatus(QString data){
    _status->setPlaceholderText(data);
}
