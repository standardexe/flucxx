import QtQuick 2.15
import QtQuick.Window 2.15
import Dispatcher 1.0
import QmlActions 1.0

Window {
    id: root

    width: 640
    height: 480
    visible: true
    title: qsTr("Artwork Gallery")

    function dispatch(action) {
        action.dispatch(Dispatcher)
    }

    Component.onCompleted: {
        dispatch(QmlActions.loadPage(1))
        dispatch(QmlActions.navigateTo("qrc:/Gallery.qml", {}))
    }

    Navigator {
        anchors.fill: parent
    }
}
