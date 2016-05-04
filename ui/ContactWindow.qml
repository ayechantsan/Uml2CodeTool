import QtQuick 2.3
import QtQuick.Controls 1.2

ApplicationWindow {
    id: root
    title: "Contact UML2Code"
    visible: true
    width: 400
    height: 100

    Column {
           spacing: 20

           Text {
               text: 'info@uml2code.com'
                horizontalAlignment: Text.AlignHCenter
           }

           Text {
               width: root.width
               wrapMode: Text.WordWrap
               text: 'CSCI427 - University of Montana - Fall 2015/Spring 2016'
           }

           Text {
               width: root.width
               wrapMode: Text.WordWrap
               text: 'D. Stoeig, C. Albaladejo, M. Kinsey, C. Murphy, Z. Falkner, A. San'

           }

       }
}
