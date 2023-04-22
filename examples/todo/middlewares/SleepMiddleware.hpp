#ifndef SLEEPMIDDLEWARE_HPP
#define SLEEPMIDDLEWARE_HPP

#include <QMetaProperty>
#include "flucxx/middleware.hpp"
#include <QtConcurrent/QtConcurrent>
#include <QTimer>
#include "actions/NavigationActions.hpp"

class SleepMiddleware : public Middleware {
public:
    void process(Action* action, std::function<void(Action*)> next) final {
        if (action->id() == "sleep") {
            ActionSleep* sleepAction = static_cast<ActionSleep*>(action);
            QTimer::singleShot(1000, sleepAction->onDone());
        }

        next(action);
    }

};

#endif // SLEEPMIDDLEWARE_HPP
