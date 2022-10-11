#ifndef NAVIGATION_STORE_HPP
#define NAVIGATION_STORE_HPP

#include <QObject>
#include "flucxx/store.hpp"
#include "models/NavigationModel.hpp"
#include "actions/NavigationActions.hpp"

class NavigationStore : public Store {
    Q_OBJECT
public:
    Q_PROPERTY(NavigationModel* screens READ screens NOTIFY screensChanged)

    NavigationStore() : Store("NavigationStore") {}

    QFuture<QVariant> process(Action* action, std::function<QFuture<QVariant>(Action*)> next) final {
        if (action->id() == ActionNavigatePush::ID) {
            auto navigateAction = static_cast<ActionNavigatePush*>(action);
            mScreens.push(navigateAction->url());
            screensChanged();
        }

        if (action->id() == ActionNavigatePop::ID) {
            auto popAction = static_cast<ActionNavigatePop*>(action);
            mScreens.pop();
            screensChanged();
        }

        return next(action);
    }

    NavigationModel* screens() { return &mScreens; }

signals:
    void screensChanged();

private:
    NavigationModel mScreens;
};

#endif // NAVIGATION_STORE_HPP
