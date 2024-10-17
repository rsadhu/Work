import QtQuick 2.0
import QtQuick.Controls 2.15

import MyModule 1.0   // Import the module registered in main.cpp

Window {
    visible: true
    width: 640
    height: 480
    color: "blue"

    Column
    {

        MyCustomClass {
            id: myClass
            name: "QtApp"
            count: 5

            // React to custom signal
            onCustomSignal: {
                console.log("Received message from C++: " + message)
            }

            onNameChanged:
            {
                console.log("hello this is handler for the signal nameChanged")
            }

            onCountChanged:
            {
                console.log("hello this is handler for the signal ountChanged")
            }
    }

        Button {
            text: "Increment Count"
         onClicked: {
             myClass.incrementCount()
          }
      }

      Button {
          //color: "red"
          text: "Send Message"
          onClicked: {
              myClass.showMessage("Hello from QML!")

          }
      }

      Text {
          text: "Count: " + myClass.count
      }
    }
}
