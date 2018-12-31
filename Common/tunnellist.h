#ifndef TUNNELLIST_H
#define TUNNELLIST_H

#include <QObject>

class TunnelList : public QObject
{
    Q_OBJECT
public:
    explicit TunnelList(QObject *parent = nullptr);
    ~TunnelList();

signals:

public slots:
};

#endif // TUNNELLIST_H
