#ifndef DISPATCHER_HPP
#define DISPATCHER_HPP

#include <QObject>
#include <vector>
#include <functional>
#include "QuickFuture"
#include "middleware.hpp"
#include "store.hpp"

class Dispatcher : public QObject {
    Q_OBJECT
public:
    Dispatcher() : QObject(nullptr) {}

    void addStore(QSharedPointer<Store> store) {
        mStores.push_back(store);
    }

    void addMiddleware(QSharedPointer<Middleware> middleware) {
        mMiddlewares.push_back(middleware);
    }

    Q_INVOKABLE void dispatch(Action* action) {
        generateNext(mMiddlewares.begin())(action);
    }

private:
    std::function<void(Action*)> generateNext(QList<QSharedPointer<Middleware>>::Iterator it) {
        return [this, it](Action* action) {
            if (it == mMiddlewares.end()) {
                generateNext(mStores.begin())(action);
            } else {
                it->get()->process(action, generateNext(it + 1));
            }
        };
    }

    std::function<void(Action*)> generateNext(QList<QSharedPointer<Store>>::Iterator it) {
        return [this, it](Action* action) {
            if (it != mStores.end()) {
                it->get()->process(action, generateNext(it + 1));
            }
        };
    }

    QList<QSharedPointer<Store>> mStores;
    QList<QSharedPointer<Middleware>> mMiddlewares;
};

Q_DECLARE_METATYPE(Dispatcher*)

#endif // DISPATCHER_HPP
