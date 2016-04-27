import QtQuick 2.5

Rectangle {
    id: joystick

    property real minX: -1
    property real maxX: 1
    property real minY: -1
    property real maxY: 1
    property bool returning: true
    property real deviationX: minX + (maxX - minX) * handle.x /
                              (joystick.width - handle.width)
    property real deviationY: minY + (maxY - minY) * handle.y /
                              (joystick.height - handle.height)

    width: 128
    height: width
    color: "transparent"
    border.width: 2
    border.color: palette.textColor
    radius: width / 2

    Rectangle {
        id: handle
        x: (joystick.width - handle.width) / 2
        y: (joystick.height - handle.height) / 2
        width: joystick.width / 4
        height: width
        color: "transparent"
        border.width: 2
        border.color: palette.textColor
        radius: width / 2
    }

    MouseArea {
        anchors.fill: parent
        drag.target: handle
        drag.axis: Drag.XAndYAxis
        drag.minimumX: 0
        drag.maximumX: joystick.width - handle.width
        drag.minimumY: 0
        drag.maximumY: joystick.height - handle.height
        onReleased: {
            if (!returning) return;
            handle.x = (joystick.width - handle.width) / 2;
            handle.y = (joystick.height - handle.height) / 2;
        }
    }
}
