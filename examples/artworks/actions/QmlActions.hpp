#ifndef QML_ACTIONS_HPP
#define QML_ACTIONS_HPP

#include "actions/GalleryActions.hpp"
#include "actions/NavigationActions.hpp"
#include "flucxx/promise.hpp"

#include <QJSValue>
#include <QJSEngine>

class QmlActions : public QObject {
    Q_OBJECT
public:
    QmlActions() = default;

    Q_INVOKABLE QJSValue loadPage(Dispatcher* dispatcher, int page) {
        auto promise = PromiseCallback::createPromise(qjsEngine(this));

        auto action = LoadGalleryPageAction(page, [promiseCallback = std::get<1>(promise)](bool success) {
            if (success) {
              promiseCallback->resolve(success);
            } else {
              promiseCallback->reject(success);
            }
            promiseCallback->deleteLater();
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

};

#endif // QML_ACTIONS_HPP
