import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15


Item {
    id: root

    Rectangle {
        id: _connecting_to_server_window_wrapper
        anchors.fill: parent
        visible: true
        color: "#80ffffff"
        MouseArea {
            anchors.fill: parent
        }

        Rectangle {
            id:_connecting_to_server_window
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 10
            height: width * 1.15
            anchors.verticalCenter: parent.verticalCenter
            radius: 10

            Image {
                id: _connecting_to_server_window_background
                property bool rounded: true
                property bool adapt: true
                anchors.fill: parent

                source: "../pics/wood_5.png"
                layer.enabled: rounded
                layer.effect: OpacityMask {
                    maskSource: Item {
                        width: _connecting_to_server_window_background.width
                        height: _connecting_to_server_window_background.height
                        Rectangle {
                            anchors.centerIn: parent
                            width: _connecting_to_server_window_background.adapt ? _connecting_to_server_window_background.width : Math.min(_connecting_to_server_window_background.width, _connecting_to_server_window_background.height)
                            height: _connecting_to_server_window_background.adapt ? _connecting_to_server_window_background.height : width
                            radius: _connecting_to_server_window.radius
                        }
                    }
                }



            }

            CustomText {
                id: _connecting_to_server_text
                text: qsTr("Connecting to server...")
                fontPointSize: 30
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: parent.height / 3
            }

            BusyIndicator {
                id: _connecting_to_server_indicator
                anchors.centerIn: parent
            }


        }
        DropShadow {
            anchors.fill: _connecting_to_server_window
            horizontalOffset: 6
            verticalOffset: 6
            color: "black"
            source: _connecting_to_server_window
        }

    }
}
