import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15

Item {
    id:root
    property string username: ""
    property alias windowVisible: _new_user_window_wrapper.visible
    signal passwordSaved()

    onPasswordSaved: {
        _stack_view.currentItem.authorizationState = "DimensionSelection"
        _stack_view.currentItem.newUserPassword = _new_password_text_field.text
        _new_password_text_field.text = ""
    }

    Rectangle {
        id: _new_user_window_wrapper
        anchors.fill: parent
        visible: true
        color: "#80ffffff"

        Rectangle {
            id:_new_user_window
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 10
            height: width * 1.15
            anchors.verticalCenter: parent.verticalCenter
            radius: 10

            Image {
                id: _new_user_window_background
                property bool rounded: true
                property bool adapt: true
                anchors.fill: parent

                source: "../pics/wood_5.png"
                layer.enabled: rounded
                layer.effect: OpacityMask {
                    maskSource: Item {
                        width: _new_user_window_background.width
                        height: _new_user_window_background.height
                        Rectangle {
                            anchors.centerIn: parent
                            width: _new_user_window_background.adapt ? _new_user_window_background.width : Math.min(_new_user_window_background.width, _new_user_window_background.height)
                            height: _new_user_window_background.adapt ? _new_user_window_background.height : width
                            radius: _new_user_window.radius
                        }
                    }
                }



            }
            CustomText {
                id: _new_user_greetings_text
                text: qsTr("New player:")
                fontPointSize: Math.min(parent.width, parent.height) / 20
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: parent.height / 10
            }

            CustomText {
                id: _new_username_text
                text: qsTr(root.username)
                color: "lightyellow"
                style: Text.Outline
                styleColor: "darksalmon"
                fontPointSize: Math.min(parent.width, parent.height) / 20
                anchors.top: _new_user_greetings_text.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: parent.height / 12
            }

            CustomText {
                id: _enter_new_password_text
                text: qsTr("Enter password:")
                fontPointSize: Math.min(root.width, root.height) / 30
                anchors.top: _new_username_text.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin:  parent.height / 5

            }

            TextField {
                id: _new_password_text_field
                width: root.width * 0.76
                height:width / 5
                text: ""
                validator: RegularExpressionValidator { regularExpression: /\w{0,12}/ }
                color: "lightyellow"
                font {
                    pointSize: Math.min(root.width, root.height) / 20
                    bold : true
                }
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: _enter_new_password_text.bottom
                anchors.topMargin:parent.height / 14
                background:  CustomBackground {
                    radius: 10
                }

            }

            CustomButton {
                id: _accept_button
                width: parent.width * 0.36
                height: width * 0.4
                anchors.left: _new_password_text_field.left
                anchors.top: _new_password_text_field.bottom
                anchors.topMargin: parent.height / 14
                text: qsTr("Accept")
                enabled: _new_password_text_field.text !== ""
                Rectangle {
                    id: _accept_button_darkener
                    z: _accept_button.z + 1
                    anchors.fill: parent
                    color: "#45000000"
                    radius: 10
                    visible: parent.enabled ? false : true
                }
                onClicked:  {
                    root.windowVisible = false
                    _stack_view.currentItem.ethalonPassword = _new_password_text_field.text
                    root.passwordSaved()
                }
            }

            CustomButton {
                id: _to_authorization_window_button
                width: parent.width * 0.36
                height: width * 0.4
                anchors.right: _new_password_text_field.right
                anchors.top: _new_password_text_field.bottom
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
            anchors.fill: _new_user_window
            horizontalOffset: 6
            verticalOffset: 6
            color: "black"
            source: _new_user_window
        }


    }

}
