import QtQuick 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15
import MainStore 1.0
import QmlActions 1.0

Item {
    id: root

    ColumnLayout {
        anchors.fill: parent

        GridLayout {
            Layout.preferredWidth: parent.width
            Layout.preferredHeight: 50

            columns: 3
            rows: 1

            Button {
                enabled: !MainStore.loading && MainStore.page > 1
                text: "<-"
                onClicked: dispatchable(QmlActions.loadPage)(MainStore.page - 1)
            }

            Text {
                text: MainStore.page
            }

            Button {
                Layout.alignment: Qt.AlignRight
                enabled: !MainStore.loading
                text: "->"
                onClicked: dispatchable(QmlActions.loadPage)(MainStore.page + 1)
            }
        }

        GridView {
            id: gridView

            Layout.fillHeight: true
            Layout.preferredWidth: parent.width

            cellWidth: 300
            cellHeight: 180

            model: MainStore.artworks
            clip: true

            delegate: Item {
                width: gridView.cellWidth - 40
                height: gridView.cellHeight - 40

                Column {
                    spacing: 10
                    topPadding: 20
                    width: parent.width

                    Image {
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: gridView.cellWidth / 3
                        height: gridView.cellHeight / 3

                        source: modelData.thumbnail
                        fillMode: Image.PreserveAspectFit

                        Image {
                            anchors.fill: parent
                            source: modelData.imageUrl
                            fillMode: Image.PreserveAspectFit
                        }
                    }

                    Text {
                        width: parent.width
                        height: 40
                        text: modelData.title + " [" + modelData.artist + "]"
                        wrapMode: Text.WordWrap
                        elide: Text.ElideRight
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onPressed: gridView.currentIndex = index
                    onDoubleClicked: dispatchable(QmlActions.navigateTo)("qrc:/Artwork.qml", { artwork: modelData })
                }
            }

            highlight: Rectangle { color: "lightsteelblue" }
            highlightMoveDuration: 0
        }
    }

    Rectangle {
        color: "red"
        visible: MainStore.hasError
        width: 150
        height: 50
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 5
        Label {
            anchors.centerIn: parent
            text: MainStore.error
        }
    }

    Rectangle {
      color: "white"
      visible: MainStore.loading
      anchors.fill: parent
      Label {
          anchors.centerIn: parent
          text: "Loading..."
      }
    }

}
