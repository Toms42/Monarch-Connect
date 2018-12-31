#include "taglist.h"

TagList::TagList(QObject *parent)
    : QObject(parent),
      _tags(QHash<QString, QUuid>()),
      _tagTypes(QHash<QUuid, TagType>())
{
}


TagType &TagList::getTagType(QString tag)
{
    return _tagTypes[this->getTagID(tag)];
}

TagType &TagList::getTagType(QUuid tagID)
{
    return _tagTypes[tagID];
}

QUuid TagList::getTagID(QString tag)
{
    return _tags[tag];
}

QString TagList::getTag(QUuid tagID)
{
    return _tagTypes[tagID].getTag();
}

void TagList::insert(TagType &type)
{
    _tags.insert(type.getTag(), type.getTagID());
    _tagTypes.insert(type.getTagID(), type);
}

void TagList::remove(QUuid tagID)
{
    _tags.remove(this->getTag(tagID));
    _tagTypes.remove(tagID);
}
