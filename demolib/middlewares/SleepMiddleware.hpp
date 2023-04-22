#ifndef SLEEPMIDDLEWARE_HPP
#define SLEEPMIDDLEWARE_HPP

#include <QDebug>
#include <QMetaProperty>
#include "flucxx/middleware.hpp"
#include <QtConcurrent/QtConcurrent>
#include "asyncfuture.h"
#include "actions/NavigationActions.hpp"

class SleepMiddleware : public Middleware {
public:
    void process(Action* action, std::function<void(Action*)> next) final {
        if (action->id() == "sleep") {
            ActionSleep* sleepAction = static_cast<ActionSleep*>(action);

            QFuture<QVariant> sleepFuture = QtConcurrent::run([time = sleepAction->durationMs()]() -> QVariant {
                QThread::msleep(time);
                return QVariant::fromValue(1234);
            });

            AsyncFuture::observe(sleepFuture).onCompleted(sleepAction->onDone());
        }

        next(action);
    }

};

#endif // SLEEPMIDDLEWARE_HPP
