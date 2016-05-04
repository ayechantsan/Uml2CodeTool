import QtQuick 2.3
import QtQuick.Controls 1.2

ApplicationWindow {
    id: root
    title: "Using UML2Code: Windows, Mac, and Linux"
    visible: true
    width: 700
    height: 500
ScrollView{
      anchors.fill: parent
      frameVisible: true
      highlightOnFocus: true
    Column {
            spacing: 10


           Text {
               text: 'Adding a new class'
               font.bold: true
           }

           Text {
               width: root.width
               wrapMode: Text.WordWrap
               text: 'Enter a name in "Class" textfield located in the sidebar, and hit the enter key or click on create.'
           }

           Text {
               text: 'Deleting a class'
               font.bold: true
           }

           Text {
               width: root.width
               wrapMode: Text.WordWrap
               text: 'Select the class, and click on delete or hit the delete key.'
           }

           Text {
               text: 'Making the class Abstract'
               font.bold: true
           }

           Text {
               width: root.width
               wrapMode: Text.WordWrap
               text: 'Select the class, and check the "Abstract" checkbox in the sidebar. Uncheck to undo.'
           }

           Text {
               text: 'Change to an Interface'
               font.bold: true
           }

           Text {
               width: root.width
               wrapMode: Text.WordWrap
               text: 'Select the class, and click on the "Interface" button in the sidebar to switch from a class to an interface.'
           }


           Text {
               text: 'Adding variables to a class'
               font.bold: true
           }

           Text {
               width: root.width
               wrapMode: Text.WordWrap
               text: 'Select the class, and fill in the variables in "Attributes" textbox. Example: If you want to add a public variable named age, that is an integer, you would write "public age: int". For visibility of variables (public, private, protected), please see the next tip.'
           }


           Text {
               text: 'Visibility of variables'
               font.bold: true
           }

           Text {
               width: root.width
               wrapMode: Text.WordWrap
               text: 'If you do not specify, variables will be public by default. You can choose a variable to be "public or +", "private or -", "protected or #".'
           }

           Text {
               text: 'Adding methods'
               font.bold: true
           }

           Text {
               width: root.width
               wrapMode: Text.WordWrap
               text: 'Select the class, and fill in the methods in "Methods" textbox. Example: If you want to add a private method called calculateAge() that returns nothing, you would write "private calculateAge() : void". For visibility of methods (public, private, protected), please see the previous tip.'
           }

           Text {
               text: 'Creating Inheritance'
               font.bold: true
           }

           Text {
               width: root.width
               wrapMode: Text.WordWrap
               text: 'If you want to have "Dog" inherits from "Animals", select "Dog", and write "Animals" in the "Inhertis From" textfield in the sidebar.'
           }

           Text {
               text: 'Creating Inheritance (shortcut)'
               font.bold: true
           }

           Text {
               width: root.width
               wrapMode: Text.WordWrap
               text: 'If you want to have "Dog" inherits from "Animals", select "Dog", and click on the "Inhertis From" textfield, and select "Animals".'
           }

           Text {
               text: 'Saving your workspace'
               font.bold: true
           }

           Text {
               width: root.width
               wrapMode: Text.WordWrap
               text: 'Go to "File" in the top menubar, and click on "Save", to get the workspace exported to a .uct file.'
           }

           Text {
               text: 'Opening an existing workspace'
               font.bold: true
           }

           Text {
               width: root.width
               wrapMode: Text.WordWrap
               text: 'Go to "File" in the top menubar, and click on "Open". Locate your .uct file and click on "Open".'
           }

           Text {
               text: 'Generating diagrams to code'
               font.bold: true
           }

           Text {
               width: root.width
               wrapMode: Text.WordWrap
               text: 'Go to "Code" in the top menubar, and click on "Generate". Select the language you want the code to be written in, choose the folder location for where you want the generated code to be saved, specify if you want a project file made to run in QtCreator, and click on "Generate".'
           }
       }
}}
