import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15


Item {
    id: root

    Rectangle {
        id: _invalid_password_window_wrapper
        anchors.fill: parent
        visible: true
        color: "#80ffffff"
        MouseArea {
            anchors.fill: parent
        }

        Rectangle {
            id:_invalid_password_window
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 10
            height: width * 1.15
            anchors.verticalCenter: parent.verticalCenter
            radius: 10

            Image {
                id: _invalid_password_window_background
                property bool rounded: true
                property bool adapt: true
                anchors.fill: parent

                source: "../pics/wood_5.png"
                layer.enabled: rounded
                layer.effect: OpacityMask {
                    maskSource: Item {
                        width: _invalid_password_window_background.width
                        height: _invalid_password_window_background.height
                        Rectangle {
                            anchors.centerIn: parent
                            width: _invalid_password_window_background.adapt ? _invalid_password_window_background.width : Math.min(_invalid_password_window_background.width, _invalid_password_window_background.height)
                            height: _invalid_password_window_background.adapt ? _invalid_password_window_background.height : width
                            radius: _invalid_password_window.radius
                        }
                    }
                }



            }

            CustomText {
                id: _wrong_password_text
                text: qsTr("Wrong password!")
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
                anchors.top: _wrong_password_text.bottom
                anchors.topMargin: parent.height / 4
                text: qsTr("Try again")
                onClicked: root.visible = false
            }

        }

        DropShadow {
            anchors.fill: _invalid_password_window
            horizontalOffset: 6
            verticalOffset: 6
            color: "black"
            source: _invalid_password_window
        }
    }

}
