import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import Dispatcher 1.0
import QmlActions 1.0

Window {
    id: root

    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    function dispatch(action) {
        action.dispatch(Dispatcher)
    }

    Component.onCompleted: {
        dispatch(QmlActions.navigateTo("qrc:/TodoEditor.qml"))
    }

    Navigator {
        anchors.fill: parent
    }
}
