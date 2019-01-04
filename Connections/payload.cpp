#include "payload.h"
#include "Common/taglist.h"
#include "Common/tagtype.h"
#include "Common/project.h"
#include <memory>

Payload::Payload(QUuid tagID, int nFields, QVector<long> vals, QObject *parent)
    : QObject (parent),
      _vals(nFields)
{
    _tagID = tagID;
    _nFields = nFields;
    _vals = vals;
}

Payload::Payload(QUuid tagID, long val, QObject *parent)
    :QObject (parent),
      _vals(1)
{
    _tagID = tagID;
    _nFields = 1;
    _vals[0] = val;
}

Payload::Payload(Payload &payload)
    : QObject (payload.parent()),
      _vals(payload._vals)
{
    _tagID = payload._tagID;
    _nFields = payload._nFields;
}

QUuid Payload::getTagID()
{
    return _tagID;
}
int Payload::nFields()
{
    return _nFields;
}

QString Payload::getFieldName(int field)
{
    const TagList& taglist = Project::getInstance().getTagList();
    std::shared_ptr<TagType> tagtype = taglist.getTagType(_tagID);
    return tagtype->getFieldName(field);
}
QString Payload::getFieldUnit(int field)
{
    const TagList& taglist = Project::getInstance().getTagList();
    std::shared_ptr<TagType> tagtype = taglist.getTagType(_tagID);
    return tagtype->getFieldUnit(field);
}
double Payload::getFieldScalar(int field)
{
    const TagList& taglist = Project::getInstance().getTagList();
    std::shared_ptr<TagType> tagtype = taglist.getTagType(_tagID);
    return tagtype->getFieldScalar(field);
}

long Payload::getValDirect(int field)
{
    if(field < 0 || field >= _nFields) return 0;
    return _vals[field];
}

double Payload::getVal(int field)
{
    if(field < 0 || field >= _nFields) return 0;
    return static_cast<double>(_vals[field])*getFieldScalar(field);
}
