#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "flucxx/action.hpp"
#include "flucxx/store.hpp"
#include "flucxx/middleware.hpp"
#include "flucxx/dispatcher.hpp"
#include "stores/MainStore.hpp"
#include "stores/NavigationStore.hpp"
#include "actions/QmlActions.hpp"
#include "middlewares/LoggingMiddleware.hpp"

#include "qffuture.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QuickFuture::init();

    auto mainStore          = QSharedPointer<MainStore>::create();
    auto dispatcher         = QSharedPointer<Dispatcher>::create();
    auto navigationStore    = QSharedPointer<NavigationStore>::create();
    auto logger             = QSharedPointer<LoggingMiddleware>::create();

    dispatcher->addStore(mainStore);
    dispatcher->addStore(navigationStore);
    dispatcher->addMiddleware(logger);

    qmlRegisterUncreatableType<NavigationStore>("NavigationStore", 1, 0, "NavigationStore", "");
    qmlRegisterUncreatableType<Dispatcher>("Dispatcher", 1, 0, "Dispatcher", "");
    qmlRegisterUncreatableType<MainStore>("MainStore", 1, 0, "MainStore", "");
    qmlRegisterUncreatableType<QmlActions>("Actions", 1, 0, "Actions", "");

    qmlRegisterSingletonInstance("NavigationStore", 1, 0, "NavigationStore", navigationStore.get());
    qmlRegisterSingletonInstance("Dispatcher", 1, 0, "Dispatcher", dispatcher.get());
    qmlRegisterSingletonInstance("MainStore", 1, 0, "MainStore", mainStore.get());
    qmlRegisterSingletonInstance("Actions", 1, 0, "Actions", new QmlActions {});

    qRegisterMetaType<ActionSleep*>();

    qRegisterMetaType<ActionTodoToggleDone*>();
    qRegisterMetaType<ActionNavigatePush*>();
    qRegisterMetaType<ActionNavigatePop*>();
    qRegisterMetaType<ActionTodoCreate*>();
    qRegisterMetaType<ActionTodoDelete*>();
    qRegisterMetaType<TodoListModel*>();
    qRegisterMetaType<TodoItem*>();
    qRegisterMetaType<Action*>();

    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:///"); // required by QuickPromise

    const QUrl url(QStringLiteral("qrc:/Main.qml"));
    engine.load(url);

    return app.exec();
}
