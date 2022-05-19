import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15

Item {
    id: root
    property real displayHeight : 20
    property real displayWidth : 80
    property string displayText : ""

    Rectangle{
        id: _caption
        height: root.displayHeight
        width: root.displayWidth
        color: "lightgrey"
        anchors.centerIn: parent
        radius: 5
        Rectangle {
            anchors.fill: parent
            anchors.margins: 5
            color : "black"
            radius: 5
            Text {
                color: "white"
                font {
                    pointSize: Math.min(parent.width, parent.height) / 2
                    bold : true
                }
                anchors.centerIn: parent
                text: root.displayText
            }

        }

    }
    DropShadow {
        anchors.fill: _caption
        horizontalOffset: 3
        verticalOffset: 3
        spread: 0.25
        radius: 4.0
        samples: 9
        color: "black"
        source: _caption
    }
}
