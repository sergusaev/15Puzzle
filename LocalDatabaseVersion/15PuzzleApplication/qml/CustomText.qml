import QtQuick 2.15
import QtGraphicalEffects 1.15

Item {
    id: root
    property alias text: _internal_text.text
    property alias color: _internal_text.color
    property alias style: _internal_text.style
    property alias styleColor: _internal_text.styleColor
    property alias fontPointSize: _internal_text.font.pointSize
    property alias fontBold: _internal_text.font.bold
    property alias verticalAlignment: _internal_text.verticalAlignment
    property alias horizontalAlignment: _internal_text.horizontalAlignment


    Text {
        id: _internal_text
        anchors.centerIn: parent
        text: qsTr("")
        color: "burlywood"
        style: Text.Outline
        styleColor:  Qt.darker("burlywood", 2)
        font {
            pointSize: 20
            bold : true
        }
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }
    DropShadow {
        anchors.fill: _internal_text
        horizontalOffset: 4
        verticalOffset: 4
        color: "black"
        source: _internal_text
    }

}
