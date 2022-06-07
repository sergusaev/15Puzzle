import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15


CustomPage {
    id: root
    Text {
        id: _15_puzzle_text
        text: qsTr("15-Puzzle")
        color: "burlywood"
        style: Text.Outline
        styleColor:  Qt.darker("burlywood", 2)
        font {
            pointSize: Math.min(root.width, root.height) / 14
            bold : true
        }
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: parent.height / 12
    }

    DropShadow {
        anchors.fill: _15_puzzle_text
        horizontalOffset: 6
        verticalOffset: 6
        color: "black"
        source: _15_puzzle_text
    }


    Rectangle {
        id:_authorization_form_wrapper
        width: parent.width * 0.76
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: _15_puzzle_text.bottom
        anchors.topMargin: height / 4
        height: width
        radius: 10

        Image {
            id: _wood_5_img
            property bool rounded: true
            property bool adapt: true
            anchors.fill: parent
            anchors.centerIn: parent
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
                        radius: _authorization_form_wrapper.radius
                    }
                }
            }

            Image {
                id: _3D_frame
                source: "../pics/frame_1.png"
                anchors.fill: parent
                anchors.centerIn: parent
                anchors.left: parent.left
                anchors.leftMargin: -9
                anchors.right: parent.right
                anchors.rightMargin: -9
                anchors.top: parent.top
                anchors.topMargin: -17
                anchors.bottom: parent.bottom
                anchors.bottomMargin: -2
            }

        }

        TextField {
            id: _nickname_text_field
            width: root.width / 1.5
            height:width / 5
            text: userSettings.readNickname()
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: height
            background: Rectangle {
                id:_inner_text_field_background
                color: parent.activeFocus ? "#50000000" : "#25000000"
                border.color: "gray"
                radius: _authorization_form_wrapper.radius
            }
        }
    }

    CustomButton {
        id: _ok_button
        width: root.width * 0.35
        height: buttonWidth * 0.45
        anchors.left: _authorization_form_wrapper.left
        anchors.leftMargin: buttonWidth / 2
        anchors.top: _authorization_form_wrapper.bottom
        anchors.topMargin: _authorization_form_wrapper.height / 4
        text: qsTr("OK")

        onClicked:  {
            _stack_view.push(_main_menu_stack_page)
            userSettings.writeSettings(_nickname_text_field.text)
            gameBoardModel.setNickname(_nickname_text_field.text)
        }

    }

    CustomButton {
        id: _quit_game_button
        width: root.width * 0.35
        height: buttonWidth * 0.45
        anchors.right: _authorization_form_wrapper.right
        anchors.rightMargin: buttonWidth / 2
        anchors.top: _authorization_form_wrapper.bottom
        anchors.topMargin: _authorization_form_wrapper.height / 4
        text: qsTr("Quit")
        onClicked: Qt.quit()


    }
}

