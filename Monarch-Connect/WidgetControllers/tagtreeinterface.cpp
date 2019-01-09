#include "tagtreeinterface.h"
#include <QStringList>
#include <QVector>
#include <QString>
#include <QList>
#include <QDebug>

TagTreeInterface::TagTreeInterface(QTreeWidget &tree, TagList &tags, QObject *parent)
    : QObject(parent),
      _tree(tree),
      _tags(tags)
{
    tree.setColumnCount(Columns::_NUMCOLUMNS);
    connect(&_tree, &QTreeWidget::itemChanged,
            this, &TagTreeInterface::itemChanged);
    connect(&_tree, &QTreeWidget::itemSelectionChanged,
            this, &TagTreeInterface::itemSelectionChanged);
    connect(&_tree, &QTreeWidget::itemDoubleClicked,
            this, &TagTreeInterface::itemDoubleClicked);
    connect(&_tags, &TagList::added,
            this, &TagTreeInterface::tagAdded);
    connect(&_tags, &TagList::removed,
            this, &TagTreeInterface::tagRemoved);
}

//adds fields of type w/ tagItem as parent.
void TagTreeInterface::addTagFields(TagType const* type, QTreeWidgetItem *tagItem)
{
    qDebug() << "adding " << type->nFields() << "fields:";
    while(tagItem->childCount())
    {
        tagItem->removeChild(tagItem->child(0));
    }
    for(int i = 0; i < type->nFields(); i++)
    {
        QVector<QString> strings(Columns::_NUMCOLUMNS);
        strings[NAME] = QString::number(i);
        strings[FIELDNAME] = type->getFieldName(i);
        strings[FIELDSCALAR] = QString::number(type->getFieldScalar(i));
        strings[FIELDUNITS] = type->getFieldUnit(i);

        QStringList stringlist = QStringList(strings.toList());
        auto fieldItem = new QTreeWidgetItem(tagItem,stringlist);
        fieldItem->setFlags(fieldItem->flags() | Qt::ItemIsEditable);
        tagItem->addChild(fieldItem);
        qDebug() << "added field:";
        qDebug() << stringlist;
    }
}

void TagTreeInterface::tagAdded(QString tag)
{
    _blocking = true;
    auto tagItems = _tree.findItems(tag, Qt::MatchFixedString, Columns::NAME);
    auto type = _tags.getTagType(tag).get();
    if(tagItems.length() == 0)
    {
        qDebug() << "adding new tag";
        auto tagItem = new QTreeWidgetItem(static_cast<QTreeWidget*>(nullptr), QStringList(tag));
        tagItem->setFlags(tagItem->flags() | Qt::ItemIsEditable);
        _tree.insertTopLevelItem(0, tagItem);
        addTagFields(type, tagItem);
    }
    else
    {
        qDebug() << "updating existing tag";
        auto tagItem = tagItems[0];
        addTagFields(type, tagItem);
    }
    _blocking = false;
}

void TagTreeInterface::tagRemoved(QString tag)
{
    auto tagItems = _tree.findItems(tag, Qt::MatchFixedString, Columns::NAME);
    for(auto item : tagItems)
    {
        delete item;
    }
}

void TagTreeInterface::itemChanged(QTreeWidgetItem * item, int column)
{
    if(_blocking) return;
    qDebug() << "item edited";
    QTreeWidgetItem *parent = nullptr;
    int field = 0;
    if(!item->parent())
    {
        parent = item;
    }
    else {
        field = item->data(Columns::NAME, Qt::DisplayRole).toInt();
        parent = item->parent();
    }

    QString tag = parent->data(Columns::NAME, Qt::DisplayRole).toString();
    if(!item->parent())
    {
        return; //can't edit these yet.
    }
    auto newType = std::make_unique<TagType>(*(_tags.getTagType(tag)));

    QString newData = item->data(column, Qt::DisplayRole).toString();
    switch(column)
    {
    case Columns::NAME:
        //not allowed, not implemented. ABORT!
        return;
    case Columns::FIELDNAME:
        newType->setFieldName(field, newData);
        break;
    case Columns::FIELDSCALAR:
        newType->setFieldScalar(field, newData.toDouble());
        break;
    case Columns::FIELDUNITS:
        newType->setFieldUnit(field, newData);
        break;
    default:
        return;
    }
    _tags.insert(std::move(newType));
}

void TagTreeInterface::itemSelectionChanged()
{
    _selected = _tree.selectedItems()[0];
    _selected_parent = nullptr;
    if(!_selected->parent())
    {
        _selected_parent = _selected;
        _selected_is_top_level = true;
        _selected_field = 0;
    }
    else {
        _selected_field = _selected->data(Columns::NAME, Qt::DisplayRole).toInt();
        _selected_parent = _selected->parent();
        _selected_is_top_level = false;
    }
}

void TagTreeInterface::itemDoubleClicked(QTreeWidgetItem * item, int column)
{
    if(column != Columns::NAME)
    {
        _tree.editItem(item, column);
    }
}

void TagTreeInterface::addTagType()
{
    auto newType = std::make_unique<TagType>("New Tag", "Field 1", 1, "Units");
    _tags.insert(std::move(newType));
}
void TagTreeInterface::addTagField()
{
    if(!_selected_parent || !_selected) return;
    auto tag = _selected_parent->data(Columns::NAME, Qt::DisplayRole).toString();
    auto newType = std::make_unique<TagType>(*_tags.getTagType(tag));
    newType->addField("New Field", 1, "Units");
    _tags.insert(std::move(newType));

}
void TagTreeInterface::removeTagType()
{
    if(!_selected_parent || !_selected) return;
    auto tag = _selected_parent->data(Columns::NAME, Qt::DisplayRole).toString();
    _selected = nullptr;
    _selected_parent = nullptr;
    _tags.remove(tag);
}
void TagTreeInterface::removeTagField()
{
    if(!_selected_parent || !_selected) return;
    auto tag = _selected_parent->data(Columns::NAME, Qt::DisplayRole).toString();
    auto newType = std::make_unique<TagType>(*_tags.getTagType(tag));
    newType->removeField(_selected_field);
    _selected = nullptr;
    _selected_parent = nullptr;
    _tags.insert(std::move(newType));
}
