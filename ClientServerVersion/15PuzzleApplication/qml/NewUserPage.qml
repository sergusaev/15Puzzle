import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15
import AuthorizationManager 1.0

CustomPage {
    id:root
    property string ethalonPasswordOnNewUserPage: ""


    Connections {
        id: _authorization_page_connections
        target: signalsHandler

        function onEthalonPasswordChanged() {
            root.ethalonPasswordOnNewUserPage = AuthorizationManager.ethalonPassword
            console.log("root.ethalonPasswordOnNewUserPage changed")
            console.log(root.ethalonPasswordOnNewUserPage)
            if(root.ethalonPasswordOnNewUserPage !== "")  {
                _user_already_exists_text.visible = true
            } else {
                _user_already_exists_text.visible = false
            }
        }

    }


    CustomText {
        id: _enter_new_nickname_text
        text: qsTr("Enter nickname:")
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin:  parent.height / 6

    }

    TextField {
        id: _new_nickname_text_field
        width: root.width * 0.76
        height:width / 5
        text: ""
        validator: RegularExpressionValidator { regularExpression: /\w{0,12}/ }
        color: "lightyellow"
        font {
            pointSize: 25
            bold : true
        }
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: _enter_new_nickname_text.bottom
        anchors.topMargin:parent.height / 14
        background:  CustomBackground {
            radius: 10
        }

        onTextChanged:  {
            AuthorizationManager.requestUserPassword(_new_nickname_text_field.text)
            console.log("New user ethalon password: " + AuthorizationManager.ethalonPassword)
        }

    }

    CustomText {
        id: _user_already_exists_text
        text: qsTr("User already exists")
        anchors.top: _new_nickname_text_field.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin:  parent.height / 18
        fontPointSize: 12
        visible: false

    }

    CustomText {
        id: _enter_new_password_text
        text: qsTr("Enter password:")
        anchors.top: _new_nickname_text_field.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin:  parent.height / 6

    }

    TextField {
        id: _new_password_text_field
        width: root.width * 0.76
        height:width / 5
        text: ""
        validator: RegularExpressionValidator { regularExpression: /\w{0,12}/ }
        color: "lightyellow"
        font {
            pointSize: 25
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
        enabled: (_new_password_text_field.text !== "" && _new_nickname_text_field.text !== "") && !_user_already_exists_text.visible
        Rectangle {
            id: _accept_button_darkener
            z: _accept_button.z + 1
            anchors.fill: parent
            color: "#45000000"
            radius: 10
            visible: parent.enabled ? false : true
        }
        onClicked:  {
            AuthorizationManager.setNickname(_new_nickname_text_field.text)
            AuthorizationManager.setPassword(_new_password_text_field.text)
            _stack_view.pop()
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
            _stack_view.pop()
        }
    }

}




