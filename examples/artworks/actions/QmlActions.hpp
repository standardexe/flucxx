#ifndef QML_ACTIONS_HPP
#define QML_ACTIONS_HPP

#include "actions/GalleryActions.hpp"
#include "actions/NavigationActions.hpp"

#include <QJSValue>

class QmlActions : public QObject {
    Q_OBJECT
public:
    QmlActions() = default;

    Q_INVOKABLE LoadGalleryPageAction* loadPage(int page) { return new LoadGalleryPageAction(page); }

    Q_INVOKABLE ActionNavigatePush* navigateTo(QString url, QVariant params) { return new ActionNavigatePush(url, params); }
    Q_INVOKABLE ActionNavigatePop* navigateBack() { return new ActionNavigatePop(); }

};

#endif // QML_ACTIONS_HPP
