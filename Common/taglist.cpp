#include "taglist.h"

TagList::TagList(QObject *parent)
    : QObject(parent),
      _tags(QHash<QString, QUuid>()),
      _tagTypes(QHash<QUuid, TagType>())
{
}


TagType &TagList::getTagType(QString tag)
{

}
TagType &TagList::getTagType(QUuid tagID)
{

}
QUuid TagList::getTagID(QString tag)
{

}

QUuid TagList::insert(TagType &type)
{

}
bool TagList::remove(QUuid tagID)
{

}
