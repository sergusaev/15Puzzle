import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import "qml" as MyQml

ApplicationWindow {
    id:root
    width: 360
    height: 640
    visible: true
    title: qsTr("15-puzzle")

    StackView {
        id: _stack_view
        anchors.fill: parent
        initialItem: _authorization_window_stack_page
    }

    Component {
        id: _authorization_window_stack_page
        MyQml.AuthorizationPage {
            id:_authorization_window
        }

    }

    Component {
        id:  _new_user_stack_page
        MyQml.NewUserPage {
        }


    }
    Component {
        id: _main_menu_stack_page
        MyQml.MainMenu {
            id:_main_menu
        }
    }

    Component {
        id:  _gameboard_stack_page
        MyQml.GamePanel {
        }
    }

    Component {
        id:  _records_stack_page
        MyQml.Records {
        }
    }

    onClosing: {
        Qt.quit()
    }

}
