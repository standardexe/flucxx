#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "flucxx/action.hpp"
#include "flucxx/store.hpp"
#include "flucxx/middleware.hpp"
#include "flucxx/dispatcher.hpp"
#include "demolib/stores/MainStore.hpp"
#include "demolib/stores/NavigationStore.hpp"
#include "demolib/actions/QmlActions.hpp"
#include "demolib/middlewares/LoggingMiddleware.hpp"
#include "demolib/middlewares/SleepMiddleware.hpp"
#include "demolib/middlewares/DialogMiddleware.hpp"

#include "qffuture.h"

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QuickFuture::init();

    auto mainStore          = QSharedPointer<MainStore>::create();
    auto dispatcher         = QSharedPointer<Dispatcher>::create();
    auto navigationStore    = QSharedPointer<NavigationStore>::create();
    auto logger             = QSharedPointer<LoggingMiddleware>::create();
    auto sleepMw            = QSharedPointer<SleepMiddleware>::create();
    auto dialogmw           = QSharedPointer<DialogMiddleware>::create();

    dispatcher->addStore(mainStore);
    dispatcher->addStore(navigationStore);
    dispatcher->addMiddleware(logger);
    dispatcher->addMiddleware(sleepMw);
    dispatcher->addMiddleware(dialogmw);

    REGISTER_SINGLETON(NavigationStore, navigationStore.get());
    REGISTER_SINGLETON(Dispatcher, dispatcher.get());
    REGISTER_SINGLETON(MainStore, mainStore.get());
    REGISTER_SINGLETON(QmlActions, new QmlActions {});

    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:///"); // required by QuickPromise
    engine.load("qrc:/Main.qml");

    return app.exec();
}
