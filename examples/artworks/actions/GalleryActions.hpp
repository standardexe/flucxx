#ifndef DIALOGACTIONS_H
#define DIALOGACTIONS_H

#include "flucxx/action.hpp"
#include "flucxx/dispatcher.hpp"
#include "models/ArtworkModel.hpp"

struct SetErrorAction : public ActionWithMembers<SetErrorAction, bool, QString> {
    Q_OBJECT
public:
    static constexpr const char* ID = "gallery/setError";
    ACTION_PROPERTY(0, bool, hasError);
    ACTION_PROPERTY(1, QString, message);
    SetErrorAction(bool hasError, QString message) : ActionWithMembers(hasError, message) {}
};
REGISTER_METATYPE(SetErrorAction)


struct LoadGalleryPageAction : public ActionWithMembers<LoadGalleryPageAction, int, Callback<bool>> {
    Q_OBJECT
public:
    static constexpr const char* ID = "gallery/loadPage";
    ACTION_PROPERTY(0, int, page);
    ACTION_PROPERTY(1, Callback<bool>, onDone);
    LoadGalleryPageAction(int page, Callback<bool> onDone = {}) : ActionWithMembers(page, onDone) {}
};
REGISTER_METATYPE(LoadGalleryPageAction)


struct GalleryPageLoadFinishedAction : public ActionWithMembers<GalleryPageLoadFinishedAction, QList<ArtworkModel*>> {
    Q_OBJECT
public:
    static constexpr const char* ID = "gallery/loadPageFinished";
    ACTION_PROPERTY(0, QList<ArtworkModel*>, models);
    GalleryPageLoadFinishedAction(QList<ArtworkModel*> models) : ActionWithMembers(models) {}
};
REGISTER_METATYPE(GalleryPageLoadFinishedAction)


#endif // DIALOGACTIONS_H
