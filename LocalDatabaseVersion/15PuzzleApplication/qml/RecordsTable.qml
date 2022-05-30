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

            CustomText {
                id: _rank_text
                height: parent.height
                width: height * 0.8
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter               
                fontPointSize: parent.height / 3.5
                text: _records_list_view.model.rankToString(index + 1)
                color: (index === 0) ? "gold" : (index === 1) ? "silver" : (index === 2) ? "#967444" : "darksalmon"
            }

            CustomText {
                id: _nickname_text
                anchors.left: _rank_text.right
                anchors.right:_time_turns_text.left
                anchors.verticalCenter: parent.verticalCenter
                fontPointSize: parent.height / 3.5
                text: nickname
                color: (index === 0) ? "gold" : (index === 1) ? "silver" : (index === 2) ? "#967444" : "darksalmon"
            }

            CustomText {
                id: _time_turns_text
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                height: parent.height
                width: height * 1.2               
                fontPointSize: parent.height / 3.5
                text: tableType === "time" ? time : turns
                color: (index === 0) ? "gold" : (index === 1) ? "silver" : (index === 2) ? "#967444" : "darksalmon"
            }

        }

    }
}
