#include "taglist.h"
#include <QDebug>

TagList::TagList(QObject *parent)
    : QObject(parent),
      _tags(),
      _tagTypes()
{
}


std::shared_ptr<const TagType> TagList::getTagType(QString tag) const
{
    auto tagID = getTagID(tag);
    return _tagTypes.value(tagID);
}

std::shared_ptr<const TagType> TagList::getTagType(QUuid tagID) const
{
    return _tagTypes.value(tagID);
}

QUuid TagList::getTagID(QString tag) const
{
    return _tags.value(tag);
}

QString TagList::getTag(QUuid tagID) const
{
    return _tagTypes.value(tagID)->getTag();
}

void TagList::insert(std::unique_ptr<TagType> type)
{
    qDebug() << "inserting";
    type->setParent(this);
    _tags.insert(type->getTag(), type->getTagID());
    auto tagID = type->getTagID();
    _tagTypes.insert(tagID, std::move(type));
    qDebug() << "inserted";
}

void TagList::remove(QUuid tagID)
{
    _tags.remove(this->getTag(tagID));
    _tagTypes.remove(tagID);
}
