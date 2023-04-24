#ifndef STORE_HPP
#define STORE_HPP

#include <QObject>
#include <QString>
#include <QSharedPointer>
#include "action.hpp"

class Dispatcher;

class Store : public QObject, public QEnableSharedFromThis<Store> {
    Q_OBJECT
public:
    Store(QString name) : QObject(nullptr), mName(name) {}

    Q_INVOKABLE virtual void process(Action* action, Dispatcher* dispatcher, std::function<void(Action* action)> next) = 0;

private:
    QString mName;
};

#endif // STORE_HPP
