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

Payload::Payload(QByteArray bytes){
    qDebug() << "Reading in bytes";
    QString stringdata = QString(bytes);
    //assume it's a qbytearray of the payload in toString's output form
    QString tag = stringdata.mid(0,stringdata.indexOf(':'));
    const TagList& taglist = Project::getInstance().getTagList();
    QVector <double> vals;
    int nFields = 0;
    int index = stringdata.indexOf(':') + 1;
    while(index < stringdata.indexOf(';')){
        nFields += 1;
        double number;
        if(stringdata.indexOf(',', index) < 0){
            if(stringdata.indexOf(';', index) < 0){
                break;
            }
            number = stringdata.mid(index, stringdata.indexOf(';', index) - index).toDouble();
            index = stringdata.indexOf(';', index) + 1;
        }
        else{
            number = stringdata.mid(index, stringdata.indexOf(',', index) - index).toDouble();
            index = stringdata.indexOf(',', index) + 1;
        }
        //append the number to values
        vals.append(number);
    }
    //if tag doesn't exist insert it
    if(!(Project::getInstance().getTagList().tagExists(tag))){
        qDebug() << "Tag not found from payload";
        //set fieldname, fieldunit, fieldscalar
        QVector<QString> fieldnames = QVector<QString>();
        fieldnames.append("Field");
        QVector<double> fieldscalars = QVector<double>();
        fieldscalars.append(1);
        QVector<QString> fieldunits = QVector<QString>();
        fieldunits.append("Unit");
        TagType *newtag = new TagType(tag, nFields, fieldnames,
                                      fieldscalars, fieldunits);
        Project::getInstance().getTagList().insert(std::unique_ptr<TagType>(newtag));
    }
    //set payload fields
    _vals = vals;
    _nFields = nFields;
    _tagID = Project::getInstance().getTagList().getTagID(tag);
    qDebug() << "Done reading in bytes";
}

Payload::Payload()
    : _vals(0)
{
}

QByteArray Payload::encode() const{
    auto &l = Project::getInstance().getTagList();
    QString payloadString = l.getTag(getTagID());
    payloadString = payloadString.toUpper() + ":";
    for(int i = 0; i < this->nFields(); i++){
        if(i != 0){
            payloadString += ",";
        }
        payloadString += QString::number(this->getValDirect(i));
    }
    payloadString += ";\r\n";
    qDebug() << "Encoded payload: " + payloadString;
    QByteArray output = payloadString.toUtf8();
    output.append('\0');
    return output;
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
    //tag: - fieldname0: value0 fieldunit0 (fieldscalar0) - fieldname1: ...
    auto &l = Project::getInstance().getTagList();
    QString tag;
    if(this->getTagID() == Payload().getTagID()){
        qDebug() <<"Unknown tag";
        return "Unknown tag";
    }
    QString out;
    out = out + tag + ": ";
    for(int i = 0; i < this->nFields(); i++)
    {
        out = out + " - " + this->getFieldName(i)
              + ": " + QString::number(this->getVal(i))
              + " " + this->getFieldUnit(i) +
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
