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
    _horizontalGroupBox->setLayout(layout);
    connect(_power, &QPushButton::pressed, this, &ConverterView::pressed);
}

void ConverterView::setData(QString data){
    _data->setPlaceholderText(data);
}

void ConverterView::setStatus(QString data){
    _status->setPlaceholderText(data);
}
