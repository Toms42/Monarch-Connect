#include "configwidgetinterface.h"

#include <QWidget>


ConfigWidgetInterface::ConfigWidgetInterface(QGridLayout &layout, QObject *parent)
    :QObject (parent),
      _layout(layout)
{
}

void ConfigWidgetInterface::changeWidget(QWidget *widget)
{
    auto *item = _layout.itemAtPosition(0,0);
    if(item && item->widget())
    {
        auto *widg = item->widget();
        _layout.removeWidget(item->widget());
        widg->hide();
    }
    if(widget)
    {
        _layout.addWidget(widget, 0, 0);
        widget->show();
    }
}
