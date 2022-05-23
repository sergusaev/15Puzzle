import QtQuick 2.15
import QtQuick.Controls 2.15

CustomPage {

    Component.onCompleted: {
        timeRecordsModel.getTimeRanking()
        turnsRecordsModel.getTurnsRanking()
    }

    id: root
    Rectangle {
        id: _records_table_wrapper
        anchors.top: parent.top
        anchors.topMargin: width / 2.5
        anchors.horizontalCenter: parent.horizontalCenter
        width: root.width * 0.82
        height: width * 1.5
        color: "white"

        StackView {
            id: _stack_view_records
            anchors.fill: parent
            initialItem: _time_records_page

        }

        Component {
            id: _time_records_page
            RecordsTable {
                id:_time_records_table
                tableType: "time"
            }
        }

        Component {
            id:  _turns_records_page
            RecordsTable {
                id:_turns_records_table
                tableType: "turns"
            }
        }

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

