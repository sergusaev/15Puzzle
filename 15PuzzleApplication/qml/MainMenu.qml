import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15

//import Qt5Compat.GraphicalEffects

CustomPage {
    id: root

    Text {
        id: _15_puzzle_text
        text: qsTr("15-Puzzle")
        color: "burlywood"
        style: Text.Outline
        styleColor: "darksalmon"
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


    CustomButton {
        id: _new_game_button
        buttonWidth: root.width * 0.7
        buttonHeight: buttonWidth * 0.3
        anchors.horizontalCenter:  parent.horizontalCenter
        anchors.top: _15_puzzle_text.bottom
        anchors.topMargin: parent.height / 8
        text: qsTr("NEW GAME")
        onClicked:  {
             gameBoardModel.restart()
            _stack_view.push(_gameboard_stack_page)
        }
    }

    CustomButton {
        id: _records_button
        buttonWidth: parent.width * 0.7
        buttonHeight: buttonWidth * 0.3
        anchors.horizontalCenter:  parent.horizontalCenter
        anchors.top: _new_game_button.bottom
        anchors.topMargin: parent.height / 8
        text: qsTr("RECORDS")
        onClicked:  {
            _stack_view.push(_records_stack_page)
        }
    }

    CustomButton {
        id: _quit_button
        buttonWidth: parent.width * 0.7
        buttonHeight: buttonWidth * 0.3
        anchors.horizontalCenter:  parent.horizontalCenter
        anchors.top: _records_button.bottom
        anchors.topMargin: parent.height / 8
        text: qsTr("QUIT")
        onClicked: Qt.quit()
    }
}










/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
