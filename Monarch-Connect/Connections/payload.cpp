#include "payload.h"
#include "Common/taglist.h"
#include "Common/tagtype.h"
#include "Common/project.h"
#include <memory>
#include <math.h>

Payload::Payload(QUuid tagID, int nFields, QVector<double> vals)
    : _vals(nFields)
{
    _tagID = tagID;
    _nFields = nFields;
    _vals = vals;
}

Payload::Payload(QUuid tagID, double val)
   : _vals(1)
{
    _tagID = tagID;
    _nFields = 1;
    _vals[0] = val;
}

Payload::Payload()
    : _vals(0)
{
}

QUuid Payload::getTagID() const
{
    return _tagID;
}
int Payload::nFields() const
{
    return _nFields;
}

QString Payload::getFieldName(int field) const
{
    const TagList& taglist = Project::getInstance().getTagList();
    std::shared_ptr<const TagType> tagtype = taglist.getTagType(_tagID);
    return tagtype->getFieldName(field);
}
QString Payload::getFieldUnit(int field) const
{
    const TagList& taglist = Project::getInstance().getTagList();
    std::shared_ptr<const TagType> tagtype = taglist.getTagType(_tagID);
    return tagtype->getFieldUnit(field);
}
double Payload::getFieldScalar(int field) const
{
    const TagList& taglist = Project::getInstance().getTagList();
    std::shared_ptr<const TagType> tagtype = taglist.getTagType(_tagID);
    return tagtype->getFieldScalar(field);
}

long Payload::getValDirect(int field) const
{
    if(field < 0 || field >= _nFields) return 0;
    return static_cast<long>(round(_vals[field] * getFieldScalar(field)));
}

double Payload::getVal(int field) const
{
    if(field < 0 || field >= _nFields) return 0;
    return static_cast<double>(_vals[field]);
}

QString Payload::toString() const
{
    auto &l = Project::getInstance().getTagList();
    QString tag = l.getTag(this->getTagID());
    QString out;
    out = out + "\"" + tag + "\"" + ": ";
    for(int i = 0; i < this->nFields(); i++)
    {
        out = out + " - " + "\"" + this->getFieldName(i) + "\""
              + " : " + QString::number(this->getVal(i))
              + " " + "\"" + this->getFieldUnit(i) + "\""
              + " (" + QString::number(this->getFieldScalar(i)) + ")";
    }
    return out;
}

QDebug operator<<(QDebug debug, const Payload &p)
{
    QDebugStateSaver saver(debug);
    auto &l = Project::getInstance().getTagList();
    QString tag = l.getTag(p.getTagID());
    debug << tag << ":";
    for(int i = 0; i < p.nFields(); i++)
    {
        debug << "-" << p.getFieldName(i)
              << ":" << p.getVal(i)
              << " " << p.getFieldUnit(i)
              << "(" << p.getFieldScalar(i) <<")";
    }
    return debug;
}
