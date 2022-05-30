import QtQuick 2.15
//import Game 1.0



GridView {
    id: root
    model: gameBoardModel



    move: Transition {
              NumberAnimation { properties: "x,y"; duration: 120 }
    }

    cellWidth: width / root.model.dimension
    cellHeight: width / root.model.dimension

    delegate: Item {
        id: _tile_wrapper
        width: root.cellWidth
        height: root.cellHeight
        visible: root.model.hiddenElementValue !== display
        Tile {
            displayText: display
            anchors.fill: _tile_wrapper
            anchors.margins: _tile_wrapper.width / 30
            isCurrent:root.model.currentElement === index

            MouseArea {
                anchors.fill: parent
                onClicked: {
                   if(root.model.move(index)) {
                       root.model.setCounter(root.model.counter + 1)
                   }
                   root.model.currentElement = index                   
                   if(root.model.checkWin()) {
                       _winning_dialog.visible = true
                       _winning_dialog_wrapper.visible = true
                   }
               }
            }

        }
    }

}
