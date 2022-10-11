import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QuickFuture 1.0
import MainStore 1.0
import Actions 1.0
import Dispatcher 1.0

Item {
    id: root

    Component.onCompleted: {
        dispatch(Actions.todoCreate("first", false))
        dispatch(Actions.todoCreate("second", true))
    }

    Column {
        width: parent.width

        Rectangle {
            height: 200
            width: parent.width
            border.color: "black"

            ListView {
                id: list
                anchors.fill: parent
                anchors.margins: 5
                model: MainStore.todoItems

                delegate: Rectangle {
                    height: 50
                    width: list.width

                    Text {
                        anchors.fill: parent
                        anchors.rightMargin: 30
                        text: item.text
                        font.strikeout: item.done
                    }

                    Button {
                        anchors.right: parent.right
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        width: 30
                        text: item.done ? "✖" : "✓"

                        onClicked: {
                            if (item.done) {
                                dispatch(Actions.todoDelete(index))
                            } else {
                                dispatch(Actions.todoToggle(index))
                            }
                        }
                    }

                }
            }
        }

        Rectangle {
            height: 50
            width: parent.width

            Rectangle {
                anchors.left: parent.left
                anchors.top: parent.top
                width: parent.width - 50
                height: parent.height
                border.color: "black"

                TextEdit {
                    id: input
                    anchors.fill: parent
                    anchors.margins: 3
                }
            }

            Button {
                height: parent.height
                anchors.right: parent.right
                width: 50
                text: "Add"

                onClicked: {
                    dispatch(Actions.todoCreate(input.text, false))
                    input.text = ""
                }
            }

        }

        Button {
            text: "About"
            onClicked: dispatch(Actions.navigateTo("qrc:/About.qml"))
        }

        Button {
            text: "Sleep"
            onClicked: {
                let response = dispatch(Actions.sleep(1000))
                Future.promise(response).then(value => console.log("Response from dispatch:", value))
            }
        }
    }

}
