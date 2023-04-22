#ifndef ACTION_NAVIGATION_HPP
#define ACTION_NAVIGATION_HPP

#include "flucxx/action.hpp"
#include "flucxx/dispatcher.hpp"

struct ActionSleep : public ActionWithMembers<ActionSleep, int, Callback<void>> {
    Q_OBJECT
public:
    static constexpr const char* ID = "sleep";
    ACTION_PROPERTY(0, int, durationMs);
    ACTION_PROPERTY(1, Callback<void>, onDone);
    ActionSleep(int ms, Callback<void> onDone) : ActionWithMembers(ms, onDone) {}
    Q_INVOKABLE void dispatch(Dispatcher* dispatcher) {
        dispatcher->dispatch(this);
    }
};
REGISTER_METATYPE(ActionSleep)


struct ActionNavigatePush : public ActionWithMembers<ActionNavigatePush, QString> {
    Q_OBJECT
   public:
    static constexpr const char* ID = "navigation/push";
    ACTION_PROPERTY(0, QString, url);
    ActionNavigatePush(QString url) : ActionWithMembers(url) {}
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
