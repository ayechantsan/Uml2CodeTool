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
                    //need a loop to go thruoght the classes i the gridLayout classes to gather an array to pass
                    //to the dispatcher to save the locations of the classes.
//                    var nowTime = gridLayout.getClasses();
//                    for (var i = 0; i < nowTime; i++)
//                    {

//                    }

//                    var x = gridLayout.getClassX(name);
//                    var y = gridLayout.getClassY(name);

                   var names = gridLayout.getAllNames();


                    var nameArray = names.split(" ");
                     console.log("names array " + nameArray);
                    var locationArrayX = [];
                    var locationArrayY = [];
                    
                    for (var i = 0; i < nameArray.length; i++)
                    {
                        locationArrayX[i] = gridLayout.getClassX(nameArray[i]);
                        locationArrayY[i] = gridLayout.getClassY(nameArray[i]);

                        console.log("name: " + nameArray[i] + " X: " + locationArrayX[i] + " Y: " + locationArrayY[i]);
                    }
                    

                    //dispatcher.saveDiagram(fileDialog.fileUrl, nameArray, locationArrayX, locationArrayY);
                    dispatcher.saveDiagram(fileDialog.fileUrl, nameArray, locationArrayX, locationArrayY);

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

