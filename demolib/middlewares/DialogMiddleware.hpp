#ifndef DIALOGMIDDLEWARE_H
#define DIALOGMIDDLEWARE_H

#include <QDebug>
#include <QMetaProperty>
#include <optional>
#include "flucxx/middleware.hpp"
#include <QtConcurrent/QtConcurrent>
#include "asyncfuture.h"
#include "actions/DialogActions.hpp"

class DialogMiddleware : public Middleware {
public:
    QFuture<QVariant> process(Action* action, std::function<QFuture<QVariant>(Action*)> next) final {
        if (auto showActionDialog = action->as<ActionShowDialog>(); showActionDialog) {
            mFuture = AsyncFuture::deferred<QVariant>();
            next(action);
            return mFuture->future();
        }

        if (auto closeActionDialog = action->as<ActionCloseDialog>(); closeActionDialog) {
            if (mFuture.has_value()) {
                mFuture.value().complete(closeActionDialog->result());
                mFuture.reset();
            }
        }

        return next(action);
    }

private:
    std::optional<AsyncFuture::Deferred<QVariant>> mFuture;
};

#endif // DIALOGMIDDLEWARE_H
