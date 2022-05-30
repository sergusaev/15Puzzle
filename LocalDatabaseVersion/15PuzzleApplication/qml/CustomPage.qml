import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15


Page {
    id: root
    Rectangle {
        anchors.fill:parent
        Image {
            id: _wood_1_img
            anchors.fill:parent
            source: "../pics/wood_1.png"

            Rectangle {
                id: _main_layer
                anchors.fill:parent
                anchors.centerIn: parent
                anchors.margins: root.width / 20
                radius: anchors.margins
                Image {
                    id: _wood_5_img
                    property bool rounded: true
                    property bool adapt: true

                    anchors.fill:parent
                    source: "../pics/wood_5.png"
                    layer.enabled: rounded
                    layer.effect: OpacityMask {
                        maskSource: Item {
                            width: _wood_5_img.width
                            height: _wood_5_img.height
                            Rectangle {
                                anchors.centerIn: parent
                                width: _wood_5_img.adapt ? _wood_5_img.width : Math.min(_wood_5_img.width, _wood_5_img.height)
                                height: _wood_5_img.adapt ? _wood_5_img.height : width
                                radius: _main_layer.radius
                            }
                        }
                    }
                    Rectangle {
                        id:_transparent_rect
                        color: "transparent"
                        anchors.centerIn: parent
                        anchors.horizontalCenterOffset: 3
                        anchors.verticalCenterOffset: 3
                        height: parent.height + 5
                        width: parent.width + 5
                        border.width : 5
                        border.color: "#65000000"

                        radius: _main_layer.radius

                    }
                    DropShadow {
                        anchors.fill: _transparent_rect
                        horizontalOffset: 3
                        verticalOffset: 3
                        color: "black"
                        source: _transparent_rect
                    }
                }

                Image {
                    id: _wood_5_frame_img
                    z: _wood_5_img.z + 1
                    source: "../pics/custom_page_frame.png"
                    property bool rounded: true
                    property bool adapt: true
                    anchors.fill: parent
                    fillMode: Image.Stretch

                    layer.enabled: rounded
                    layer.effect: OpacityMask {
                        maskSource: Item {
                            width: _wood_5_frame_img.width
                            height: _wood_5_frame_img.height
                            Rectangle {
                                anchors.centerIn: parent
                                width: _wood_5_frame_img.adapt ? _wood_5_frame_img.width : Math.min(_wood_5_frame_img.width, _wood_5_frame_img.height)
                                height: _wood_5_frame_img.adapt ? _wood_5_frame_img.height : width
                                radius: _main_layer.radius
                            }
                        }
                    }
                }


            }
        }
    }
}
