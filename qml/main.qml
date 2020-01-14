import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3

ApplicationWindow {
    width: 350
    height: 580

    maximumWidth: 350
    maximumHeight: 580

    minimumWidth: 350
    minimumHeight: 580

    MessageDialog {
        id: messageDialog

        width: 500
        height: 500

        title: "Connection failed"

        icon: StandardIcon.Critical
        standardButtons: Qt.Yes | Qt.No

        onAccepted: playerController.connectToHost()
        onRejected: playerController.errorCloseApplication();

        Component.onCompleted: visible = false
    }

    Rectangle {
        id: connectingRectangle
        color: "#ffffff"
        anchors.fill: parent
        z: parent.z + 1
        visible: false

        Connections {
            target: connectionModel
            onStartedConnecting: connectingRectangle.visible = true
            onConnected:  connectingRectangle.visible = false
            onErrorOccurred: {
                messageDialog.text = "Connection error occurred: " + message + ". Retry?"
                messageDialog.visible = true
            }
        }

        BusyIndicator {
            id: connectingIndicator
            anchors.fill: parent

            Label {
                id: connectingLabel
                text: "Connecting..."
                font.pointSize: 19
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.fill: parent
            }
        }
    }

    TabBar {
        id: bar
        height: 30
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        currentIndex: 1

        TabButton {
            text: "Equalizer"
        }
        TabButton {
            text: "Player"
        }
        TabButton {
            text: "Playlist"
        }
    }

    StackLayout {
        anchors.top: bar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        currentIndex: bar.currentIndex
        Equalizer {}
        Player {}
        Playlist {}
    }
}
