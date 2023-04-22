#ifndef STORE_MAIN_HPP
#define STORE_MAIN_HPP

#include <QObject>
#include "flucxx/store.hpp"
#include "models/TodoListModel.hpp"
#include "actions/TodoActions.hpp"
#include "actions/DialogActions.hpp"

class MainStore : public Store {
    Q_OBJECT
public:
    Q_PROPERTY(TodoListModel* todoItems READ todoItems NOTIFY todoItemsChanged)
    Q_PROPERTY(QString dialogPrompt READ dialogPrompt NOTIFY dialogPromptChanged)
    Q_PROPERTY(bool dialogVisible READ dialogVisible NOTIFY dialogVisibleChanged)

    MainStore() : Store("MainStore") {}

    QFuture<QVariant> process(Action* action, std::function<QFuture<QVariant>(Action*)> next) final {
        if (auto createAction = action->as<ActionTodoCreate>(); createAction) {
            auto item = new TodoItem(createAction->text(), createAction->done());
            mTodoItems.add(item);
            todoItemsChanged();
        }
        else if (auto deleteAction = action->as<ActionTodoDelete>(); deleteAction) {
            mTodoItems.remove(deleteAction->index());
            todoItemsChanged();
        }
        else if (auto toggleAction = action->as<ActionTodoToggleDone>(); toggleAction) {
            auto todoItem = mTodoItems.at(toggleAction->index());
            todoItem->setDone(!todoItem->done());
        }
        else if (auto dialogAction = action->as<ActionShowDialog>(); dialogAction) {
            mDialogPrompt = dialogAction->prompt();
            mDialogVisible = true;
            dialogPromptChanged();
            dialogVisibleChanged();
        }
        else if (auto dialogAction = action->as<ActionCloseDialog>(); dialogAction) {
            mDialogVisible = false;
            dialogVisibleChanged();
        }

        return next(action);
    }

    TodoListModel* todoItems() { return &mTodoItems; }
    QString dialogPrompt() const { return mDialogPrompt; }
    bool dialogVisible() const { return mDialogVisible; }

signals:
    void todoItemsChanged();
    void dialogPromptChanged();
    void dialogVisibleChanged();

private:
    TodoListModel mTodoItems;
    bool mDialogVisible {false};
    QString mDialogPrompt;
};

#endif // STORE_MAIN_HPP
