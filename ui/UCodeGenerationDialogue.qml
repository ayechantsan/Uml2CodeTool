import QtQuick 2.3
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.0

ApplicationWindow {
    id: root
    visible: true
    width: 700
    height: 500
    title: "Code Generation"
    color:  "white"


    ColumnLayout {
        Layout.margins: 20
        anchors.fill: parent

        RowLayout {
            Layout.margins: 20
            Layout.fillHeight: true
            Layout.fillWidth: true
            Label {
                Layout.fillHeight: true
                Layout.fillWidth: true
                StyledText {
                    text: "Language"
                    horizontalAlignment: Text.AlignLeft
                }
            }
            ComboBox {
                id: languageCB
                model: [ "None", "C++", "Java", "Python" ]
                onCurrentIndexChanged: {
                    dispatcher.setLanguage(languageCB.currentText);
                   genButton.visible = true
                }

            }
        }

        RowLayout {
            Layout.margins: 20
            Layout.fillHeight: true
            Layout.fillWidth: true
            Label {
                id: fileLocationLbl
                Layout.fillHeight: true
                Layout.fillWidth: true
                StyledText {
                    text: "Folder"
                    horizontalAlignment: Text.AlignLeft
                }
            }
            Button {
                StyledText {
                    text: "Choose Folder"
                }
                onClicked: {
                    loadFileDialog.visible = true;
                }
                FileDialog {
                    id: loadFileDialog
                    title: "Please choose a folder"
                    folder: shortcuts.home
                    selectFolder: true
                    onAccepted: {


                        console.log("Accepted "+fileUrl);
                        dispatcher.setUrl(fileUrl);
                        fileLocationLbl.text = fileUrl;
                    }
                    onRejected: {

                    }
                    Component.onCompleted: visible = false
                }
            }
        }

        RowLayout {
            Layout.margins: 20
            Layout.fillHeight: true
            Layout.fillWidth: true
            Label {
                Layout.fillHeight: true
                Layout.fillWidth: true
                StyledText {
                    text: "Project File"
                    horizontalAlignment: Text.AlignLeft
                }
            }
            ComboBox {
                id: projectCB
                model: [ "None", "Visual Studio", "QtCreator" ]
                onCurrentIndexChanged: {
                    dispatcher.setDevEnv(projectCB.currentText);
                }
            }
        }

//        RowLayout {
//            Layout.margins: 20
//            Layout.fillHeight: true
//            Layout.fillWidth: true
//            Label {
//                Layout.fillHeight: true
//                Layout.fillWidth: true
//                StyledText {
//                    text: "Doxygen Comments"
//                    horizontalAlignment: Text.AlignLeft
//                }
//            }
//            CheckBox {
//                checked: false
//            }
//        }

        RowLayout {
            Layout.margins: 20
            Layout.fillHeight: true
            Layout.fillWidth: true
            Button {
                StyledText {
                    text: "Cancel"
                }
                onClicked: {
                    close()
                }

            }
            Button {
                id: genButton
                visible: false
                StyledText {
                    text: "Generate"

                }
                onClicked: {
                    //TODO
                    dispatcher.generateCode()
                    dispatcher.generateProjectFile()
                    close()
                }
            }
        }
    }
}

