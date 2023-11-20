# Flucxx Library (QML, C++)

An experiment in writing QML applications using the flux pattern, but combined with the type safety and speed of C++.

```
                             ┌──────────────────┐
                             │                  │
         ┌───────────────────┤      Action      ◄──────────────────┐
         │                   │                  │                  │
         │                   └──────────────────┘                  │
         │                                                         │
         │                                                         │
         │                                                         │
         │                                                         │
┌────────▼────────┐          ┌──────────────────┐            ┌─────┴────┐
│                 │          │                  │            │          │
│   Dispatcher    ├──────────►       Store      ├────────────►   View   │
│                 │          │                  │            │          │
└─────────────────┘          └──────────────────┘            └──────────┘
```

## 0. How to build

```bash
mkdir build && cd build
cmake ..
make -j
./examples/calculator/calculator_flucxx
```

## 1. Define Actions in C++

Let's define an action to create a todo entry for a todo list:

```cpp
struct ActionTodoCreate : public ActionWithMembers<ActionTodoCreate, QString, bool> {
  Q_OBJECT
public:
  static constexpr const char* ID = "todo/create";
  ACTION_PROPERTY(0, QString, text);
  ACTION_PROPERTY(1, bool, done);
  ActionTodoCreate(QString text, bool done) : ActionWithMembers(text, done) {}
};
REGISTER_METATYPE(ActionTodoCreate)
```

* Our action is a `ActionWithMembers` with 2 fields: A string and a boolean.
* The class needs to a `QObject`. We want to access it from QML.
* Every action must have a name `ID`.
* We can define the names of the getters for our fields using the `ACTION_PROPERTY` macro.
* Finally, we need to register our new type with the Qt type system.


## 2. Wrap Actions for use with QML

I know of no way to directly call the constructor of a C++ class.
We can however work around this by providing a QML singleton which can do so.
That's `QmlActions`. At first, this may look like a lot of redundancy. However, there are benefits to this: We know when the action is created in C++ vs. when it's created in QML. That way we have more control over our memory management. Also, we can provide additional features for QML land like promises (see advanced topics).

```cpp
class QmlActions : public QObject {
  Q_OBJECT
public:
  Q_INVOKABLE ActionTodoCreate* todoCreate(QString text, bool done) {
      return new ActionTodoCreate(text, done);
  }
};

int main() {
  ...
  REGISTER_SINGLETON(Dispatcher, new Dispatcher {});
  REGISTER_SINGLETON(QmlActions, new QmlActions {});
  ...
}
```

A created action should be passed to a dispatcher. \
We create one as another QML singleton.
In QML, we can then write:
```qml
import QmlActions 1.0
import Dispatcher 1.0
Dispatcher.dispatch(QmlActions.todoCreate("Todo text", false))
```


## 3. Creating a Todo Store

To handle todo creation actions, we need a store:
```cpp
class TodoStore : public Store {
public:
  Q_PROPERTY(TodoModel* items READ items)

  TodoStore() : Store("TodoStore") {}

  void process(Action* action, Dispatcher*, std::function<void(Action*)> next) {
    if (auto createAction = action->as<ActionTodoCreate>(); createAction) {
      auto item = new Todo(createAction->text(), createAction->done());
      mItems.add(item);
    }

    next();
  }

  TodoModel* items() { return &mItems; }

private:
  TodoModel mItems;
};
```

* We instantiate a model `TodoModel` to manage our todos, which can be a simple `QAbstractListModel`. Model not shown in this introduction.
* In `process()`, we check if the current action can be cast to `ActionTodoCreate`.
* If so, we create a new todo and put it into our model (which then may notify QML).

To use our store, we register it with the dispatcher and make it a QML singleton.

```cpp
int main() {
  ...
  auto dispatcher = QSharedPointer<Dispatcher>::create();
  auto todoStore = QSharedPointer<TodoStore>::create();
  dispatcher->addStore(todoStore);

  REGISTER_SINGLETON(Dispatcher, dispatcher.get());
  REGISTER_SINGLETON(TodoStore, todoStore.get());
  REGISTER_SINGLETON(QmlActions, new QmlActions {});
  ...
}
```

and this is how it's used in QML:
```qml
import TodoStore 1.0

ListView {
  model: TodoStore.items
}
```

## Advanced topics

### Middlewares

Every dispatched action can be filtered, extended or inspected using middlewares.

For example, let's create a logger middleware:
```cpp
class LoggerMiddleware : public Middleware {
public:
  void process(Action* action, Dispatcher*, std::function<void(Action*)> next) {
    QString type = action->metaObject()->className();
    qDebug() << "Action" << action->id() << "[" << type << "]";
    next(action);
  }
};
```

And then register it:
```cpp
int main() {
  ...
  auto loggerMiddleware = QSharedPointer<LoggerMiddleware>::create();
  dispatcher->addMiddleware(loggerMiddleware);
  ...
}
```

Astute readers will have noticed that the `process()` signature is the same as in stores.

### Actions that return Promises

We can create an action which takes a callback:
```cpp
struct ActionFetchUrl : public ActionWithMembers<ActionFetchUrl, QString, Callback<bool>> {
  Q_OBJECT
public:
  static constexpr const char* ID = "network/fetchUrl";
  ACTION_PROPERTY(0, QString, url);
  ACTION_PROPERTY(1, Callback<bool>, onDone);
  ActionFetchUrl(QString url, Callback<bool> onDone = {}) : ActionWithMembers(url, onDone) {}
};
REGISTER_METATYPE(ActionFetchUrl)


class QmlActions : public QObject {
  Q_OBJECT
public:
  Q_INVOKABLE ActionFetchUrl* fetch(QString url, QJSValue callback) {
    return new ActionFetchUrl(url, [callback](bool result) mutable {
      callback.call({result});
    });
  }
};
```

That way the following is possible in QML:

```qml
Button {
    onClicked: Dispatcher.dispatch(
        QmlActions.fetch("https://google.com",
        result => console.log("Fetch result: ", result)))
}
```

If we were to dispatch more actions inside these callbacks, we'd end up with callback hell. \
To mitigate this, we can refactor some of this and make use of JS promises.

1. Add support to `QmlActions`:
   ```cpp
    class QmlActions : public QObject {
      Q_OBJECT
    public:
      Q_INVOKABLE QJSValue* fetch(Dispatcher* dispatcher, QString url) {
        // Create a generic JS promise object
        auto promise = PromiseCallback::createPromise(qjsEngine(this));

        auto action = ActionFetchUrl(url, [callback = std::get<1>(promise)](bool result) {
          // Resolve or reject promise (callback into JS).
          // This could also be handled inside the store by
          // passing the JS promise as an action argument.
          if (result)
            callback->resolve("success");
          else
            callback->reject("unknown error");
          callback->deleteLater();
        });

        dispatcher->dispatch(&action);

        // Return JS promise object
        return std::get<0>(promise);
     }
   };
   ```

2. Now that the `QmlAction::fetch()` needs a `Dispacher` as an argument, we can use the promise like so:
   ```qml
   QmlActions.fetch(Dispatcher, "https://google.com")
        .then(success => console.log("Done fetching!"))
        .catch(err => console.log("Error while fetching!"))
   ```
   Or, if we want to hide the `Dispatcher`:
   ```qml
   function dispatchable(f) { return f.bind(this, Dispatcher) }

   dispatchable(QmlActions.fetch)("https://google.com")
        .then(success => console.log("Done fetching:", success))
        .catch(err => console.log("Error while fetching:", err))
   ```
3. This way, using promises, we can prevent nesting when chaining callbacks.
