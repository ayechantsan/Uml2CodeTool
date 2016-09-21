import QtQuick 2.3
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1


ApplicationWindow {
    id: root
    visible: true
    width: 1600
    height: 1600
    minimumWidth: 300
    minimumHeight: 300
    title: "uCode"
    color:  "white"

    function exit()
    {
        root.close();
    }

    onWidthChanged: drawingCanvas.requestPaint()
    onHeightChanged: drawingCanvas.requestPaint()

    //Creates the Menu bar at the top
    menuBar : UMenuBar {

    }

    Menu {
        id: contextMenu
        MenuItem {
            text: qsTr('Delete Class')
            onTriggered: uClassPanel.deleteMethod();
        }

        MenuItem {
            text: qsTr('Delete Inheritance')
            onTriggered:
            {
                uClassPanel.setParentField("");
                uClassPanel.updateMethod();
            }
        }
    }

    //Main Window
    RowLayout {
        id: mainWindow
        anchors.fill: parent
        spacing: 5

        // Creates the Canvas to draw the UML Diagram
        UDrawingCanvas {
            id: drawingCanvas
            Layout.preferredWidth: parent.width * 0.75
            Layout.preferredHeight: parent.height
            onHeightChanged: gridLayout.setHeight(Number(height));
            onWidthChanged: gridLayout.setWidth(Number(width));

            Keys.onDeletePressed: {
                uClassPanel.deleteMethod();
                event.accepted = true;
            }

            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                onPressed: {
                    drawingCanvas.selectedX = mouse.x
                    drawingCanvas.selectedY = mouse.y
                    drawingCanvas.selectClass(mouse.x, mouse.y)
                    drawingCanvas.forceActiveFocus()
                    if (mouse.button == Qt.RightButton && !gridLayout.isEmpty(mouse.x, mouse.y))
                    {
                        console.log("Right Click")
                        contextMenu.popup()
                    }
                }
                onMouseXChanged: drawingCanvas.moveClass(mouse.x, mouse.y)
                onMouseYChanged: drawingCanvas.moveClass(mouse.x, mouse.y)
                onReleased: drawingCanvas.releasedMouse(mouse.x, mouse.y)
                cursorShape: Qt.UpArrowCursor

            }
        }


        //Right column with buttons and boxes
        ColumnLayout {
            id: sideWindow
            spacing : 5
            Layout.preferredWidth: parent.width * 0.25
            Layout.preferredHeight: parent.height
            Layout.margins: 10
            Layout.leftMargin: 5

            // Buttons Class and Interface
            UClassTypeSelection {
                id: uClassSelection
                Layout.preferredWidth: parent.width
                Layout.preferredHeight: parent.height * 0.05
            }

            //Boxes and buttons Create and Update
            UClassPanel {
                id : uClassPanel
                Layout.preferredWidth: parent.width
                Layout.preferredHeight: parent.height * 0.95
            }
        }
    }
}
