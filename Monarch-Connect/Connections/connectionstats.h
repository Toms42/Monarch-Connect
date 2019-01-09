#ifndef CONNECTIONSTATS_H
#define CONNECTIONSTATS_H

#include <QObject>

class ConnectionStats : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionStats(QObject *parent = nullptr);

signals:

public slots:
};

#endif // CONNECTIONSTATS_H
