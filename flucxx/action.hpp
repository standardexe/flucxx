#ifndef __ACTION_HPP__
#define __ACTION_HPP__

#include <QObject>
#include <QString>
#include <QSharedPointer>
#include <QVariantMap>

#define ACTION_PROPERTY(index, type, name)        \
    Q_PROPERTY(type name READ name)               \
    type name() const { return get<index>(); }

class Action : public QObject {
public:
    Action(QString id) : mId(id) {}

    QString const& id() const { return mId; }

private:
    QString mId;
};

template<typename TOwner>
class SimpleAction : public Action {
public:
    SimpleAction() : Action(TOwner::ID) {}
};

template<typename TOwner, typename ...TMembers>
class ActionWithMembers : public Action, public std::tuple<TMembers...> {
public:
    ActionWithMembers(TMembers... args) : Action(TOwner::ID), std::tuple<TMembers...>(args...) {}

protected:
    template<int index>
    decltype(auto) get() const { return std::get<index>(static_cast<std::tuple<TMembers...> const&>(*this)); }
};

Q_DECLARE_METATYPE(Action*)

#endif
