import QtQuick 2.0
import QtQuick.Controls 2.3
import Models 1.0

Item {
    id: element
    property EqualizerBand equalizerBand
    property alias value: valueSlider.value

    Label {
        id: maxValueLabel
        text: "20dB"
        font.pointSize: 8
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
    }

    Slider {
        id: valueSlider
        anchors.bottom: minValueLabel.top
        anchors.bottomMargin: 0
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: maxValueLabel.bottom
        anchors.topMargin: 0
        orientation: Qt.Vertical
        live: false
        from: -20
        to: 20
        value: equalizerBand.value
    }

    Label {
        id: minValueLabel
        text: "-20db"
        font.pointSize: 8
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: nameLabel.top
        anchors.bottomMargin: 5
    }

    Label {
        id: nameLabel
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        anchors.horizontalCenter: parent.horizontalCenter
        text: equalizerBand.name
        font.pointSize: 10
    }



}

/*##^##
Designer {
    D{i:0;autoSize:true;height:200;width:70}D{i:1;anchors_x:8;anchors_y:121}D{i:3;anchors_x:23}
}
##^##*/
