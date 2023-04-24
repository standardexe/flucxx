#ifndef NAVIGATION_MODEL_HPP
#define NAVIGATION_MODEL_HPP

#include <QObject>
#include <QStack>
#include <QVariant>

class NavigationModel : public QObject {
    Q_OBJECT
public:
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(QString current READ current NOTIFY currentChanged)
    Q_PROPERTY(QVariant currentParams READ currentParams NOTIFY currentParamsChanged)

    void push(QString url, QVariant params) {
        mScreenStack.push(url);
        mParamsStack.push(params);
        countChanged();
        currentChanged(url);
        currentParamsChanged(params);
        screenPushed(url);
    }

    void pop() {
        mScreenStack.pop();
        mParamsStack.pop();
        countChanged();
        currentChanged(current());
        currentParamsChanged(currentParams());
        screenPopped();
    }

    int count() const {
        return mScreenStack.size();
    }

    QString current() const {
        if (mScreenStack.empty()) return "";
        return mScreenStack.top();
    }

    QVariant currentParams() const {
        if (mParamsStack.empty()) return QVariant();
        return mParamsStack.top();
    }

signals:
    void screenPushed(QString const& url);
    void currentChanged(QString const& url);
    void currentParamsChanged(QVariant const& params);
    void screenPopped();
    void countChanged();

private:
    QStack<QString> mScreenStack;
    QStack<QVariant> mParamsStack;

};

#endif
