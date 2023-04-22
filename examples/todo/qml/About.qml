import QtQuick 2.15
import QtQuick.Controls 2.15
import QmlActions 1.0

Item {
    Column {
        Text {
            text: "flucxx"
        }
        Text {
            text: "Test"
        }

        Button {
            text: "Back"
            onClicked: {
                dispatch(QmlActions.navigateBack())
            }
        }
    }
}
