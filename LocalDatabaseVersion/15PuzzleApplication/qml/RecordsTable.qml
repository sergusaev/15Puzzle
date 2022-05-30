import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15

Item {
    id:root
    property string tableType: ""

    ListView {
        id: _records_list_view
        anchors.fill: parent
        spacing: 1
        model: tableType === "time" ? timeRecordsModel : turnsRecordsModel
        delegate: Rectangle {
            id: _delegate_background
            width: root.width
            height: root.height / 10
            color: "transparent"

            Text {
                id: _rank_text
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                height: parent.height
                width: height
                style: Text.Outline
                styleColor: Qt.darker("burlywood", 2)
                font {
                    pointSize: parent.height / 3.5
                    bold : true
                }
                text: _records_list_view.model.rankToString(index + 1)
                color: "darksalmon"
            }

            DropShadow {
                anchors.fill: _rank_text
                horizontalOffset: 6
                verticalOffset: 6
                color: "black"
                source: _rank_text
            }

            Text {
                id: _nickname_text
                anchors.left: _rank_text.right
                anchors.right:_time_turns_text.left
                anchors.verticalCenter: parent.verticalCenter
                height: parent.height
                style: Text.Outline
                styleColor: Qt.darker("burlywood", 2)
                font {
                    pointSize: parent.height / 3.5
                    bold : true
                }
                text: nickname
                color: "darksalmon"
            }

            DropShadow {
                anchors.fill: _nickname_text
                horizontalOffset: 6
                verticalOffset: 6
                color: "black"
                source: _nickname_text
            }

            Text {
                id: _time_turns_text
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                height: parent.height
                width: height * 1.2
                style: Text.Outline
                styleColor: Qt.darker("burlywood", 2)
                font {
                    pointSize: parent.height / 3.5
                    bold : true
                }
                text: tableType === "time" ? time : turns
                color: "darksalmon"
            }

            DropShadow {
                anchors.fill: _time_turns_text
                horizontalOffset: 6
                verticalOffset: 6
                color: "black"
                source: _time_turns_text
            }

        }

    }
}
