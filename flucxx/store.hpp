#ifndef STORE_HPP
#define STORE_HPP

#include <QObject>
#include <QString>
#include <QSharedPointer>
#include "QuickFuture"
#include "action.hpp"

class Store : public QObject, public QEnableSharedFromThis<Store> {
    Q_OBJECT
public:
    Store(QString name) : QObject(nullptr), mName(name) {}

    Q_INVOKABLE virtual QFuture<QVariant> process(Action* action, std::function<QFuture<QVariant>(Action* action)> next) = 0;

private:
    QString mName;
};

#endif // STORE_HPP
