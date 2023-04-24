import QtQuick 2.15
import QtQuick.Controls 2.15
import NavigationStore 1.0

Item {
    property var model: null

    Connections {
        target: model

        function onScreenPushed(url) {
            stackView.push(url, model.currentParams)
        }

        function onScreenPopped() {
            stackView.pop()
            if (stackView.empty && model.current !== "") {
                stackView.push(model.current)
            }
        }
    }

    Component.onCompleted: {
        model = NavigationStore.screens

        if (model.current !== "") {
            stackView.push(model.current, model.currentParams)
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent

        pushEnter: Transition {}
        popEnter: Transition {}
        pushExit: Transition {}
        popExit: Transition {}
    }
}
