#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "flucxx/action.hpp"
#include "flucxx/store.hpp"
#include "flucxx/middleware.hpp"
#include "flucxx/dispatcher.hpp"
#include "stores/MainStore.hpp"
#include "actions/QmlActions.hpp"
#include "middlewares/LoggingMiddleware.hpp"

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    auto dispatcher         = QSharedPointer<Dispatcher>::create();
    auto mainStore          = QSharedPointer<MainStore>::create();
    auto loggerMiddleware   = QSharedPointer<LoggingMiddleware>::create();

    dispatcher->addStore(mainStore);
    dispatcher->addMiddleware(loggerMiddleware);

    REGISTER_SINGLETON(Dispatcher, dispatcher.get());
    REGISTER_SINGLETON(MainStore, mainStore.get());
    REGISTER_SINGLETON(QmlActions, new QmlActions {});

    QQmlApplicationEngine engine;
    engine.load("qrc:/Main.qml");

    return app.exec();
}
