import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.15
import QtQuick.Dialogs 1.3
import AuthorizationManager 1.0



CustomPage {
    id: root
    property string authorizationState: "NicknameInput"
    property bool newUser: true
    property string newUserPassword: ""
    property string ethalonPassword: ""
    property int currDimension: 2



//    onEthalonPasswordChanged: {
//        console.log("On root.ethalonPassword changed")
//        console.log ("ethalon password changed!")
//        root.ethalonPassword = AuthorizationManager.ethalonPassword
//        console.log ("New ethalon password: " + root.ethalonPassword)
//    }




    Component.onCompleted: {
        AuthorizationManager.setNickname (userSettings.readNickname())
        AuthorizationManager.setPassword (userSettings.readPassword())
        root.ethalonPassword = AuthorizationManager.password
        if((userSettings.readDimension() > 2)) {
            AuthorizationManager.setDimension (userSettings.readDimension())
        }
        root.newUser = AuthorizationManager.nickname === ""
        _puzzle_size_selection_combobox.currentIndex = AuthorizationManager.dimension - 2

        console.log("On AuthorizationPage creation")
        console.log("QSettings password: " + AuthorizationManager.password)
        console.log("Root ethalon password: " + root.ethalonPassword)

    }

    CustomText {
        id: _15_puzzle_text
        text: qsTr("15-Puzzle")
        fontPointSize: 50
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: parent.height / 9
    }

    CustomText {
        id: _enter_nickname_text
        text: qsTr("Enter your nickname:")
        anchors.top: _15_puzzle_text.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: parent.height / 12
    }

    TextField {
        id: _nickname_text_field
        width: root.width * 0.76
        height:width / 5
        text: AuthorizationManager.nickname
        validator: RegularExpressionValidator { regularExpression: /\w{0,12}/ }
        color: "lightyellow"
        font {
            pointSize: 25
            bold : true
        }
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: _enter_nickname_text.bottom
        anchors.topMargin: _nickname_text_field.height / 2
        background:  CustomBackground {
            radius: 10
        }
        enabled: root.authorizationState === "NicknameInput"
        onFocusChanged: {
            AuthorizationManager.requestUserPassword(_nickname_text_field.text)
        }
    }
    Rectangle {
        id: _nickname_text_field_darkener
        z: _nickname_text_field.z + 1
        anchors.fill: _nickname_text_field
        color: "#45000000"
        radius: 10
        visible: !_nickname_text_field.enabled
    }


    CustomText {
        id: _enter_password_text
        text: qsTr("Enter password:")
        anchors.top: _nickname_text_field.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: _nickname_text_field.height / 2
        visible: root.authorizationState === "PasswordInput" || root.authorizationState === "DimensionSelection" ? true : false
    }

    TextField {
        id: _password_text_field
        width: root.width * 0.76
        height:width / 5
        text: root.newUserPassword === "" ? AuthorizationManager.password : root.newUserPassword
        validator: RegularExpressionValidator { regularExpression: /\w{0,12}/ }
        color: "lightyellow"
        font {
            pointSize: 25
            bold : true
        }
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: _enter_password_text.bottom
        anchors.topMargin: _nickname_text_field.height / 2
        background:  CustomBackground {
            radius: 10
        }
        visible:  root.authorizationState === "PasswordInput" || root.authorizationState === "DimensionSelection" ? true : false
        enabled: root.authorizationState === "PasswordInput"
    }

    Rectangle {
        id: _password_text_field_darkener
        z: _password_text_field.z + 1
        anchors.fill: _password_text_field
        color: "#45000000"
        radius: 10
        visible: _password_text_field.visible ? !_password_text_field.enabled : _password_text_field.visible
    }




    CustomText {
        id: _select_puzzle_size_text
        text: qsTr("Select 15-puzzle size:")
        anchors.top: _password_text_field.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: _password_text_field.height / 2
        visible: root.authorizationState === "DimensionSelection" ? true : false
    }

    ComboBox {
        id: _puzzle_size_selection_combobox
        width: root.width * 0.76
        height:width / 5
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: _select_puzzle_size_text.bottom
        anchors.topMargin: _nickname_text_field.height / 2
        background: CustomBackground {
            radius: 10
        }
        model: ["2x2", "3x3", "4x4", "5x5"]
        delegate: ItemDelegate {
            id:_combobox_delegate
            width: _puzzle_size_selection_combobox.width
            height: _puzzle_size_selection_combobox.height
            contentItem: CustomText {
                text: modelData
                fontPointSize: 15
                color: _combobox_delegate.pressed ? "lightyellow" : "burlywood"
            }
            background: CustomBackground {
                radius: 10
            }
            onClicked:  {
                root.currDimension = (index + 2)

            }
        }

        Rectangle {
            id: _combobox_darkener
            z: _puzzle_size_selection_combobox.z + 1
            anchors.fill: parent
            color: "#45000000"
            radius: 10
            visible: _puzzle_size_selection_combobox.popup.visible ? true : false
        }

        contentItem: CustomText {
            id: _combobox_text
            anchors.fill:parent
            text: _puzzle_size_selection_combobox.displayText
            fontPointSize: 25
            color: _puzzle_size_selection_combobox.pressed ? "lightyellow" : "burlywood"
        }

        popup: Popup {
            y: _puzzle_size_selection_combobox.height - 1
            width: _puzzle_size_selection_combobox.width
            height: _puzzle_size_selection_combobox.height * 4
            padding: 0
            contentItem: ListView {
                model: _puzzle_size_selection_combobox.popup.visible ?_puzzle_size_selection_combobox.delegateModel : null
            }
            background: Rectangle {
                color: "transparent"
                radius: 10
            }
        }
        visible: root.authorizationState === "DimensionSelection" ? true : false
    }


    CustomButton {
        id: _ok_button
        width: root.width * 0.35
        height: width * 0.4
        anchors.left: _nickname_text_field.left
        anchors.top: _puzzle_size_selection_combobox.bottom
        anchors.topMargin: _puzzle_size_selection_combobox.height
        enabled: (state === "NickInput") ? _nickname_text_field.text !== "" :
                                           (state === "PassInput") ? _password_text_field.text !== "" : true
        text: qsTr("OK")

        states: [
            State {
                name: "NickInput"
                when: root.authorizationState === "NicknameInput"
            },
            State {
                name: "PassInput"
                when: root.authorizationState === "PasswordInput"
            },
            State {
                name: "DimSelect"
                when: root.authorizationState === "DimensionSelection"
            }
        ]
        onClicked:  {
            if (state === "NickInput") {
                if(!AuthorizationManager.connectionState) {
                    _no_server_connection_popup.open()
                } else {

                    console.log("Clicking OK-button (NickInput state)")
                    console.log("root.ethalonPassword: " + root.ethalonPassword)

                    if(root.ethalonPassword === "") {
                        AuthorizationManager.setNickname(_nickname_text_field.text)
                        AuthorizationManager.setPassword("")
                        root.newUser = true
                        _new_user_popup_window.windowVisible = true
                    } else {
                        root.authorizationState = "PasswordInput"
                    }
                }
            } else if (state === "PassInput"){

                console.log("Clicking OK-button (PassInput state)")
                console.log("root.ethalonPassword: " + root.ethalonPassword)
                console.log("_password_text_field.text: " + _password_text_field.text)

                if(root.ethalonPassword === _password_text_field.text) {
                    root.authorizationState = "DimensionSelection"
                } else {
                    _wrong_password_popup.open()
                }
            }

            else if (state === "DimSelect") {
                if(!AuthorizationManager.connectionState) {
                    _no_server_connection_popup.open()
                } else {
                    AuthorizationManager.setNickname(_nickname_text_field.text)
                    AuthorizationManager.setPassword(_password_text_field.text)
                    AuthorizationManager.setDimension(root.currDimension)
                    AuthorizationManager.addNewUser(AuthorizationManager.nickname, AuthorizationManager.password)
                    userSettings.writeSettings(AuthorizationManager.nickname, AuthorizationManager.password, AuthorizationManager.dimension)
                    root.authorizationState === "NicknameInput"
                    _stack_view.push(_main_menu_stack_page)
                }
            }

        }
        Rectangle {
            id: _ok_button_darkener
            z: _ok_button.z + 1
            anchors.fill: parent
            color: "#45000000"
            radius: 10
            visible: parent.enabled ? false : true
        }

    }

    CustomButton {
        id: _quit_or_back_button
        width: root.width * 0.35
        height: width * 0.4
        anchors.right:_nickname_text_field.right
        anchors.top: _puzzle_size_selection_combobox.bottom
        anchors.topMargin: _puzzle_size_selection_combobox.height
        text: state === "Quit" ? qsTr("Quit") : qsTr("Back")

        states:[
            State {
                name: "Quit"
                when: root.authorizationState === "NicknameInput"
            },
            State {
                name: "Back"
                when: root.authorizationState !== "NicknameInput"
            }

        ]
        onClicked:
            if(state === "Quit") {
                Qt.quit()
            } else {
                if(root.authorizationState === "PasswordInput") {
                    root.authorizationState = "NicknameInput"
                } else {
                    root.authorizationState = "PasswordInput"
                    root.currDimension = 2
                }
            }
    }

    NewUserWindow {
        id: _new_user_popup_window
        z: root.z + 1
        anchors.fill: parent
        username: _nickname_text_field.text
        windowVisible: false

    }

    Popup
    {
        id: _wrong_password_popup
        width: parent.width * 0.9
        height: width
        anchors.centerIn: parent
        padding: 0

        background: Rectangle {
            id:_inner_rect
            anchors.fill:parent
            radius: 10

            Image {
                id: _inner_rect_background
                property bool rounded: true
                property bool adapt: true
                anchors.fill: parent

                source: "../pics/wood_5.png"
                layer.enabled: rounded
                layer.effect: OpacityMask {
                    maskSource: Item {
                        width: _inner_rect_background.width
                        height: _inner_rect_background.height
                        Rectangle {
                            anchors.centerIn: parent
                            width: _inner_rect_background.adapt ? _inner_rect_background.width : Math.min(_inner_rect_background.width, _inner_rect_background.height)
                            height: _inner_rect_background.adapt ? _inner_rect_background.height : width
                            radius: _inner_rect.radius
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
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: _wrong_password_text.bottom
                anchors.topMargin: parent.height / 4
                text: qsTr("Try again")
                onClicked: _wrong_password_popup.close()
            }


        }

    }

    Popup
    {
        id: _internal_server_error_popup
        width: parent.width * 0.9
        height: width
        anchors.centerIn: parent
        padding: 0


        background: Rectangle {
            id:_inner_internal_server_error_popup_rect
            anchors.fill:parent
            radius: 10

            Image {
                id:_inner_internal_server_error_popup_rect_background
                property bool rounded: true
                property bool adapt: true
                anchors.fill: parent

                source: "../pics/wood_5.png"
                layer.enabled: rounded
                layer.effect: OpacityMask {
                    maskSource: Item {
                        width: _inner_internal_server_error_popup_rect_background.width
                        height: _inner_internal_server_error_popup_rect_background.height
                        Rectangle {
                            anchors.centerIn: parent
                            width: _inner_internal_server_error_popup_rect_background.adapt
                                   ? _inner_internal_server_error_popup_rect_background.width
                                   : Math.min(_inner_internal_server_error_popup_rect_background.width, _inner_internal_server_error_popup_rect_background.height)
                            height: _inner_internal_server_error_popup_rect_background.adapt ? _inner_internal_server_error_popup_rect_background.height : width
                            radius: _inner_internal_server_error_popup_rect.radius
                        }
                    }
                }

            }

            CustomText {
                id: _internal_server_error_text
                text: qsTr("Internal server error!")
                fontPointSize: 30
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: parent.height / 3
            }

            CustomButton {
                id: _internal_server_error_try_again_button
                width: parent.width * 0.5
                height: width * 0.4
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: _internal_server_error_text.bottom
                anchors.topMargin: parent.height / 4
                text: qsTr("Try again")
                onClicked: _internal_server_error_popup.close()
            }


        }

    }
    Popup
    {
        id: _no_server_connection_popup
        width: parent.width * 0.9
        height: width
        anchors.centerIn: parent
        padding: 0


        background: Rectangle {
            id:_no_server_connection_popup_rect
            anchors.fill:parent
            radius: 10

            Image {
                id:_no_server_connection_popup_rect_background
                property bool rounded: true
                property bool adapt: true
                anchors.fill: parent

                source: "../pics/wood_5.png"
                layer.enabled: rounded
                layer.effect: OpacityMask {
                    maskSource: Item {
                        width: _no_server_connection_popup_rect_background.width
                        height: _no_server_connection_popup_rect_background.height
                        Rectangle {
                            anchors.centerIn: parent
                            width: _no_server_connection_popup_rect_background.adapt
                                   ? _no_server_connection_popup_rect_background.width
                                   : Math.min(_no_server_connection_popup_rect_background.width, _no_server_connection_popup_rect_background.height)
                            height: _no_server_connection_popup_rect_background.adapt ? _no_server_connection_popup_rect_background.height : width
                            radius: _no_server_connection_popup_rect.radius
                        }
                    }
                }

            }

            CustomText {
                id: _no_server_connection_text
                text: qsTr("No server connection!")
                fontPointSize: 30
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: parent.height / 3
            }
            CustomText {
                id: _cache_adding_text
                text: qsTr("Record added into cache.")
                anchors.top: _no_server_connection_text.top
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: parent.height / 6
                //                visible: ErrorHandler.cacheAddingTextVisible
            }

            CustomButton {
                id: _no_server_connection_try_again_button
                width: parent.width * 0.5
                height: width * 0.4
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: _cache_adding_text.bottom
                anchors.topMargin: parent.height / 4
                text: qsTr("Try again")
                onClicked:  {
                    ErrorHandler.setCacheAddingTextVisible(false)
                    _no_server_connection_popup.close()
                }


            }

        }
    }

}
