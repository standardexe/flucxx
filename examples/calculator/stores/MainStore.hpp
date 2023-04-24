#ifndef STORE_MAIN_HPP
#define STORE_MAIN_HPP

#include <QObject>
#include "flucxx/store.hpp"
#include "actions/CalculatorActions.hpp"

class MainStore : public Store {
    Q_OBJECT
public:
    Q_PROPERTY(QString displayText READ getDisplay NOTIFY displayChanged)

    MainStore() : Store("MainStore") {}

    void process(Action* action, Dispatcher*, std::function<void(Action*)> next) final {
        if (auto digitAction = action->as<ActionDigit>(); digitAction) {
            mCurrentNumber = mCurrentNumber * 10 + digitAction->digit();
            updateDisplay(QString::number(mCurrentNumber));
        }
        else if (auto operatorAction = action->as<ActionOperator>(); operatorAction) {
            if (mNextOp == "+") { mCurrentNumber = mLastNumber + mCurrentNumber; }
            if (mNextOp == "-") { mCurrentNumber = mLastNumber - mCurrentNumber; }
            if (mNextOp == "*") { mCurrentNumber = mLastNumber * mCurrentNumber; }
            if (mNextOp == "/") { mCurrentNumber = mLastNumber / mCurrentNumber; }

            if (operatorAction->op() == "=") {
              mNextOp = "";
              updateDisplay(QString::number(mCurrentNumber));
            } else {
              mNextOp = operatorAction->op();
              mLastNumber = mCurrentNumber;
              mCurrentNumber = 0;
              updateDisplay(QString::number(mLastNumber));
            }
        }

        next(action);
    }

    QString getDisplay() const { return mDisplayText; }

signals:
    void displayChanged();

private:
    QString mDisplayText = "0";
    int mCurrentNumber = 0;
    int mLastNumber = 0;
    QString mNextOp = "";

    void updateDisplay(QString const& text) {
        mDisplayText = text;
        displayChanged();
    }
};

#endif // STORE_MAIN_HPP
