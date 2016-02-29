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
    title: "Select File"
    color:  "white"

        Button {
            id: load
            x: 28
            y: 307
            text: qsTr("Click to draw")
            tooltip: "load file"
            onClicked:
            {

                fileDialog.visible = true
                drawingCanvas.requestPaint()
            }

            FileDialog {
                id: fileDialog
                title: "Please choose a file"
                folder: shortcuts.home
                onAccepted: {
                    console.log("You chose: " + fileDialog.fileUrls)
                    dispatcher.loadDiagram(fileDialog.fileUrl);
                    close()
                }
                onRejected: {
                    console.log("Canceled")
                   close()
                }
                Component.onCompleted: visible = false
            }
        }


        Label {
            id: label
            x: 36
            y: 35
            width: 67
            height: 27
            text: qsTr("Pick a file")
        }



}

