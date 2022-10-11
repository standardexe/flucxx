import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import Dispatcher 1.0
import Actions 1.0

Window {
    id: root

    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    function dispatch(action) {
        return Dispatcher.dispatch(action)
    }

    Component.onCompleted: {
        dispatch(Actions.navigateTo("qrc:/TodoEditor.qml"))
    }

    Navigator {
        anchors.fill: parent
    }
}
