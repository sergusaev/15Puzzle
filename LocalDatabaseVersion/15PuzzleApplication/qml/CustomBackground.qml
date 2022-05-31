import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.15

Item {
    id: root
    property alias radius: _inner_rect.radius

    Rectangle {
        id:_inner_rect
        anchors.fill: parent
        radius: 10

        Image {
            id: _custom_background_img
            property bool rounded: true
            property bool adapt: true
            anchors.fill: parent
            source: "../pics/wood_5.png"
            layer.enabled: rounded
            layer.effect: OpacityMask {
                maskSource: Item {
                    width: _custom_background_img.width
                    height: _custom_background_img.height
                    Rectangle {
                        anchors.centerIn: parent
                        width: _custom_background_img.adapt ? _custom_background_img.width : Math.min(_custom_background_img.width, _custom_background_img.height)
                        height: _custom_background_img.adapt ? _custom_background_img.height : width
                        radius: _inner_rect.radius
                    }
                }
            }
        }

        Image {
            id: _custom_background_frame_img
            z: _custom_background_img.z + 1
            source: "../pics/frame_1.png"
            property bool rounded: true
            property bool adapt: true
            anchors.fill: parent
            layer.enabled: rounded
            layer.effect: OpacityMask {
                maskSource: Item {
                    width: _custom_background_frame_img.width
                    height: _custom_background_frame_img.height
                    Rectangle {
                        anchors.centerIn: parent
                        width: _custom_background_frame_img.adapt ? _custom_background_frame_img.width : Math.min(_custom_background_frame_img.width, _custom_background_frame_img.height)
                        height: _custom_background_frame_img.adapt ? _custom_background_frame_img.height : width
                        radius: _inner_rect.radius
                    }
                }
            }
        }
    }
}
