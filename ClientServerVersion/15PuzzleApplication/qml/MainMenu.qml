import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15
import AuthorizationManager 1.0

CustomPage {
    id: root

    CustomText {
        id: _greetings_text
        text: qsTr("Hi, " + AuthorizationManager.nickname + "!")
        fontPointSize: 40
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: parent.height / 6
    }


    CustomButton {
        id: _new_game_button
        width: root.width * 0.7
        height: width * 0.3
        anchors.horizontalCenter:  parent.horizontalCenter
        anchors.top: _greetings_text.bottom
        anchors.topMargin: parent.height / 10
        fontPointSize: 30
        text: qsTr("NEW GAME")
        onClicked:  {
             gameBoardModel.restart()
            _stack_view.push(_gameboard_stack_page)
        }
    }

    CustomButton {
        id: _records_button
        width: parent.width * 0.7
        height: width * 0.3
        anchors.horizontalCenter:  parent.horizontalCenter
        anchors.top: _new_game_button.bottom
        anchors.topMargin: _new_game_button.height * 0.5
        fontPointSize: 30
        text: qsTr("RECORDS")
        onClicked:  {
            _stack_view.push(_records_stack_page)
        }
    }

    CustomButton {
        id: _back_button
        width: parent.width * 0.7
        height: width * 0.3
        anchors.horizontalCenter:  parent.horizontalCenter
        anchors.top: _records_button.bottom
        anchors.topMargin: _records_button.height * 0.5
        fontPointSize: 30
        text: qsTr("BACK")
        onClicked: {
            if(_stack_view.depth > 1) {
                _stack_view.pop()
            } else {
                return
            }
        }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
}
