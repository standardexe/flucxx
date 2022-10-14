#ifndef DIALOGACTIONS_H
#define DIALOGACTIONS_H

#include "flucxx/action.hpp"

struct ActionShowDialog : public ActionWithMembers<ActionShowDialog, QString> {
    static constexpr const char* ID = "dialog/show";

    ACTION_PROPERTY(0, QString, prompt);

    ActionShowDialog(QString prompt) : ActionWithMembers(prompt) {}

    Q_OBJECT
};
Q_DECLARE_METATYPE(ActionShowDialog*)

struct ActionCloseDialog : public ActionWithMembers<ActionCloseDialog, bool> {
    static constexpr const char* ID = "dialog/close";

    ACTION_PROPERTY(0, bool, result);

    ActionCloseDialog(bool result) : ActionWithMembers(result) {}

    Q_OBJECT
};
Q_DECLARE_METATYPE(ActionCloseDialog*)

#endif // DIALOGACTIONS_H
