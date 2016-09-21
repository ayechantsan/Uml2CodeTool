import QtQuick 2.3
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.0

ApplicationWindow
{
    id: closeDialog
    width: 500
    height: 50
    title: "Are you sure you want to close? Unsaved changes would be lost"

    RowLayout{
        Button {

            StyledText {
                text: "Yes"
            }
            Layout.fillHeight: true
            Layout.fillWidth: true
            onClicked: {
                root.exit()
            }
        }
        Button {

            StyledText {
                text: "No"
            }
            Layout.fillHeight: true
            Layout.fillWidth: true
            onClicked: {
                closeDialog.close()
            }
        }
    }
}


