import QtQuick 2.0
import QtQuick.Controls 2.3

Item {
    id: element
    property alias name: nameLabel.text
    property alias from: dial.from
    property alias fromName: minLabel.text
    property alias to: dial.to
    property alias toName: maxLabel.text
    property alias value: dial.value

    Dial {
        id: dial
        anchors.bottom: nameLabel.top
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.bottomMargin: 5
        anchors.topMargin: 10
        live: false

        Label {
            id: minLabel
            x: -10
            y: 272
            verticalAlignment: Text.AlignVCenter
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
        }

        Label {
            id: maxLabel
            x: 0
            y: -18
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
        }
    }

    Label {
        id: nameLabel
        font.pointSize: 16
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:300;width:300}D{i:2;anchors_x:10}
}
##^##*/
