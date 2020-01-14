import QtQuick 2.3
import QtQuick.Controls 2.4
import QtGraphicalEffects 1.0

Item {
    id: root
    signal clicked();
    property alias source: image.source

    Button {
        id: button
        anchors.fill: parent
        onClicked: root.clicked()

        background: Rectangle {
            anchors.fill: parent
            color: "transparent"
        }

        contentItem: Image {
            id: image
            anchors.fill: parent
            fillMode: Image.PreserveAspectFit
            mipmap: true
            smooth: true
        }

        DropShadow {
            id: shadow
            anchors.fill: image
            radius: 0
            samples: 40
            spread: 0.4
            color: "#80000000"
            source: image
        }

        onPressed: {
            shadow.radius = 20
        }
        onReleased: {
            shadow.radius = 0
        }
    }
}
