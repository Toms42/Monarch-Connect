#include "taglist.h"

TagList::TagList(QObject *parent)
    : QObject(parent),
      _tags(),
      _tagTypes()
{
}


std::shared_ptr<TagType> TagList::getTagType(QString tag) const
{
    auto tagID = getTagID(tag);
    return _tagTypes.value(tagID);
}

std::shared_ptr<TagType> TagList::getTagType(QUuid tagID) const
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
    type->setParent(this);
    _tags.insert(type->getTag(), type->getTagID());
    _tagTypes.insert(type->getTagID(), std::move(type));
}

void TagList::remove(QUuid tagID)
{
    _tags.remove(this->getTag(tagID));
    _tagTypes.remove(tagID);
}
