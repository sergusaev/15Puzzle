import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15

CustomPage {

    Component.onCompleted: {
        timeRecordsModel.getTimeRanking(gameBoardModel.dimension)
        turnsRecordsModel.getTurnsRanking(gameBoardModel.dimension)
    }

    id: root


    CustomText {
        id: _15_puzzle_text
        text: (_stack_view_records.currentItem.tableType === "time") ? qsTr("Time ranking") : qsTr("Turns ranking")
        fontPointSize: Math.min(root.width, root.height) / 18
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: parent.height / 12
    }

    Rectangle {
        id: _records_table_wrapper
        anchors.top: parent.top
        anchors.topMargin: width / 2.5
        anchors.horizontalCenter: parent.horizontalCenter
        width: root.width * 0.82
        height: width * 1.5
        color: "transparent"

        StackView {
            id: _stack_view_records
            anchors.fill: parent
            initialItem: _time_records_page
            pushEnter: Transition {
                XAnimator {
                    duration: 0
                }
            }
            pushExit: Transition {
                XAnimator {
                    duration: 0
                }
            }
            popEnter: Transition {
                XAnimator {
                    duration: 0
                }
            }
            popExit: Transition {
                XAnimator {
                    duration: 0
                }
            }
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
        width: parent.width * 0.25
        height: width * 0.5
        anchors.left: _records_table_wrapper.left
        anchors.top: _records_table_wrapper.bottom
        anchors.topMargin: height / 2
        text: qsTr("Time")
        onClicked:  {
            if ( _stack_view_records.currentItem.tableType !== "time") {
                if(_stack_view_records.depth > 1) {
                    _stack_view_records.pop()
                } else {
                    _stack_view_records.push(_time_records_page)
                }
            }

        }
    }

    CustomButton {
        id: _back_button
        width: parent.width * 0.25
        height: width * 0.5
        anchors.right:  _records_table_wrapper.right
        anchors.top: _records_table_wrapper.bottom
        anchors.topMargin: height / 2
        text: qsTr("Back")
        onClicked:  {
            if(_stack_view.depth > 1) {
                _stack_view.pop()
            }
        }
    }
    CustomButton {
        id: _turns_button
        width: parent.width * 0.25
        height: width * 0.5
        anchors.horizontalCenter:  parent.horizontalCenter
        anchors.top: _records_table_wrapper.bottom
        anchors.topMargin: height / 2
        text: qsTr("Turns")
        onClicked:  {
            if ( _stack_view_records.currentItem.tableType !== "turns") {
                if(_stack_view_records.depth > 1) {
                    _stack_view_records.pop()
                } else {
                    _stack_view_records.push(_turns_records_page)
                }
            }
        }
    }



}

