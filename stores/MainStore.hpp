#ifndef STORE_MAIN_HPP
#define STORE_MAIN_HPP

#include <QObject>
#include "flucxx/store.hpp"
#include "models/TodoListModel.hpp"
#include "actions/TodoActions.hpp"

class MainStore : public Store {
    Q_OBJECT
public:
    Q_PROPERTY(TodoListModel* todoItems READ todoItems NOTIFY todoItemsChanged)

    MainStore() : Store("MainStore") {}

    QFuture<QVariant> process(Action* action, std::function<QFuture<QVariant>(Action*)> next) final {
        if (action->id() == ActionTodoCreate::ID) {
            auto createAction = static_cast<ActionTodoCreate*>(action);
            auto item = new TodoItem(createAction->text(), createAction->done());
            mTodoItems.add(item);
            todoItemsChanged();
        }

        if (action->id() == ActionTodoDelete::ID) {
            auto deleteAction = static_cast<ActionTodoDelete*>(action);
            mTodoItems.remove(deleteAction->index());
            todoItemsChanged();
        }

        if (action->id() == ActionTodoToggleDone::ID) {
            auto toggleAction = static_cast<ActionTodoToggleDone*>(action);
            auto todoItem = mTodoItems.at(toggleAction->index());
            todoItem->setDone(!todoItem->done());
        }

        return next(action);
    }

    TodoListModel* todoItems() { return &mTodoItems; }

signals:
    void todoItemsChanged();

private:
    TodoListModel mTodoItems;
};

#endif // STORE_MAIN_HPP
