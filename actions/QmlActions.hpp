#ifndef QML_ACTIONS_HPP
#define QML_ACTIONS_HPP

#include "actions/TodoActions.hpp"
#include "actions/NavigationActions.hpp"
#include "actions/DialogActions.hpp"

class QmlActions : public QObject {
    Q_OBJECT
public:
    QmlActions() = default;

    Q_INVOKABLE ActionTodoCreate* todoCreate(QString text, bool done) { return new ActionTodoCreate(text, done); }
    Q_INVOKABLE ActionTodoDelete* todoDelete(int index) { return new ActionTodoDelete(index); }
    Q_INVOKABLE ActionTodoToggleDone* todoToggle(int index) { return new ActionTodoToggleDone(index); }

    Q_INVOKABLE ActionNavigatePush* navigateTo(QString url) { return new ActionNavigatePush(url); }
    Q_INVOKABLE ActionNavigatePop* navigateBack() { return new ActionNavigatePop(); }

    Q_INVOKABLE ActionSleep* sleep(int ms) { return new ActionSleep(ms); }

    Q_INVOKABLE ActionShowDialog* showDialog(QString prompt) { return new ActionShowDialog(prompt); }
    Q_INVOKABLE ActionCloseDialog* closeDialog(bool result) { return new ActionCloseDialog(result); }
};

#endif // QML_ACTIONS_HPP
