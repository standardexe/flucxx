#ifndef QML_ACTIONS_HPP
#define QML_ACTIONS_HPP

#include "actions/CalculatorActions.hpp"

class QmlActions : public QObject {
    Q_OBJECT
public:
    QmlActions() = default;

    Q_INVOKABLE ActionDigit* inputDigit(int digit) { return new ActionDigit(digit); }
    Q_INVOKABLE ActionOperator* inputOperator(QString op) { return new ActionOperator(op); }
};

#endif // QML_ACTIONS_HPP
