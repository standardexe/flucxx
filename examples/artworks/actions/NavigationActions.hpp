#ifndef ACTION_NAVIGATION_HPP
#define ACTION_NAVIGATION_HPP

#include "flucxx/action.hpp"
#include "flucxx/dispatcher.hpp"


struct ActionNavigatePush : public ActionWithMembers<ActionNavigatePush, QString, QVariant> {
    Q_OBJECT
   public:
    static constexpr const char* ID = "navigation/push";
    ACTION_PROPERTY(0, QString, url);
    ACTION_PROPERTY(1, QVariant, params);
    ActionNavigatePush(QString url, QVariant params = {}) : ActionWithMembers(url, params) {}
    Q_INVOKABLE void dispatch(Dispatcher* dispatcher) { dispatcher->dispatch(this); }
};
REGISTER_METATYPE(ActionNavigatePush)


struct ActionNavigatePop : public SimpleAction<ActionNavigatePop> {
    Q_OBJECT
public:
    static constexpr const char* ID = "navigation/pop";
    Q_INVOKABLE void dispatch(Dispatcher* dispatcher) { dispatcher->dispatch(this); }
};
REGISTER_METATYPE(ActionNavigatePop)


#endif // ACTION_NAVIGATION_HPP
