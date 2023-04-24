#ifndef __MIDLEWARE_HPP__
#define __MIDLEWARE_HPP__

#include <QObject>
#include <QSharedPointer>
#include "action.hpp"

class Dispatcher;

class Middleware : public QObject, public QEnableSharedFromThis<Middleware> {
    Q_OBJECT
public:
    Middleware() : QObject(nullptr) {}

    virtual void process(Action* action, Dispatcher* dispatcher, std::function<void(Action*)> next) = 0;

};

#endif
