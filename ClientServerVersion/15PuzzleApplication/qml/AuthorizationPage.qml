import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.15
import QtQuick.Dialogs 1.3
import AuthorizationManager 1.0
import SignalsHandler 1.0

CustomPage {
    id: root
    property string authorizationState: ""
    property bool newUser: false

    Connections {
        id: _authorization_page_connections
        target: SignalsHandler

        function onConnectionStateChanged(connectionState) {
//            console.log("onConnectionStateChanged signal caught, connectionState: " + connectionState)
            _authorization_page_connecting_to_server_window.visible = !connectionState
        }

        function onNicknameExists(exists) {
//            console.log("onNicknameExists signal caught, exists: " + exists)
//            console.log("Current _ok_button_state: " + _ok_button.state)
//            console.log("root.newUser: " + root.newUser)
            if (root.newUser) {
                return
            }
            if(exists) {
                _ok_button.clicked()
            } else {
                _invalid_nickname_window.visible = true
            }
        }


        function onPasswordValidationCompleted(validationResult) {
            console.log("onPasswordValidationCompleted signal caught, validationResult: " + validationResult)
            console.log("Encoded password: " + AuthorizationManager.encodedPassword)
            console.log("Current _ok_button_state: " + _ok_button.state)
            if(!validationResult) {
                _invalid_password_window.visible = true
            } else {
                _ok_button.clicked()
            }

        }

        function onNicknameChanged(nickname) {
            console.log("onNicknameChanged signal caught, nickname: " + nickname)
            _nickname_text_field.text = nickname
        }

        function onPasswordChanged(password) {
            console.log("onPasswordChanged signal caught, password: " + password)
            _password_text_field.text = password
        }

        function onDimensionChanged(dimension) {
            console.log("onDimensionChanged signal caught, dimension: " + dimension)
            _puzzle_size_selection_combobox.currentIndex = dimension - 2
        }



        function onAuthorizationPageStateChanged(newAuthorizationPageState) {
//            console.log("onAuthorizationPageStateChanged signal caught, newAuthorizationPageState: " + newAuthorizationPageState)
            switch(newAuthorizationPageState){
            case 1:
                root.authorizationState = "NicknameInput"
                break;
            case 2:
                root.authorizationState = "PasswordInput"
                break;
            case 3:
                root.authorizationState = "DimensionSelection"
                break;
            default:
                break;
            }
//            console.log("New autorization page state: " + root.authorizationState)
        }

        function onNewUserChanged(newUser) {
//            console.log("onNewUserChanged signal caught, newUser: " + newUser)
            root.newUser = newUser
        }

        function onUserSuccessfullyAdded() {
            _new_user_addition_succes_window.visible = true
        }

        function onUserAdditionInternalServerError() {
            _internal_server_error_window.visible = true
        }

        function onPasswordInternalServerError() {
             _internal_server_error_window.visible = true
        }
    }



    Component.onCompleted: {

//        console.log("On AuthorizationPage creation")

        AuthorizationManager.setNickname (userSettings.readNickname())
        AuthorizationManager.setPassword (userSettings.readPassword())
        if((userSettings.readDimension() > 2)) {
            AuthorizationManager.setDimension (userSettings.readDimension())
        }
//        console.log("QSettings authorizationPageState:" + userSettings.readAuthorizationPageState())
        if((1 < userSettings.readAuthorizationPageState() && userSettings.readAuthorizationPageState() < 4)) {
            AuthorizationManager.setAuthorizationPageState (userSettings.readAuthorizationPageState())
        } else {
            AuthorizationManager.setAuthorizationPageState(1)
        }
        AuthorizationManager.validatePassword(AuthorizationManager.nickname, AuthorizationManager.password)
        _puzzle_size_selection_combobox.currentIndex = AuthorizationManager.dimension - 2

//        console.log("nickname: " + AuthorizationManager.nickname)
//        console.log("password: " + AuthorizationManager.password)
//        console.log("dimension: " + AuthorizationManager.dimension)
//        console.log("authorizationPageState: " + AuthorizationManager.authorizationPageState)
//        console.log("AuthorizationManager ethalon password: " + AuthorizationManager.ethalonPassword)
//        userSettings.clearSettings()
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
        text: ""
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
        text:  ""
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
            },
            State {
                name: "ProcessingNicknameExistanceRequest"

            },
            State {
                name: "ProcessingAuthorizationRequest"

            }
        ]

        onStateChanged:  {
//            console.log("_ok_button.stateChanged signal caught, state: " + _ok_button.state)
            if(state === "ProcessingPasswordRequest" && root.newUser) {
                _ok_button.clicked()
            }
        }

        onClicked:  {
            console.log("Ok button pressed, state: " + state)
            if (state === "NickInput") {
                AuthorizationManager.setNickname(_nickname_text_field.text)
                AuthorizationManager.setAuthorizationPageState(2)
            }
            else if (state === "PassInput"){
                AuthorizationManager.setPassword(_password_text_field.text)
                AuthorizationManager.setAuthorizationPageState(3)
            }
            else if (state === "DimSelect") {
                AuthorizationManager.setDimension(_puzzle_size_selection_combobox.currentIndex + 2)
                if(root.newUser) {
                    state = "ProcessingPasswordRequest"
                } else {
                    AuthorizationManager.checkNicknameExistance(_nickname_text_field.text)
                    state = "ProcessingNicknameExistanceRequest"
                }

            }
            else if(state === "ProcessingNicknameExistanceRequest") {
                AuthorizationManager.validatePassword(_nickname_text_field.text, _password_text_field.text)
                state = "ProcessingPasswordRequest"
            }

            else if (state === "ProcessingPasswordRequest"){

//                AuthorizationManager.setNickname(_nickname_text_field.text)
//                AuthorizationManager.setPassword(_password_text_field.text)
//                AuthorizationManager.setDimension(_puzzle_size_selection_combobox.currentIndex + 2)
                if(root.newUser) {
                    AuthorizationManager.addNewUser(AuthorizationManager.nickname, AuthorizationManager.password)
                }
                userSettings.writeSettings(AuthorizationManager.nickname,
                                           AuthorizationManager.password,
                                           AuthorizationManager.dimension,
                                           AuthorizationManager.authorizationPageState)
                if(!root.newUser) {
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
        onClicked:{
//            console.log("_quit_or_back_button pressed, state: " + state)
            if(state === "Quit") {
                Qt.quit()
            } else {
                AuthorizationManager.setNewUser(false)
                if(root.authorizationState === "PasswordInput") {
                    //set authorizationState "NicknameInput"
                    AuthorizationManager.setAuthorizationPageState(1)
                } else {
                    //set authorizationState "PasswordInput" and return dimension to minimal (2)
                    AuthorizationManager.setAuthorizationPageState(2)
                    AuthorizationManager.setDimension (2)
                }
            }
        }
    }

    CustomButton {
        id: _new_player_button
        width: root.width * 0.76
        height: _ok_button.height * 1.1
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: _ok_button.bottom
        anchors.topMargin: _puzzle_size_selection_combobox.height / 3
        text:  qsTr("New player")
        enabled: root.authorizationState === "NicknameInput"
        onClicked:  {
//            console.log("_new_player_button pressed")
            _stack_view.push(_new_user_stack_page)
            AuthorizationManager.setNewUser(true)
        }
        Rectangle {
            id: _new_player_button_darkener
            z: _new_player_button.z + 1
            anchors.fill: parent
            color: "#45000000"
            radius: 10
            visible: parent.enabled ? false : true
        }
    }



    InvalidNicknameWindow {
        id: _invalid_nickname_window
        z: parent.z + 1
        anchors.fill: parent
        visible: false
    }


    InvalidPasswordWindow {
        id: _invalid_password_window
        z: parent.z + 2
        anchors.fill: parent
        visible: false

    }

    ConnectingToServerWindow {
        id: _authorization_page_connecting_to_server_window
        z: parent.z + 2
        anchors.fill: parent
        visible: false

    }

    UserAdditionSuccessWindow {
        id: _new_user_addition_succes_window
        anchors.fill: parent
        z: parent.z + 2
        visible: false
        onOkButtonClicked: {
            _new_user_addition_succes_window.visible = false
            _stack_view.push(_main_menu_stack_page)
        }
    }

    InternalServerErrorWindow {
        id: _internal_server_error_window
        anchors.fill: parent
        visible: false
        onTryAgainButtonClicked: {
            _internal_server_error_window.visible = false
            //set authorizationState "NicknameInput"
            AuthorizationManager.setAuthorizationPageState(1)
        }
    }

}

