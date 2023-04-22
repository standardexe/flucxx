import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Dialogs 1.3
import MainStore 1.0
import QmlActions 1.0
import Dispatcher 1.0

Item {
    id: root

    Component.onCompleted: {
        dispatch(QmlActions.todoCreate("first", false))
        dispatch(QmlActions.todoCreate("second", true))
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
                                dispatch(QmlActions.todoDelete(index))
                            } else {
                                dispatch(QmlActions.todoToggle(index))
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
                    dispatch(QmlActions.todoCreate(input.text, false))
                    input.text = ""
                }
            }

        }

        Button {
            text: "About"
            onClicked: dispatch(QmlActions.navigateTo("qrc:/About.qml"))
        }

        Button {
            text: "Sleep"
            onClicked: dispatch(QmlActions.sleep(100,
                                                 () => console.log("Sleep done.")))
        }

        Button {
            text: "Show dialog"
            onClicked: dispatch(QmlActions.showDialog("Ein Prompt",
                                                      result => console.log("Callback for show dialog! Result:", result)))
        }

    }

    Dialog {
        visible: MainStore.dialogVisible
        title: MainStore.dialogPrompt
        modality: Qt.ApplicationModal

        standardButtons: StandardButton.Yes | StandardButton.No

        onNo: dispatch(QmlActions.closeDialog(false))
        onYes: dispatch(QmlActions.closeDialog(true))
    }
}
