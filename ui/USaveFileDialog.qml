import QtQuick 2.1
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.0
import MyModules 1.0

ApplicationWindow {
    id: root
    visible: true
    width: 700
    height: 500
    title: "Select Folder"
    color:  "white"

    function openSaveFile()
    {
        saveFile.open();
    }

    function openLoadFile()
    {

        loadFileDialog.visible = true

    }

    FileSaveDialog {
        id: saveFile
        title: "Save file"
        filename: "untitled.uct"
        nameFilters: ["Uml Code (*.uct)", "All files (*)"]

        onAccepted: {
            uDebugger.qPrintText("You chose: " + saveFile.fileUrl)

            var names = gridLayout.getAllNames();
            var nameArray = names.split(" "); //Adds void class by default
            console.log("names array " + nameArray);
            var locationArrayX = [];
            var locationArrayY = [];

            for (var i = 0; i < nameArray.length; i++)
            {
                locationArrayX[i] = gridLayout.getClassX(nameArray[i]);
                locationArrayY[i] = gridLayout.getClassY(nameArray[i]);

                uDebugger.qPrintText("name: " + nameArray[i] + " X: " + locationArrayX[i] + " Y: " + locationArrayY[i]);
            }
            if(nameArray.length > 1)
                dispatcher.saveDiagram(saveFile.fileUrl, nameArray, locationArrayX, locationArrayY);

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

    FileDialog {
        id: loadFileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        onAccepted: {
            gridLayout.cleanAll();
            dispatcher.clearAll();
            var words =  dispatcher.loadDiagram(loadFileDialog.fileUrl);
            words = words
            var splitWords = words.split(" ");
            uDebugger.qPrintText(splitWords);
            for (var i = 1; i< splitWords.length; i++)
            {

                var x = dispatcher.getClassX(splitWords[i]);
                var y = dispatcher.getClassY(splitWords[i]);

               // gridLayout.addClass(k * (width/5), j * (height/5), drawingCanvas.getClassWidth(), drawingCanvas.getClassHeight(), splitWords[i])
                uDebugger.qPrintText("Postion: (" + x + "," + y +"), Name: " +splitWords[i]);
                gridLayout.addClass(x, y, x + drawingCanvas.getClassWidth(), y + drawingCanvas.getClassHeight(), splitWords[i]);

            }
            drawingCanvas.requestPaint();
            uClassPanel.clearTextFields();
            close();
            root.close()
        }
        onRejected: {
            console.log("Canceled");
            close();
            root.close()
        }
        Component.onCompleted: visible = false
    }

}

