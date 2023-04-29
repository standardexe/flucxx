#ifndef QML_ACTIONS_HPP
#define QML_ACTIONS_HPP

#include "actions/GalleryActions.hpp"
#include "actions/NavigationActions.hpp"

#include <QJSValue>
#include <QJSEngine>


class PromiseCallback : public QObject {
    Q_OBJECT
public:
    Q_INVOKABLE void callback(QJSValue resolve, QJSValue reject) {
      mResolve = resolve;
      mReject = reject;
    }

    template<typename ...T>
    void resolve(T... args) { mResolve.call({args...}); deleteLater(); }

    template<typename ...T>
    void reject(T... args) { mReject.call({args...}); deleteLater(); }

private:
    QJSValue mResolve;
    QJSValue mReject;
};


class QmlActions : public QObject {
    Q_OBJECT
public:
    QmlActions() = default;

    Q_INVOKABLE QJSValue loadPage(Dispatcher* dispatcher, int page) {
        auto promise = createPromise();

        auto action = LoadGalleryPageAction(page, [promiseCallback = std::get<1>(promise)](bool success) {
            if (success) {
              promiseCallback->resolve(success);
            } else {
              promiseCallback->reject(success);
            }
        });

        dispatcher->dispatch(&action);

        return std::get<0>(promise);
    }

    Q_INVOKABLE void navigateTo(Dispatcher* dispatcher, QString url, QVariant params) {
        auto action = ActionNavigatePush(url, params);
        dispatcher->dispatch(&action);
    }

    Q_INVOKABLE void navigateBack(Dispatcher* dispatcher) {
        auto action = ActionNavigatePop();
        dispatcher->dispatch(&action);
    }

private:
    std::tuple<QJSValue, PromiseCallback*> createPromise() {
        PromiseCallback* promiseCallback = new PromiseCallback;
        QJSValue callbackObject = qjsEngine(this)->newQObject(promiseCallback);
        QJSValue promiseFunction = qjsEngine(this)->evaluate("(function(callbackObject) { return new Promise(callbackObject.callback) })");
        QJSValue promise = promiseFunction.call({callbackObject});
        return { promise, promiseCallback };
    }
};

#endif // QML_ACTIONS_HPP
