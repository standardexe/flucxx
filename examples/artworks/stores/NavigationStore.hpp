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

    void process(Action* action, Dispatcher*, std::function<void(Action*)> next) final {
        if (auto navigateAction = action->as<ActionNavigatePush>(); navigateAction) {
            mScreens.push(navigateAction->url(), navigateAction->params());
            screensChanged();
        }
        else if (auto popAction = action->as<ActionNavigatePop>(); popAction) {
            mScreens.pop();
            screensChanged();
        }

        next(action);
    }

    NavigationModel* screens() { return &mScreens; }

signals:
    void screensChanged();

private:
    NavigationModel mScreens;
};

#endif // NAVIGATION_STORE_HPP
