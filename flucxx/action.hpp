#ifndef __ACTION_HPP__
#define __ACTION_HPP__

#include <QObject>
#include <QString>
#include <QSharedPointer>
#include <QVariantMap>

#define REGISTER_METATYPE(CLASS)     \
    Q_DECLARE_METATYPE(CLASS*)       \
    static struct CLASS##Metaid      \
    {                                \
      CLASS##Metaid()                \
      {                              \
        qRegisterMetaType<CLASS*>(); \
      }                              \
    } _##CLASS##metaid;


#define REGISTER_SINGLETON(type, variable) 						\
    qmlRegisterUncreatableType<type>(#type, 1, 0, #type, ""); 	\
    qmlRegisterSingletonInstance(#type, 1, 0, #type, variable);


// No way around passing the type. The moc is not smart enough
// to figure out decltype(...) shenanigans on its own.
#define ACTION_PROPERTY(index, type, name)        \
    Q_PROPERTY(type name READ name)               \
    type name() const { return get<index>(); }

template<typename T>
struct CallbackDefinition {
  using type = std::function<void(T)>;
};

template<>
struct CallbackDefinition<void> {
  using type = std::function<void()>;
};

template<typename T>
using Callback = typename CallbackDefinition<T>::type;

Q_DECLARE_METATYPE(Callback<bool>)
Q_DECLARE_METATYPE(Callback<int>)
Q_DECLARE_METATYPE(Callback<QString>)
Q_DECLARE_METATYPE(Callback<void>)

class Action : public QObject {
public:
    Action(QString id) : mId(id) {}

    QString const& id() const { return mId; }

    template<typename T> T* as() {
        if (id() == T::ID) {
          return static_cast<T*>(this);
        }
        return nullptr;
    }

private:
    QString mId;
};

REGISTER_METATYPE(Action)


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


#endif
