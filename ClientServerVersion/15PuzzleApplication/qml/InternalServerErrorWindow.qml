import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15

Item {

    id: root
    signal tryAgainButtonClicked()

    Rectangle {
        id: _internal_server_error_window_wrapper
        anchors.fill: parent
        visible: true
        color: "#80ffffff"
        MouseArea {
            anchors.fill: parent
        }

        Rectangle {
            id:_internal_server_error_window
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 10
            height: width * 1.15
            anchors.verticalCenter: parent.verticalCenter
            radius: 10

            Image {
                id: _internal_server_error_window_background
                property bool rounded: true
                property bool adapt: true
                anchors.fill: parent

                source: "../pics/wood_5.png"
                layer.enabled: rounded
                layer.effect: OpacityMask {
                    maskSource: Item {
                        width: _internal_server_error_window_background.width
                        height: _internal_server_error_window_background.height
                        Rectangle {
                            anchors.centerIn: parent
                            width: _internal_server_error_window_background.adapt ? _internal_server_error_window_background.width : Math.min(_internal_server_error_window_background.width, _internal_server_error_window_background.height)
                            height: _internal_server_error_window_background.adapt ? _internal_server_error_window_background.height : width
                            radius: _internal_server_error_window.radius
                        }
                    }
                }



            }

            CustomText {
                id: _internal_server_error_text
                text: qsTr("Oops! Server error :(")
                fontPointSize: 30
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: parent.height / 3
            }

            CustomButton {
                id: _try_again_button
                width: parent.width * 0.5
                height: width * 0.4
                z: root.z + 1
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: _internal_server_error_text.bottom
                anchors.topMargin: parent.height / 4
                text: qsTr("Try again")
                onClicked: root.tryAgainButtonClicked()
            }

        }

        DropShadow {
            anchors.fill: _internal_server_error_window
            horizontalOffset: 6
            verticalOffset: 6
            color: "black"
            source: _internal_server_error_window
        }
    }

}
