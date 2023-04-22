#ifndef DIALOGMIDDLEWARE_H
#define DIALOGMIDDLEWARE_H

#include <optional>
#include "flucxx/middleware.hpp"
#include "actions/DialogActions.hpp"

class DialogMiddleware : public Middleware {
public:
    void process(Action* action, std::function<void(Action*)> next) final {
        if (auto showActionDialog = action->as<ActionShowDialog>(); showActionDialog) {
            mDoneCallback = showActionDialog->onDone();
        }

        if (auto closeActionDialog = action->as<ActionCloseDialog>(); closeActionDialog) {
            if (mDoneCallback) mDoneCallback(closeActionDialog->result());
        }

        next(action);
    }

private:
    std::function<void(bool)> mDoneCallback;
};

#endif // DIALOGMIDDLEWARE_H
