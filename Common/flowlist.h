#ifndef FLOWLIST_H
#define FLOWLIST_H

#include <QObject>

class FlowList : public QObject
{
    Q_OBJECT
public:
    explicit FlowList(QObject *parent = nullptr);
    ~FlowList();

signals:

public slots:
};

#endif // FLOWLIST_H
