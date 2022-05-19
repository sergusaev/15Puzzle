import QtQuick 2.15
import QtQuick.Controls 2.15

CustomPage {


    id: root

    Component.onCompleted: {
        console.log(13)
    }

    CustomButton {
        id: _time_button
        buttonWidth: parent.width * 0.25
        buttonHeight: buttonWidth * 0.6
        anchors.left:  parent.left
        anchors.leftMargin: buttonWidth / 1.15
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 2 * buttonWidth
        text: qsTr("Time")
        onClicked:  {

        }
    }


        CustomButton {
            id: _back_button
            buttonWidth: parent.width * 0.25
            buttonHeight: buttonWidth * 0.6
            anchors.right:  parent.right
            anchors.rightMargin: buttonWidth / 1.15
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 2 * buttonWidth
            text: qsTr("Back")
            onClicked:  {
                if(_stack_view.depth > 1) {
                    _stack_view.pop()
                }
            }
        }
        CustomButton {
            id: _turns_button
            buttonWidth: parent.width * 0.25
            buttonHeight: buttonWidth * 0.6
            anchors.horizontalCenter:  parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 2 * buttonWidth
            text: qsTr("Turns")
            onClicked:  {

            }
        }





}

