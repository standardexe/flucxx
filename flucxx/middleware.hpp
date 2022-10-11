#ifndef __MIDLEWARE_HPP__
#define __MIDLEWARE_HPP__

#include <QObject>
#include <QSharedPointer>
#include "QuickFuture"
#include "action.hpp"

class Middleware : public QObject, public QEnableSharedFromThis<Middleware> {
    Q_OBJECT
public:
    Middleware() : QObject(nullptr) {}

    virtual QFuture<QVariant> process(Action* action, std::function<QFuture<QVariant>(Action*)> next) = 0;

};

#endif
