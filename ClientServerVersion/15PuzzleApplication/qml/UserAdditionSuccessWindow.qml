import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15

Item {

    id: root
    signal okButtonClicked()

    Rectangle {
        id: _user_addition_success_window_wrapper
        anchors.fill: parent
        visible: true
        color: "#80ffffff"
        MouseArea {
            anchors.fill: parent
        }

        Rectangle {
            id:_user_addition_success_window
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 10
            height: width * 1.15
            anchors.verticalCenter: parent.verticalCenter
            radius: 10

            Image {
                id: _user_addition_success_window_background
                property bool rounded: true
                property bool adapt: true
                anchors.fill: parent

                source: "../pics/wood_5.png"
                layer.enabled: rounded
                layer.effect: OpacityMask {
                    maskSource: Item {
                        width: _user_addition_success_window_background.width
                        height: _user_addition_success_window_background.height
                        Rectangle {
                            anchors.centerIn: parent
                            width: _user_addition_success_window_background.adapt ? _user_addition_success_window_background.width : Math.min(_user_addition_success_window_background.width, _user_addition_success_window_background.height)
                            height: _user_addition_success_window_background.adapt ? _user_addition_success_window_background.height : width
                            radius: _user_addition_success_window.radius
                        }
                    }
                }



            }

            CustomText {
                id: _user_addition_success_text
                text: qsTr("User successfully added")
                fontPointSize: 30
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: parent.height / 3
            }

            CustomButton {
                id: _user_addition_success_window_to_authorization_page_button
                width: parent.width * 0.5
                height: width * 0.4
                z: root.z + 1
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: _user_addition_success_text.bottom
                anchors.topMargin: parent.height / 4
                text: qsTr("OK")
                onClicked: root.okButtonClicked()
            }

        }

        DropShadow {
            anchors.fill: _user_addition_success_window
            horizontalOffset: 6
            verticalOffset: 6
            color: "black"
            source: _user_addition_success_window
        }
    }

}
