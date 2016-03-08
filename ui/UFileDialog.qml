import QtQuick 2.3
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.0

FileDialog {
    id: saveFileDialog
    title: "Please choose a folder"
    folder: shortcuts.home
    selectFolder: true
    onAccepted: {
        console.log("Accepted "+fileUrl);
        dispatcher.url = fileUrl;
    }
    onRejected: {

    }
    Component.onCompleted: visible = true
}
