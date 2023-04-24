#ifndef DIALOGACTIONS_H
#define DIALOGACTIONS_H

#include "flucxx/action.hpp"
#include "flucxx/dispatcher.hpp"

struct ActionDigit : public ActionWithMembers<ActionDigit, int> {
    Q_OBJECT
public:
    static constexpr const char* ID = "calc/digit";
    ACTION_PROPERTY(0, int, digit);
    ActionDigit(int digit) : ActionWithMembers(digit) {}
    Q_INVOKABLE void dispatch(Dispatcher* dispatcher) { dispatcher->dispatch(this); }
};
REGISTER_METATYPE(ActionDigit)


struct ActionOperator : public ActionWithMembers<ActionOperator, QString> {
    Q_OBJECT
public:
    static constexpr const char* ID = "calc/operator";
    ACTION_PROPERTY(0, QString, op);
    ActionOperator(QString op) : ActionWithMembers(op) {}
    Q_INVOKABLE void dispatch(Dispatcher* dispatcher) { dispatcher->dispatch(this); }
};
REGISTER_METATYPE(ActionOperator)


#endif // DIALOGACTIONS_H
