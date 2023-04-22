#ifndef MODEL_TODO_HPP
#define MODEL_TODO_HPP

#include "flucxx/action.hpp"
#include <QObject>
#include <QAbstractListModel>

class TodoItem : public QObject {
    Q_OBJECT
public:
    Q_PROPERTY(QString text READ text NOTIFY textChanged)
    Q_PROPERTY(bool done READ done NOTIFY doneChanged)

    TodoItem() = default;
    TodoItem(QString text, bool done) : mText(text), mDone(done) {}

    QString text() const { return mText; }
    bool done() const { return mDone; }

    void setText(QString text) {
        mText = text;
        textChanged();
    }

    void setDone(bool done) {
        mDone = done;
        doneChanged();
    }

signals:
    void textChanged();
    void doneChanged();

private:
    QString mText;
    bool mDone;
};

REGISTER_METATYPE(TodoItem)

#endif // MODEL_TODO_HPP
