#ifndef NAVIGATION_MODEL_HPP
#define NAVIGATION_MODEL_HPP

#include <QObject>
#include <QStack>

class NavigationModel : public QObject {
    Q_OBJECT
public:
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(QString current READ current NOTIFY currentChanged)

    void push(QString url) {
        mScreenStack.push(url);
        countChanged();
        currentChanged(url);
        screenPushed(url);
    }

    void pop() {
        mScreenStack.pop();
        countChanged();
        currentChanged(current());
        screenPopped();
    }

    int count() const {
        return mScreenStack.size();
    }

    QString current() const {
        if (mScreenStack.empty()) return "";
        return mScreenStack.top();
    }

signals:
    void screenPushed(QString const& url);
    void currentChanged(QString const& url);
    void screenPopped();
    void countChanged();

private:
    QStack<QString> mScreenStack;

};

#endif
