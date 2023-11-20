#ifndef __PROMISE_HPP__
#define __PROMISE_HPP__

#include <tuple>
#include <QQmlEngine>

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

    static std::tuple<QJSValue, PromiseCallback*> createPromise(QJSEngine* engine) {
        PromiseCallback* promiseCallback = new PromiseCallback;
        QJSValue callbackObject = engine->newQObject(promiseCallback);
        QJSValue promiseFunction = engine->evaluate("(function(callbackObject) { return new Promise(callbackObject.callback) })");
        QJSValue promise = promiseFunction.call({callbackObject});
        return { promise, promiseCallback };
    }


private:
    QJSValue mResolve;
    QJSValue mReject;
};

#endif
