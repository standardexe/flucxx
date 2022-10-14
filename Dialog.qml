import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    property alias prompt: text.text

    signal cancel()
    signal ok()

    width: 300
    height: 180
    color: "gray"

    Column {
        spacing: 10
        Text { id: text; height: 100; width: parent.width }
        Row {
            height: 50
            spacing: 10
            Button { text: "Cancel"; onClicked: cancel() }
            Button { text: "OK"; onClicked: ok() }
        }
    }
}
