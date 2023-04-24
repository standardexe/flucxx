#ifndef ARTWORK_MODEL_HPP
#define ARTWORK_MODEL_HPP

#include <QObject>

class ArtworkModel : public QObject {
    Q_OBJECT
public:
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(QString artist READ artist NOTIFY artistChanged)
    Q_PROPERTY(QString thumbnail READ thumbnail NOTIFY thumbnailChanged)
    Q_PROPERTY(QString imageUrl READ imageUrl NOTIFY imageUrlChanged)

    ArtworkModel(QString title, QString artist, QString thumbnail, QString imageUrl)
        : mTitle(title), mArtist(artist), mThumbnail(thumbnail), mImageUrl(imageUrl) {}

    QString title() const { return mTitle; }
    QString artist() const { return mArtist; }
    QString thumbnail() const { return mThumbnail; }
    QString imageUrl() const { return mImageUrl; }

signals:
    void artistChanged();
    void titleChanged();
    void thumbnailChanged();
    void imageUrlChanged();

private:
    QString mTitle;
    QString mArtist;
    QString mThumbnail;
    QString mImageUrl;

};

#endif
