#ifndef TAGTREEINTERFACE_H
#define TAGTREEINTERFACE_H

#include <QObject>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "Common/taglist.h"
#include "Common/tagtype.h"

class TagTreeInterface : public QObject
{
    Q_OBJECT
public:
    explicit TagTreeInterface(QTreeWidget &tree, TagList &tags, QObject *parent = nullptr);

signals:

private slots:
    //update taglist: (from tree)
    void itemChanged(QTreeWidgetItem * item, int column);
    void itemSelectionChanged();
    void itemDoubleClicked(QTreeWidgetItem * item, int column);

    //update display: (from taglist)
    void tagAdded(QString tag);
    void tagRemoved(QString tag);

public slots:
    //update taglist: (from external sources)
    void addTagType();
    void addTagField();
    void removeTagType();
    void removeTagField();

private:
    void addTagFields(TagType const *type, QTreeWidgetItem *tagItem);
    QTreeWidget &_tree;
    TagList &_tags;
    QTreeWidgetItem *_activeItem;

    enum Columns
    {
        NAME = 0,
        FIELDNAME,
        FIELDSCALAR,
        FIELDUNITS,
        _NUMCOLUMNS
    };

private:
    QTreeWidgetItem *_selected = nullptr;
    QTreeWidgetItem *_selected_parent = nullptr;
    bool _selected_is_top_level = false;
    int _selected_field = 0;
    bool _blocking = false;
};

#endif // TAGTREEINTERFACE_H
