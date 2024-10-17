import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 2.15
import QtQuick.Layouts


Window {
    visible: true
    width: 640
    height: 480
    title: "My Window"
    color: "blue"
    ColumnLayout
    {
        Text
        {
            id: tid
            text: "Hello, World!"
        }


        Button
        {
            property int counter : 0

            onClicked:
            {
                counter++
                var str = "updated test_" + counter
                tid.text = str
                console.log("button pressed_"+ str)
            }

            text: "pressme"
        }
     }
}
