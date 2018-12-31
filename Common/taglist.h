#ifndef TAGLIST_H
#define TAGLIST_H

#include <QObject>
#include <QHash>
#include "Common/tagtype.h"

class TagList : public QObject
{
    Q_OBJECT
public:
    explicit TagList(QObject *parent = nullptr);
    ~TagList();
    TagType &getTagType(QString tag);
    TagType &getTagType(QUuid tagID);

    QUuid getTagID(QString tag);
    QString getTag(QUuid tagID);

    void insert(TagType &type);
    void remove(QUuid tagID);

private:
    QHash<QString, QUuid> _tags;
    QHash<QUuid, TagType> _tagTypes;

signals:

public slots:
};

#endif // TAGLIST_H
