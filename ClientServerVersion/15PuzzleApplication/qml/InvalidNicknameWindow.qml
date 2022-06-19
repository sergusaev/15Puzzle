import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15
import AuthorizationManager 1.0

Item {
    id:root

    property alias windowVisible: _invalid_nickname_window_wrapper.visible
    signal newUserButtonClicked()

    Rectangle {
        id: _invalid_nickname_window_wrapper
        anchors.fill: parent
        visible: true
        color: "#80ffffff"

        Rectangle {
            id:_invalid_nickname_window
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 10
            height: width * 1.15
            anchors.verticalCenter: parent.verticalCenter
            radius: 10

            Image {
                id: _invalid_nickname_window_background
                property bool rounded: true
                property bool adapt: true
                anchors.fill: parent

                source: "../pics/wood_5.png"
                layer.enabled: rounded
                layer.effect: OpacityMask {
                    maskSource: Item {
                        width: _invalid_nickname_window_background.width
                        height: _invalid_nickname_window_background.height
                        Rectangle {
                            anchors.centerIn: parent
                            width: _invalid_nickname_window_background.adapt ? _invalid_nickname_window_background.width : Math.min(_invalid_nickname_window_background.width, _invalid_nickname_window_background.height)
                            height: _invalid_nickname_window_background.adapt ? _invalid_nickname_window_background.height : width
                            radius: _invalid_nickname_window.radius
                        }
                    }
                }



            }
            CustomText {
                id: _invalid_nickname_text
                text: qsTr("No such player found")
                fontPointSize: 30
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: parent.height / 10
            }


            CustomButton {
                id: _new_player_button
                width: parent.width * 0.45
                height: width * 0.4
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.top: _invalid_nickname_text.bottom
                anchors.topMargin: parent.height / 14
                text: qsTr("New player")

                onClicked:  {
                    root.windowVisible = false
                    root.newUserButtonClicked()
                }
            }

            CustomButton {
                id: _to_authorization_window_button
                width: parent.width * 0.45
                height: width * 0.4
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.top: _invalid_nickname_text.bottom
                anchors.topMargin: parent.height / 14
                text: qsTr("Back")
                onClicked:  {
                    root.windowVisible = false
                    if(_stack_view.depth > 1) {
                        _stack_view.pop()
                    }
                }
            }

        }
        DropShadow {
            anchors.fill: _invalid_nickname_window
            horizontalOffset: 6
            verticalOffset: 6
            color: "black"
            source: _invalid_nickname_window
        }


    }

}
