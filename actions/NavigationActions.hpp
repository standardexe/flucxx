#ifndef ACTION_NAVIGATION_HPP
#define ACTION_NAVIGATION_HPP

#include "flucxx/action.hpp"


struct ActionSleep : public ActionWithMembers<ActionSleep, int> {
    static constexpr const char* ID = "sleep";

    ACTION_PROPERTY(0, int, durationMs);

    ActionSleep(int ms) : ActionWithMembers(ms) {}

    Q_OBJECT
};
Q_DECLARE_METATYPE(ActionSleep*)


struct ActionNavigatePush : public ActionWithMembers<ActionNavigatePush, QString> {
    static constexpr const char* ID = "navigation/push";

    ACTION_PROPERTY(0, QString, url);

    ActionNavigatePush(QString url) : ActionWithMembers(url) {}

    Q_OBJECT
};
Q_DECLARE_METATYPE(ActionNavigatePush*)


struct ActionNavigatePop : public SimpleAction<ActionNavigatePop> {
    static constexpr const char* ID = "navigation/pop";
    Q_OBJECT
};
Q_DECLARE_METATYPE(ActionNavigatePop*)


#endif // ACTION_NAVIGATION_HPP
