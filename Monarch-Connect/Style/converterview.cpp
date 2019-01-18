#include "converterview.h"

ConverterView::ConverterView(QWidget *parent) : QWidget(parent)
{
    _horizontalGroupBox = new QGroupBox(tr("Converter"), this);
    _power = new QPushButton("On/Off");
    _data = new QLineEdit();
    _status = new QLineEdit();
    _status->setReadOnly(true);
    _status->setPlaceholderText("Shows whether data is sending or not");
    _data->setReadOnly(true);
    _data->setPlaceholderText("Data");
    _status->setPlaceholderText("Status");
    QFormLayout *layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Status:")), _status);
    layout->addRow(new QLabel(tr("Data:")), _data);
    layout->addRow(_power);
    //range
    _min = new QLineEdit();
    _max = new QLineEdit();
    _min->setPlaceholderText("-1.0");
    _max->setPlaceholderText("1.0");
    _range = new QPushButton("Set sensitivity");
    layout->addRow(new QLabel(tr("Min:")), _min);
    layout->addRow(new QLabel(tr("Max:")), _max);
    layout->addRow(_range);
    _horizontalGroupBox->setLayout(layout);
    connect(_power, &QPushButton::pressed, this, &ConverterView::pressed);
    connect(_range, &QPushButton::pressed, this, &ConverterView::rangePressed);
}

void ConverterView::setData(QString data){
    _data->setPlaceholderText(data);
}

void ConverterView::setStatus(QString data){
    _status->setPlaceholderText(data);
}
