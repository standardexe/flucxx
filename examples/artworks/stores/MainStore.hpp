#ifndef STORE_MAIN_HPP
#define STORE_MAIN_HPP

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>
#include <QMetaEnum>

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

            loadPage(dispatcher, loadGalleryPageAction->onDone());

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
    QNetworkAccessManager mManager;

    void setArtworks(QList<ArtworkModel*> artworks) {
      for (ArtworkModel* model : mArtworks) model->deleteLater();
      mArtworks = artworks;
    }

    void loadPage(Dispatcher* dispatcher, std::function<void(bool)> actionCallback) {
        QNetworkRequest request {
            QUrl("https://api.artic.edu/api/v1/artworks?limit=15&page=" + QString::number(mPage))
        };

        QNetworkReply *reply = mManager.get(request);

        QObject::connect(reply, &QNetworkReply::sslErrors, [reply](const QList<QSslError> &errors) {
            reply->ignoreSslErrors();
        });

        QObject::connect(reply, &QNetworkReply::finished, [this, reply, callback = actionCallback, dispatcher]() {
            QJsonDocument doc   = QJsonDocument::fromJson(reply->readAll());
            QJsonObject config  = doc.object().value("config").toObject();
            QJsonArray data     = doc.object().value("data").toArray();

            QList<ArtworkModel*> artworks;

            for (int i = 0; i < data.size(); i++) {
                QJsonObject artwork = data.at(i).toObject();
                const QString thumbnail   = artwork["thumbnail"].toObject().value("lqip").toString();
                const QString artistTitle = artwork["artist_title"].toString();
                const QString imageId     = artwork["image_id"].toString();
                const QString title       = artwork["title"].toString();
                const QString imageUrl    = config["iiif_url"].toString() + "/" + imageId + "/full/843,/0/default.jpg";
                artworks.append(new ArtworkModel {title, artistTitle, thumbnail, imageUrl});
            }

            auto action = GalleryPageLoadFinishedAction(artworks);
            dispatcher->dispatch(&action);

            if (callback) {
                callback(true);
            }

            reply->deleteLater();
        });

        QObject::connect(reply, &QNetworkReply::errorOccurred, [dispatcher, callback = actionCallback](QNetworkReply::NetworkError err) {
            auto action = SetErrorAction(true, QtEnumToString(err));
            dispatcher->dispatch(&action);

            if (callback) {
                callback(false);
            }
        });
    }

    template<typename QEnum>
    static QString QtEnumToString (const QEnum value) {
      return QMetaEnum::fromType<QEnum>().valueToKey(value);
    }
};

#endif // STORE_MAIN_HPP
