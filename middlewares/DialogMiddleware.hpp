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
        if (action->id() == "dialog/show") {
            ActionShowDialog* showActionDialog = static_cast<ActionShowDialog*>(action);
            mFuture = AsyncFuture::deferred<QVariant>();
            next(action);
            return mFuture->future();
        }

        if (action->id() == "dialog/close") {
            ActionCloseDialog* closeActionDialog = static_cast<ActionCloseDialog*>(action);
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
