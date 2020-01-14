import QtQuick 2.11
import QtQuick.Controls 2.4
import Models 1.0

Rectangle {
    id: root

    width: 350
    height: 550
    color: "#ffffff"

    TitleLabel {
        id: tabTitleLabel
        text: "Player"
    }

    Item {
        id: visualisationVolumeItem
        x: 25
        y: 69
        width: 334
        height: 250
        anchors.bottom: titleLabel.top
        anchors.bottomMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter

        Frame {
            id: visualisationFrame
            y: -13
            width: 253
            height: 216
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
        }

        Item {
            id: volumeItem
            x: 262
            y: 21
            width: 53
            height: 200
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 10

            Slider {
                id: slider
                x: 489
                width: 22
                live: false
                to: 100
                from: 0
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: volumeLabel.top
                anchors.bottomMargin: 10
                anchors.top: parent.top
                anchors.topMargin: 0
                orientation: Qt.Vertical
                value: playerModel.volume
                onValueChanged: playerController.setPlayerVolume(value)
            }

            Label {
                id: volumeLabel
                x: 30
                y: 182
                text: qsTr("Volume")
                anchors.horizontalCenterOffset: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

    }

    Label {
        id: titleLabel
        x: 159
        y: 336
        width: 300
        height: 50
        text: playerModel.currentMedium.length == 0? "No media" : playerModel.currentMedium
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        lineHeight: 1
        fontSizeMode: Text.FixedSize
        renderType: Text.QtRendering
        textFormat: Text.PlainText
        font.weight: Font.Normal
        font.pointSize: 26
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: progressItem.top
        anchors.bottomMargin: 5
    }


    Item {
        id: progressItem
        y: 384
        height: 76
        anchors.right: parent.right
        anchors.rightMargin: 15
        anchors.left: parent.left
        anchors.leftMargin: 15
        anchors.bottom: buttonItem.top
        anchors.bottomMargin: 10

        Slider {
            id: progressSlider
            height: 40
            live: false
            anchors.right: parent.right
            anchors.rightMargin: 5
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: parent.top
            anchors.topMargin: 10
            from: 0
            to: playerModel.totalTime
            value: playerModel.currentTime
            onValueChanged: playerController.seekPlayerPosition(value)
        }

        Label {
            id: totalTimeLabel
            x: 220
            width: 33
            height: 17
            text: playerModel.totalTimeLabel
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.top: progressSlider.bottom
            anchors.topMargin: 5
        }

        Label {
            id: currentTimeLabel
            text: playerModel.currentTimeLabel
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.top: progressSlider.bottom
            anchors.topMargin: 5
        }
    }

    Item {
        id: buttonItem
        y: 447
        height: 70
        anchors.right: parent.right
        anchors.rightMargin: 15
        anchors.left: parent.left
        anchors.leftMargin: 15
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 15

        ImageButton {
            id: previousButton
            y: 109
            width: 60
            height: 60
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            source: "qrc:/resources/icons/previous.png"
            onClicked: playerController.playPrevious()
        }

        ImageButton {
            id: playPauseButton
            x: -59
            y: 109
            width: 60
            height: 60
            anchors.horizontalCenterOffset: -36
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            source: playerModel.playState === PlayState.PLAYING? "qrc:/resources/icons/pause.png" : "qrc:/resources/icons/play.png"
            onClicked: playerController.switchPlayState()
        }

        ImageButton {
            id: stopButton
            x: 117
            y: 109
            width: 60
            height: 60
            anchors.horizontalCenterOffset: 36
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            source: "qrc:/resources/icons/stop.png"
            onClicked: playerController.stopPlayer()
        }

        ImageButton {
            id: nextButton
            x: 198
            y: 109
            width: 60
            height: 60
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 20
            source: "qrc:/resources/icons/next.png"
            onClicked: playerController.playNext()
        }

    }













}

/*##^##
Designer {
    D{i:8;anchors_height:200;anchors_y:"-98"}
}
##^##*/
