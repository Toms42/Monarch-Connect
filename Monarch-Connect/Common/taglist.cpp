#include "taglist.h"
#include <QDebug>
#include "project.h"

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
    //qDebug() << "inserting";
    auto tag = type->getTag();
    auto tagID = type->getTagID();

    if(_tagTypes.contains(tagID) || _tags.contains(tag))
    {
        //bad to assume syncronization?
        //tbh should just remove tagID's and rely on tag names...
        _tagTypes.remove(tagID);
        _tags.remove(tag);
        qDebug() << "removed older item";
    }
    _tags.insert(tag, tagID);
    _tagTypes.insert(tagID, std::move(type));

    qDebug() << "inserted";
    emit(added(tag));
    Project::getInstance().updateAllPayloads();
}

void TagList::remove(QUuid tagID)
{
    if(_tagTypes.contains(tagID))
    {
        auto tag = getTag(tagID);
        _tags.remove(tag);
        _tagTypes.remove(tagID);
        emit(removed(tag));
    }
}
void TagList::remove(QString tag)
{
    if(_tags.contains(tag))
    {
        auto tagID = getTagID(tag);
        _tags.remove(tag);
        _tagTypes.remove(tagID);
        emit(removed(tag));
    }
}
