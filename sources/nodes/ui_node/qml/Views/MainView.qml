import QtQuick 2.5

Rectangle {
    id: main
    color: "#2c3e50"

    StatusView {
        id: status
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
    }

    Row {
        anchors.top: status.bottom
        anchors.left: parent.left
        anchors.margins: 4
        spacing: 4
        width: parent.width
        height: parent.height - status.height

        Column {
            id: dashboard
            anchors.top: parent.top
            spacing: 4

            FlightDirectorView {
                id: flightDirector
                pitch: boardService.pitch
                roll: boardService.roll
                yaw: boardService.yaw
                velocity: boardService.velocity
                altitude: boardService.barAltitude
            }

            Row {
                anchors.horizontalCenter: parent.horizontalCenter

                Text {
                    text: qsTr("FIX: ") + boardService.snsFix
                    font.pointSize: 14
                    color: "#ecf0f1"
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            VideoView {
                id: video
                width: parent.width
                height: width * 3 / 4
            }
        }

        MapView {
            id: map
            width: parent.width - dashboard.width
            height: parent.height
        }
    }
}
