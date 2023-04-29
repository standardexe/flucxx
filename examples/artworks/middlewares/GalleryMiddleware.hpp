#ifndef DIALOGMIDDLEWARE_H
#define DIALOGMIDDLEWARE_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>
#include <QMetaEnum>

#include "flucxx/middleware.hpp"
#include "flucxx/dispatcher.hpp"
#include "models/ArtworkModel.hpp"
#include "actions/GalleryActions.hpp"

class GalleryMiddleware : public Middleware {
public:
    void process(Action* action, Dispatcher* dispatcher, std::function<void(Action*)> next) final {
        if (auto loadGalleryPageAction = action->as<LoadGalleryPageAction>(); loadGalleryPageAction) {
            QNetworkRequest request {
                QUrl("https://api.artic.edu/api/v1/artworks?limit=15&page=" + QString::number(loadGalleryPageAction->page()))
            };

            QNetworkReply *reply = mManager.get(request);

            QObject::connect(reply, &QNetworkReply::sslErrors, [reply](const QList<QSslError> &errors) {
                reply->ignoreSslErrors();
            });

            QObject::connect(reply, &QNetworkReply::finished, [this, reply, callback = loadGalleryPageAction->onDone(), dispatcher]() {
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

            QObject::connect(reply, &QNetworkReply::errorOccurred, [dispatcher, callback = loadGalleryPageAction->onDone()](QNetworkReply::NetworkError err) {
                auto action = SetErrorAction(true, QtEnumToString(err));
                dispatcher->dispatch(&action);

                if (callback) {
                    callback(false);
                }
            });
        }

        next(action);
    }

private:
    std::function<void(bool)> mDoneCallback;
    QNetworkAccessManager mManager;

    template<typename QEnum>
    static QString QtEnumToString (const QEnum value) {
      return QMetaEnum::fromType<QEnum>().valueToKey(value);
    }
};

#endif // DIALOGMIDDLEWARE_H
