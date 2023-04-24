import QtQuick 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import Dispatcher 1.0
import QmlActions 1.0
import MainStore 1.0

Window {
    id: root

    width: 450
    height: 280
    visible: true
    title: "flucxx calculator"

    GridLayout {
        id: layout
        columns: 4
        rows: 5

        anchors.fill: parent

        Text {
            width: parent.width
            Layout.columnSpan: layout.columns
            Layout.rowSpan: 1
            text: MainStore.displayText
        }

        Repeater {
            model: ["7", "8", "9", "+",
                    "4", "5", "6", "-",
                    "1", "2", "3", "*",
                    " ", "0", "=", "/"]

            delegate: Button {
                text: modelData
                opacity: text != " " ? 1 : 0
                enabled: text != " "
                onClicked: {
                    if ("0123456789".includes(text)) {
                        QmlActions.inputDigit(text).dispatch(Dispatcher)
                    } else {
                        QmlActions.inputOperator(text).dispatch(Dispatcher)
                    }
                }
            }

        }

    }
}
