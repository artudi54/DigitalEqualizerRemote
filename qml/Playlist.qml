import QtQuick 2.0
import QtQuick.Controls 2.3

Rectangle {
    id: element

    width: 350
    height: 550
    color: "#ffffff"

    TitleLabel {
        id: tabTitleLabel
        text: "Playlist"
    }

    ListView {
        id: playlistView
        anchors.top: tabTitleLabel.bottom
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        highlightFollowsCurrentItem: true

        currentIndex: playerModel.currentIndex
        model: playerModel.playlist
        onModelChanged: currentIndex = -1
        onCurrentIndexChanged: playerController.setPlayedSource(currentIndex)

        delegate: Rectangle {
            width: parent.width
            height: 60
            color: "transparent"
            Label {
                anchors.centerIn: parent
                text: modelData
                font.bold: true
                anchors.verticalCenter: parent.verticalCenter
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
            MouseArea {
                 z: 1
                 hoverEnabled: false
                 anchors.fill: parent
                 onClicked: playlistView.currentIndex = index
            }
        }
        highlight: Rectangle {
            color: "lightblue"
        }
    }
}

/*##^##
Designer {
    D{i:1;anchors_width:349;anchors_x:80;anchors_y:31}D{i:3;anchors_height:242;anchors_width:226;anchors_x:43;anchors_y:148}
D{i:2;anchors_height:242;anchors_width:226;anchors_x:159;anchors_y:30}
}
##^##*/
