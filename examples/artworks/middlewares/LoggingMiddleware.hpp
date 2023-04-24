#ifndef LOGGING_MIDDLEWARE_HPP
#define LOGGING_MIDDLEWARE_HPP

#include <QDebug>
#include <QMetaProperty>
#include "flucxx/middleware.hpp"
#include <QtConcurrent/QtConcurrent>

class LoggingMiddleware : public Middleware {
public:
    void process(Action* action, Dispatcher*, std::function<void(Action*)> next) final {
        dumpProperties(action);
        next(action);
    }

    static void dumpProperties(Action* action) {
        auto metaObject = action->metaObject();

        qDebug() << "Action" << action->id() << "[" << metaObject->className() << "]";

        std::vector<std::pair<QString, QVariant>> properties;
        properties.reserve(metaObject->propertyCount() - metaObject->propertyOffset());

        for (int i = metaObject->propertyOffset(); i < metaObject->propertyCount(); i++) {
            properties.emplace_back(metaObject->property(i).name(), metaObject->property(i).read(action));
        }

        std::sort(properties.begin(), properties.end());
        for (auto const& property : properties) {
            qDebug() << "  " << property.first << "=>" << property.second;
        }
    }
};

#endif // LOGGING_MIDDLEWARE_HPP
