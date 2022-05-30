import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15

Item {
    id: root
    property alias buttonWidth: _caption.width
    property alias buttonHeight: _caption.height
    property alias text: _caption.text

    signal clicked()

    Button {
        id: _caption
        height: 20
        width: 80
        anchors.centerIn: parent

        text: ""
        contentItem: Text {
            text: _caption.text
            color: _caption.pressed ? Qt.darker("burlywood", 0.7) :  "burlywood"
            style: Text.Outline
            styleColor: "dimgrey"
            font {
                pointSize: _caption.height / 4
                bold : true
            }
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        background: Image {
            anchors.fill:parent
            source: "../pics/button_1.png"
        }

        states: State {
            name: "pressed"
            when: _caption.pressed === true

            PropertyChanges {
                target: _caption
                anchors.horizontalCenterOffset:  2
                anchors.verticalCenterOffset:  2
            }
            PropertyChanges {
                target: _caption_shadow
                horizontalOffset: 4
                verticalOffset: 4

            }
        }

        transitions: Transition {
            from: ""
            to: "pressed"
            reversible: true
        }

        onClicked: root.clicked()
    }

    DropShadow {
        id: _caption_shadow
        anchors.fill: _caption
        horizontalOffset: 6
        verticalOffset: 6
        color: "black"
        source: _caption
    }

}
