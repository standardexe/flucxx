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

    function dispatchable(f) {
        return f.bind(this, Dispatcher)
    }

    Component.onCompleted: {
        dispatchable(QmlActions.loadPage)(1)
            .then((success) => console.log("DONE LOADING PAGE 1. Result: ", success))
            .catch((err) => console.log("ERROR LOADING PAGE 1: ", err))

        dispatchable(QmlActions.navigateTo)("qrc:/Gallery.qml", {})
    }

    Navigator {
        anchors.fill: parent
    }
}
