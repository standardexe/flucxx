#ifndef STORE_MAIN_HPP
#define STORE_MAIN_HPP

#include <QObject>
#include "flucxx/store.hpp"
#include "actions/GalleryActions.hpp"

class MainStore : public Store {
    Q_OBJECT
public:
    Q_PROPERTY(int page READ page NOTIFY pageChanged)
    Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged)
    Q_PROPERTY(bool hasError READ hasError NOTIFY hasErrorChanged)
    Q_PROPERTY(QString error READ error NOTIFY errorChanged)
    Q_PROPERTY(QList<ArtworkModel*> artworks READ artworks NOTIFY artworksChanged)

    MainStore() : Store("MainStore") {}

    void process(Action* action, Dispatcher* dispatcher, std::function<void(Action*)> next) final {
        if (auto loadGalleryPageAction = action->as<LoadGalleryPageAction>(); loadGalleryPageAction) {
            mPage = loadGalleryPageAction->page();
            mLoading = true;

            pageChanged();
            loadingChanged();
        }
        else if (auto loadGalleryPageFinishedAction = action->as<GalleryPageLoadFinishedAction>(); loadGalleryPageFinishedAction) {
            setArtworks(loadGalleryPageFinishedAction->models());
            mLoading = false;

            artworksChanged();
            loadingChanged();
        }
        else if (auto setErrorAction = action->as<SetErrorAction>(); setErrorAction) {
            mLoading = false;
            mHasError = setErrorAction->hasError();
            mError = setErrorAction->message();

            errorChanged();
            hasErrorChanged();
            loadingChanged();
        }

        next(action);
    }

    int page() const { return mPage; }
    bool loading() const { return mLoading; }
    bool hasError() const { return mHasError; }
    QString error() const { return mError; }
    QList<ArtworkModel*> artworks() const { return mArtworks; }

signals:
    void pageChanged();
    void loadingChanged();
    void artworksChanged();
    void hasErrorChanged();
    void errorChanged();

private:
    int mPage = -1;
    bool mLoading = false;
    bool mHasError = false;
    QString mError = "";
    QList<ArtworkModel*> mArtworks;

    void setArtworks(QList<ArtworkModel*> artworks) {
      for (ArtworkModel* model : mArtworks) model->deleteLater();
      mArtworks = artworks;
    }
};

#endif // STORE_MAIN_HPP
