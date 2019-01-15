#ifndef CONFIGWIDGETINTERFACE_H
#define CONFIGWIDGETINTERFACE_H

#include <QObject>
#include <QLayout>

class ConfigWidgetInterface : public QObject
{
    Q_OBJECT
public:
    explicit ConfigWidgetInterface(QGridLayout &layout, QObject *parent = nullptr);
signals:


public slots:
    void changeWidget(QWidget *widget);

private:
    QGridLayout& _layout;
};

#endif // CONFIGWIDGETINTERFACE_H
