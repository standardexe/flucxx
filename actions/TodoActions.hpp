#ifndef ACTION_TODO_REMOVE_HPP
#define ACTION_TODO_REMOVE_HPP

#include "flucxx/action.hpp"


struct ActionTodoCreate : public ActionWithMembers<ActionTodoCreate, QString, bool> {
    static constexpr const char* ID = "todo/create";

    ACTION_PROPERTY(0, QString, text);
    ACTION_PROPERTY(1, bool, done);

    ActionTodoCreate(QString text, bool done) : ActionWithMembers(text, done) {}

    Q_OBJECT
};
Q_DECLARE_METATYPE(ActionTodoCreate*)


struct ActionTodoDelete : public ActionWithMembers<ActionTodoDelete, int> {
    static constexpr const char* ID = "todo/delete";

    ACTION_PROPERTY(0, int, index);

    ActionTodoDelete(int index) : ActionWithMembers(index) {}

    Q_OBJECT
};
Q_DECLARE_METATYPE(ActionTodoDelete*)


struct ActionTodoToggleDone : public ActionWithMembers<ActionTodoToggleDone, int> {
    static constexpr const char* ID = "todo/toggleDone";

    ACTION_PROPERTY(0, int, index);

    ActionTodoToggleDone(int index) : ActionWithMembers(index) {}

    Q_OBJECT
};
Q_DECLARE_METATYPE(ActionTodoToggleDone*)

#endif // ACTION_TODO_REMOVE_HPP
