import QtQuick 2.0
import QtQuick.Controls 2.3

Rectangle {
    id: root

    width: 350
    height: 550
    color: "#ffffff"

    TitleLabel {
        id: titleLabel
        text: "Equalizer"
    }

    Item {
        id: equalizerParametersItem
        width: 330
        height: 180
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: titleLabel.bottom
        anchors.topMargin: 30

        //        EqualizerBandControl {
        //            id: dbGainControl
        //            width: 50
        //            height: parent.height
        //            anchors.left: parent.left
        //            anchors.leftMargin: 10
        //            anchors.verticalCenter: parent.verticalCenter
        //            equalizerBand: playerModel.equalizerParameters.dbGain
        //        }

        ListView {
            id: frequencyDbGainsView
            height: parent.height
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.verticalCenter: parent.verticalCenter
            orientation: ListView.Horizontal
            model: playerModel.equalizerParameters.frequencyDbGains

            delegate: EqualizerBandControl {
                width: 33
                height: parent.height
                equalizerBand: modelData
                onValueChanged: playerController.setEqualizerBandValue(value, index)
            }
        }
    }


    Item {
        id: dialItem
        y: 249
        height: 196
        anchors.right: parent.right
        anchors.rightMargin: 25
        anchors.left: parent.left
        anchors.leftMargin: 25
        anchors.bottom: resetButton.top
        anchors.bottomMargin: 10

        DescriptiveDial {
            id: volumeDial
            width: 140
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            name: "Volume"
            from: 0
            fromName: "0"
            to: 100
            toName: "100"
            value: playerModel.volume
            onValueChanged: playerController.setPlayerVolume(value)
        }

        DescriptiveDial {
            id: overallGainDial
            name: "Overall gain"
            width: 140
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            from: -20
            fromName: "-20db"
            to: 20
            toName: "20db"
            value: playerModel.equalizerParameters.dbGain.value
            onValueChanged: playerController.setOverallGainValue(value)

        }
    }

    Button {
        id: resetButton
        x: 45
        y: 478
        height: 35
        text: qsTr("Reset")
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: playerController.resetEqualizer()
    }
}

/*##^##
Designer {
    D{i:4;anchors_width:110;anchors_x:100}D{i:3;anchors_x:"-43"}D{i:2;anchors_y:113}D{i:6;anchors_height:185;anchors_width:162;anchors_x:8;anchors_y:71}
D{i:7;anchors_height:185;anchors_width:162;anchors_x:-105;anchors_y:71}D{i:5;anchors_width:323;anchors_x:17}
}
##^##*/
