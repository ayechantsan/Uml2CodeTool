import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.0
ApplicationWindow {
    id: root
    visible: true
    width: 700
    height: 500
    title: "Select Folder"
    color:  "white"



            FileDialog {
                id: fileDialog
                title: "Please choose a file"
                folder: shortcuts.home
                selectFolder: true
                onAccepted: {
                    console.log("You chose: " + fileDialog.fileUrls)
                    dispatcher.saveDiagram(fileDialog.fileUrl);
                    close()
                    root.close()
                }
                onRejected: {
                    console.log("Canceled")
                    close()
                    root.close()
                }
                Component.onCompleted: visible = true
            }







}

