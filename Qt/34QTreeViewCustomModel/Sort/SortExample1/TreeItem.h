#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVariant>

class TreeItem
{
public:
    enum Type
    {
        UNKNOWN = -1,
        PROVINCE,
        PERSON
    };

    explicit TreeItem(TreeItem *parent = nullptr);
    ~TreeItem();

    void addChild(TreeItem *item);
    void removeChildren();

    TreeItem *child(int row) { return _children.value(row); }
    TreeItem *parent() { return _parent; }

    int childCount() const { return _children.count(); }

    QVariant data(int column) const;

    //设置、获取节点存的数据指针
    void setPtr(void* p) { _ptr = p; }
    void* ptr() const { return _ptr; }

    // 保存该节点是其父节点的第几个子节点，查询优化所用
    void setRow(int row) { _row = row; }
    // 返回本节点位于父节点下第几个子节点
    int row() const { return _row; }

    Type getType() const { return _type; }
    void setType(const Type &value) { _type = value; }

    void sort(int column, Qt::SortOrder order);

private:
    static bool lessThan_sex(const TreeItem *item1, const TreeItem *item2);
    static bool lessThan_age(const TreeItem *item1, const TreeItem *item2);
    void sort_sex(Qt::SortOrder order);
    void sort_age(Qt::SortOrder order);

private:
    QList<TreeItem*> _children;   // 子节点
    TreeItem *_parent;          // 父节点
    Type _type;      // 此节点保存的数据类型
    void* _ptr;     // 存储数据的指针
    int _row;       // 此item位于父节点中第几个
};

#endif // TREEITEM_H
