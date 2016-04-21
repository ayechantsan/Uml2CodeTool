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
            text: "Open..."
            onTriggered: {
                var component = Qt.createComponent("ULoadFileDialog.qml");
                var win = component.createObject(root);
                win.show();
            }
        }

        MenuItem {
            text: "Close"
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
            text: "Load"
            onTriggered: {

                var component = Qt.createComponent("USaveFileDialog.qml");
                var win = component.createObject(root);
                win.show();
                win.openLoadFile()
            }

        }

    }

    Menu {
        title: "Edit"

        MenuItem {
            text: "Cut"
        }

        MenuItem {
            text: "Copy"
        }

        MenuItem {
            text: "Paste"
        }
    }

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

    }

    Menu {
        title: "About"
    }

}
