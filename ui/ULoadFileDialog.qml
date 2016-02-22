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
            text: qsTr("Button")
            tooltip: "load file"
            onClicked:
            {

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

