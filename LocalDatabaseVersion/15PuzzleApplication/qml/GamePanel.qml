import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15


CustomPage {
    id: root


    Text {
        id: _counter_title
        text: qsTr("Turns")
        color: Qt.darker("burlywood", 0.8)
        style: Text.Outline
        styleColor: "darksalmon"
        font {
            pointSize: 16
            bold : true
        }
        anchors.top: parent.top
        anchors.horizontalCenter: _counter.horizontalCenter
        anchors.topMargin: parent.height / 12
    }

    DropShadow {
        anchors.fill: _counter_title
        horizontalOffset: 6
        verticalOffset: 6
        color: "black"
        source: _counter_title
    }

    Text {
        id: _timer_title
        text: qsTr("Time")
        color: Qt.darker("burlywood", 0.8)
        style: Text.Outline
        styleColor: "darksalmon"
        font {
            pointSize: 16
            bold : true
        }
        anchors.top: parent.top
        anchors.horizontalCenter: _timer.horizontalCenter
        anchors.topMargin: parent.height / 12
    }

    DropShadow {
        anchors.fill: _timer_title
        horizontalOffset: 6
        verticalOffset: 6
        color: "black"
        source: _timer_title
    }

    CustomDisplay {
        id: _timer
        anchors.left: _gameboard_wrapper.left
        anchors.leftMargin: displayWidth / 2
        anchors.top: _timer_title.bottom
        anchors.topMargin: displayHeight / 1.5
        displayHeight: displayWidth * 0.45
        displayWidth: root.width * 0.35
        displayText: _gameboard.model.getTime
    }

    CustomDisplay {
        id: _counter
        anchors.right: _gameboard_wrapper.right
        anchors.rightMargin: displayWidth / 2
        anchors.top: _counter_title.bottom
        anchors.topMargin: displayHeight / 1.5
        displayHeight: displayWidth * 0.45
        displayWidth: parent.width * 0.35
        displayText: _gameboard.model.counter
    }



    Rectangle {
        id:_gameboard_wrapper
        width: parent.width * 0.76
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: _counter.bottom
        anchors.topMargin: height / 4
        height: width
        radius: 10

        Image {
            id: _gameboard_wrapper_img
            property bool rounded: true
            property bool adapt: true
            anchors.fill: parent
            anchors.centerIn: parent
            source: "../pics/wood_5.png"
            layer.enabled: rounded
            layer.effect: OpacityMask {
                maskSource: Item {
                    width: _gameboard_wrapper_img.width
                    height: _gameboard_wrapper_img.height
                    Rectangle {
                        anchors.centerIn: parent
                        width: _gameboard_wrapper_img.adapt ? _gameboard_wrapper_img.width : Math.min(_gameboard_wrapper_img.width, _gameboard_wrapper_img.height)
                        height: _gameboard_wrapper_img.adapt ? _gameboard_wrapper_img.height : width
                        radius: _gameboard_wrapper.radius
                    }
                }
            }

        }

        GameBoard {
            id: _gameboard
            z:_gameboard_wrapper_frame_img.z + 1
            anchors.fill: parent
            anchors.margins: 3
        }

        Image {
            id: _gameboard_wrapper_frame_img
            z: _gameboard_wrapper_img.z + 1
            source: "../pics/frame_1.png"
            property bool rounded: true
            property bool adapt: true
            anchors.fill: parent
            fillMode: Image.Stretch

            layer.enabled: rounded
            layer.effect: OpacityMask {
                maskSource: Item {
                    width: _gameboard_wrapper_frame_img.width
                    height: _gameboard_wrapper_frame_img.height
                    Rectangle {
                        anchors.centerIn: parent
                        width: _gameboard_wrapper_frame_img.adapt ? _gameboard_wrapper_frame_img.width : Math.min(_gameboard_wrapper_frame_img.width, _gameboard_wrapper_frame_img.height)
                        height: _gameboard_wrapper_frame_img.adapt ? _gameboard_wrapper_frame_img.height : width
                        radius: _gameboard_wrapper.radius
                    }
                }
            }
        }
    }

    CustomButton {
        id: _restart_button
        width: _timer.displayWidth
        height: width * 0.45
        anchors.horizontalCenter:  _timer_title.horizontalCenter
        anchors.top: _gameboard_wrapper.bottom
        anchors.topMargin: _gameboard_wrapper.height / 5
        text: qsTr("Restart")
        onClicked:  {
            _gameboard.model.restart()
        }
    }

    CustomButton {
        id: _quit_game_button
        width: _counter.displayWidth
        height: width * 0.45
        anchors.horizontalCenter:  _counter_title.horizontalCenter
        anchors.top: _gameboard_wrapper.bottom
        anchors.topMargin: _gameboard_wrapper.height / 5
        text: qsTr("Quit")
        onClicked:  {
            if(_stack_view.depth > 1){
                _stack_view.pop()
            }
        }
    }

    Rectangle {
        id: _winning_dialog_wrapper
        anchors.fill: parent
        visible: false
        color: "#80ffffff"

        Rectangle {
            id:_winning_dialog
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 10
            height: width * 1.15
            anchors.verticalCenter: parent.verticalCenter
            radius: 10

            Image {
                id: _winning_background
                property bool rounded: true
                property bool adapt: true
                anchors.fill: parent

                source: "../pics/wood_5.png"
                layer.enabled: rounded
                layer.effect: OpacityMask {
                    maskSource: Item {
                        width: _winning_background.width
                        height: _winning_background.height
                        Rectangle {
                            anchors.centerIn: parent
                            width: _winning_background.adapt ? _winning_background.width : Math.min(_winning_background.width, _winning_background.height)
                            height: _winning_background.adapt ? _winning_background.height : width
                            radius: _gameboard_wrapper.radius
                        }
                    }
                }

                Text {
                    id: _winning_text
                    text: qsTr("YOU WIN!")
                    color: "lightyellow"
                    style: Text.Outline
                    styleColor: "darksalmon"
                    font {
                        pointSize: 50
                        bold : true
                    }
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.topMargin: parent.height / 4
                }

                DropShadow {
                    anchors.fill: _winning_text
                    horizontalOffset: 6
                    verticalOffset: 6
                    color: "black"
                    source: _winning_text
                }
            }


            CustomButton {
                id: _to_main_menu_button
                width: parent.width * 0.35
                height: width * 0.5
                anchors.right: parent.right
                anchors.rightMargin: width / 4
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: height / 2
                text: qsTr("Quit")
                onClicked:  {
                    parent.visible = false
                    if(_stack_view.depth > 1) {
                        _stack_view.pop()
                    }
                }
            }

            CustomButton {
                id: _start_new_game_button
                width: parent.width * 0.35
                height: width * 0.5
                anchors.left: parent.left
                anchors.leftMargin: width / 4
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: height / 2
                text: qsTr("Restart")
                onClicked:  {
                    parent.visible = false
                    _winning_dialog_wrapper.visible = false
                    _gameboard.model.restart()
                }
            }

        }
        DropShadow {

            anchors.fill: _winning_dialog
            horizontalOffset: 6
            verticalOffset: 6
            color: "black"
            source: _winning_dialog
        }


    }

}




