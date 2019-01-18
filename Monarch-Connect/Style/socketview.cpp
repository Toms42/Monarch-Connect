#include "socketview.h"

SocketView::SocketView(QWidget *parent) : QWidget(parent)
{
    _horizontalGroupBox = new QGroupBox(tr("Configure connection"), this);
    _confirm = new QPushButton("Connect");
    _host = new QLineEdit();
    _port = new QLineEdit();
    _status = new QLineEdit();
    _status->setReadOnly(true);
    _host->setPlaceholderText("Type host here");
    _port->setPlaceholderText("Type port here");
    _status->setPlaceholderText("Status will pop up");
    QFormLayout *layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Host:")), _host);
    layout->addRow(new QLabel(tr("Port:")), _port);
    layout->addRow(new QLabel(tr("Status:")), _status);
    layout->addRow(new QLabel(tr("Connect:")), _confirm);
    _horizontalGroupBox->setLayout(layout);
    connect(_confirm, &QPushButton::pressed, this, &SocketView::pressed);
}

void SocketView::setStatus(QString status){
    _status->setPlaceholderText(status);
}
