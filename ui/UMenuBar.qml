import QtQuick 2.3
import QtQuick.Window 2.1
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.0
import MyModules 1.0

MenuBar {
    id: mainMenuBar

    Menu {

        title: "File"

        MenuItem {
            text: "Open"
            onTriggered: {
                var component = Qt.createComponent("USaveFileDialog.qml");
                var win = component.createObject(root);
                win.show();
                win.openLoadFile()
            }
        }

        MenuItem {
            text: "Save"
            onTriggered: {
                
                var component = Qt.createComponent("USaveFileDialog.qml");
                var win = component.createObject(root);
                win.show();
                win.openSaveFile()
            }
        }

        MenuItem {
            text: "Close"
            onTriggered:
            {
                var component = Qt.createComponent("uCloseDialog.qml");
                var win = component.createObject(root);
                win.show();
            }
        }

    }

//    Menu {
//        title: "Edit"

//        MenuItem {
//            text: "Cut"
//        }

//        MenuItem {
//            text: "Copy"
//        }

//        MenuItem {
//            text: "Paste"
//        }
//    }

    Menu {
        title: "Code"

        MenuItem {
            text: "Generate"
            onTriggered: {
                var component = Qt.createComponent("UCodeGenerationDialogue.qml");
                var win = component.createObject(root);
                win.show();
            }
        }

    }

    Menu {
        title: "Help"

        MenuItem {
            text: "Guide"
        }

        MenuItem {
            text: "About"
        }

    }
}
