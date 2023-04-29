import QtQuick 2.15
import QtQuick.Controls 2.15
import QmlActions 1.0

ScrollView {
    id: root

    property var artwork

    Column {
        Image {
            width: root.width - 40
            source: artwork.imageUrl
            fillMode: Image.PreserveAspectFit
        }

        Text {
            text: artwork.title + " by " + artwork.artist
        }

        Button {
            text: "Back"
            onClicked: dispatchable(QmlActions.navigateBack)()
        }
    }
}
