#ifndef TODO_LIST_MODEL_HPP
#define TODO_LIST_MODEL_HPP

#include <QObject>
#include <QAbstractListModel>
#include "models/TodoItem.hpp"

class TodoListModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum Roles { Item };

    void add(TodoItem* item) {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        mItems.push_back(item);
        endInsertRows();
    }

    void remove(int index) {
        beginRemoveRows(QModelIndex(), index, index);
        mItems.erase(mItems.begin() + index);
        endRemoveRows();
    }

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return mItems.size();
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        const int i = index.row();
        if (i < 0 || i >= mItems.size()) return QVariant(QVariant::Invalid);
        return QVariant::fromValue(mItems[i]);
    }

    TodoItem* at(int index) {
        return mItems[index];
    }

    QHash<int,QByteArray> roleNames() const override {
        return { { Roles::Item, "item" } };
    }

private:
    QList<TodoItem*> mItems;
};

REGISTER_METATYPE(TodoListModel)

#endif // TODO_LIST_MODEL_HPP
