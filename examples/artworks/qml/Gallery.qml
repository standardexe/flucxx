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
                width: 100
                height: parent.height
                enabled: !MainStore.loading
                text: "<-"
                onClicked: dispatch(QmlActions.loadPage(Math.max(1, MainStore.page - 1)))
            }

            Text {
                text: MainStore.page
            }

            Button {
                width: 100
                height: parent.height
                Layout.alignment: Qt.AlignRight
                enabled: !MainStore.loading
                text: "->"
                onClicked: dispatch(QmlActions.loadPage(MainStore.page + 1))
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

                    Rectangle {
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: gridView.cellWidth / 3
                        height: gridView.cellHeight / 3

                        Image {
                            anchors.fill: parent
                            source: modelData.thumbnail
                            fillMode: Image.PreserveAspectFit
                        }
                        Image {
                            anchors.fill: parent
                            source: modelData.imageUrl
                            fillMode: Image.PreserveAspectFit
                        }
                    }

                    Text {
                        text: modelData.title + " [" + modelData.artist + "]"
                        width: parent.width
                        height: 40
                        wrapMode: Text.WordWrap
                        elide: Text.ElideRight
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onPressed: gridView.currentIndex = index
                    onDoubleClicked: dispatch(QmlActions.navigateTo("qrc:/Artwork.qml", { artwork: modelData }))
                }
            }

            highlight: Rectangle { color: "lightsteelblue" }
            highlightMoveDuration: 0

            focus: true
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
