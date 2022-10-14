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

        if (action->id() == ActionShowDialog::ID) {
            auto dialogAction = static_cast<ActionShowDialog*>(action);
            mDialogPrompt = dialogAction->prompt();
            mDialogVisible = true;
            dialogPromptChanged();
            dialogVisibleChanged();
        }

        if (action->id() == ActionCloseDialog::ID) {
            auto dialogAction = static_cast<ActionCloseDialog*>(action);
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
