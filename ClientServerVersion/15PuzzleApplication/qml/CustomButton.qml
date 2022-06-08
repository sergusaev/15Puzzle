import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15

Item {
    id: root    
    property alias text: _caption_text.text
    property alias fontPointSize: _caption_text.font.pointSize
    signal clicked()   

    Button {
        id: _caption
        anchors.fill: parent
        text: ""
        background: Rectangle {
            color: "transparent "
        }

        Text {
            id: _caption_text
            z: _caption_background_img.z + 1
            anchors.centerIn: _caption_background_img
            text: _caption.text
            color: _caption.pressed ? Qt.darker("burlywood", 0.7) :  "burlywood"
            style: Text.Outline
            styleColor: "dimgrey"
            font {
                pointSize: 20
                bold : true
            }
        }

        Image {
            id:_caption_background_img
            height:  _caption.height
            width:  _caption.width
            anchors.centerIn: parent
            anchors.horizontalCenterOffset: 0
            anchors.verticalCenterOffset: 0
            source: "../pics/button_1.png"
        }

        states: State {
            name: "pressed"
            when: _caption.pressed
            PropertyChanges {
                target: _caption_background_img
                anchors.horizontalCenterOffset: 2
                anchors.verticalCenterOffset: 2
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
