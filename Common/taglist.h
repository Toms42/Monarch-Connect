#ifndef TAGLIST_H
#define TAGLIST_H

#include <QObject>
#include <QHash>
#include <QUuid>
#include "Common/tagtype.h"
#include <memory>

class TagList : public QObject
{
    Q_OBJECT
public:
    explicit TagList(QObject *parent = nullptr);
    std::shared_ptr<TagType> getTagType(QString tag) const;
    std::shared_ptr<TagType> getTagType(QUuid tagID) const;

    QUuid getTagID(QString tag) const;
    QString getTag(QUuid tagID) const;

    void insert(std::unique_ptr<TagType> type);
    void remove(QUuid tagID);

private:
    QHash<QString, QUuid> _tags;
    QHash<QUuid, std::shared_ptr<TagType>> _tagTypes;

signals:

public slots:
};

#endif // TAGLIST_H
