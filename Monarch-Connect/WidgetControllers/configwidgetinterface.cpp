#include "configwidgetinterface.h"

#include <QWidget>


ConfigWidgetInterface::ConfigWidgetInterface(QGridLayout &layout, QObject *parent)
    :QObject (parent),
      _layout(layout)
{
}

ConfigWidgetInterface::~ConfigWidgetInterface()
{
    QWidget *widg = _layout.itemAtPosition(0,0)->widget();
    if(widg)
    {
        _layout.removeWidget(widg);
        widg->hide();
    }
}

void ConfigWidgetInterface::changeWidget(QWidget *widget)
{
    auto *item = _layout.itemAtPosition(0,0);
    if(item && item->widget())
    {
        _layout.removeWidget(item->widget());
        item->widget()->hide();
    }
    if(widget)
    {
        _layout.addWidget(widget, 0, 0);
        widget->show();
    }
}
