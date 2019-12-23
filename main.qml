import QtQuick 2.12
import QtQuick.Window 2.12
import threadtest 1.0

Window {
    id: window
    visible: true
    width: 640
    height: 480
    color: "#000000"
    title: qsTr("Hello World")

    Text {
        id: element
        x: 190
        y: 188
        width: 261
        height: 104
        color: "#ffffff"
        text: qsTr("EDIT ME!!")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 44

        Updater.onHasWork:  {
            if (arg === 1) {
                element.text = "Hello World!"
                element.color = "#ffffff"
                window.color = "#000000"
            } else {
                element.text = ":D"
                element.color = "000000"
                window.color = "#ffffff"
            }
        }

        /*Updater {
            onHasWork: {
                if (arg === 1) {
                    element.text = "Hello World!"
                    element.color = "#ffffff"
                    window.color = "#000000"
                } else {
                    element.text = ":D"
                    element.color = "000000"
                    window.color = "#ffffff"
                }
            }
        }*/
    }
}
