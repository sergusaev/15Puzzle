import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15

Item {
    id: root
    property string displayText : ""
    property bool isCurrent : false

    Rectangle {
        id: _tile_background
        anchors.centerIn: parent
        anchors.fill:parent
        radius: 10
        clip: true

        Image {
            id: _wood_3_img
            property bool rounded: true
            property bool adapt: true
            anchors.fill:parent
            anchors.centerIn: parent
            source: "../pics/wood_3.png"
            layer.enabled: rounded
            layer.effect: OpacityMask {
                maskSource: Item {
                    width: _wood_3_img.width
                    height: _wood_3_img.height
                    Rectangle {
                        anchors.centerIn: parent
                        width: _wood_3_img.adapt ? _wood_3_img.width : Math.min(_wood_3_img.width, _wood_3_img.height)
                        height: _wood_3_img.adapt ? _wood_3_img.height : width
                        radius: 10
                    }
                }
            }
        }
        Text {
            id: _tile_text
            text: root.displayText
            anchors.centerIn: parent
            font {
                pointSize: _tile_background.width / 2.5
                bold : true
            }
            color: isCurrent ? "white" :"#15000000"
            style: Text.Outline
            styleColor: isCurrent ? "white" : "dimgrey"
        }

    }
    DropShadow {
        anchors.fill: _tile_background
        horizontalOffset: 3
        verticalOffset: 3
        color: "black"
        source: _tile_background
    }
}
