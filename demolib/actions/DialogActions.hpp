#ifndef DIALOGACTIONS_H
#define DIALOGACTIONS_H

#include <QMetaType>
#include "flucxx/action.hpp"
#include "flucxx/dispatcher.hpp"

struct ActionShowDialog : public ActionWithMembers<ActionShowDialog, QString> {
    Q_OBJECT
public:
    static constexpr const char* ID = "dialog/show";
    ACTION_PROPERTY(0, QString, prompt);
    ActionShowDialog(QString prompt) : ActionWithMembers(prompt) {}
    Q_INVOKABLE QFuture<QVariant> dispatch(Dispatcher* dispatcher) { return dispatcher->dispatch(this); }
};
REGISTER_METATYPE(ActionShowDialog)


struct ActionCloseDialog : public ActionWithMembers<ActionCloseDialog, bool> {
    Q_OBJECT
public:
    static constexpr const char* ID = "dialog/close";
    ACTION_PROPERTY(0, bool, result);
    ActionCloseDialog(bool result) : ActionWithMembers(result) {}
    Q_INVOKABLE void dispatch(Dispatcher* dispatcher) { dispatcher->dispatch(this); }
};
REGISTER_METATYPE(ActionCloseDialog)


#endif // DIALOGACTIONS_H
