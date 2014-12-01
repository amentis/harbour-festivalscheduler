import QtQuick 2.0
import Sailfish.Silica 1.0
import com.ivanbratoev.festivalsheduler 1.0

Dialog {
    function isValid() {
        if (name.text !== "" && day.text !== "Choose Date" && numberOfDays.text !== "1" && place.text !== "" && numberOfScenes.text !== 1 && (1*numberOfDays.text) > 0 && (1*numberOfScenes.text) > 0){
            return true
        } else {
            return false
        }
    }

    property bool isEdit

    id: addFest
    canAccept: isValid()
    DialogHeader {
        acceptText: "Save"
        cancelText: "Cancel"

    }
    SilicaFlickable {
        Column {
            id: forms
            anchors {
                top: parent.top
                margins: 5 * Theme.paddingLarge
            }
            width: addFest.width
            spacing: Theme.paddingMedium
            TextField {
                width: parent.width
                id: name
                x: Theme.paddingMedium
                placeholderText: "Festival name"
                label: "Festival name"
                text: isEdit? dbConnect.getFest(dbConnect.currentFest).name : ""
                EnterKey.enabled: text.length > 0
                EnterKey.iconSource: "image://theme/icon-m-enter-next"
                EnterKey.onClicked: focus = false
            }
            Button {
                id: day
                width: parent.width - 5
                x: Theme.paddingMedium
                property date date
                text: "Choose Date"
                onClicked: {
                    var datePicker = pageStack.push(pickerDialog)
                    datePicker.accepted.connect(function() {
                        date = pickerDialog.date
                        text = pickerDialog.dateText
                        flick.scrollToBottom()
                    })
                }
                DatePickerDialog {
                    id: pickerDialog
                }
            }

            TextField {
                id: numberOfDays
                width: parent.width
                x: Theme.paddingMedium
                text: isEdit? dbConnect.getFest(dbConnect.currentFest).numberOfDays : 1
                placeholderText: "Number of Days"
                label: "Number of Days"
                validator: IntValidator { bottom: 1; top: 10 }
                color: errorHighlight? "red" : Theme.primaryColor
                inputMethodHints: Qt.ImhNoPredictiveText
                EnterKey.enabled: text.length > 0
                EnterKey.iconSource: "image://theme/icon-m-enter-next"
                EnterKey.onClicked: place.focus = true
            }
            TextField {
                id: place
                width: parent.width
                x: Theme.paddingMedium
                placeholderText: "Place"
                label: "Place"
                text: isEdit? dbConnect.getFest(dbConnect.currentFest).place : ""
                EnterKey.enabled: text.length > 0
                EnterKey.iconSource: "image://theme/icon-m-enter-next"
                EnterKey.onClicked: numberOfScenes.focus = true
            }
            TextField {
                id: numberOfScenes
                width: parent.width
                x: Theme.paddingMedium
                text: isEdit? dbConnect.getFest(dbConnect.currentFest).numberOfScenes : 1
                placeholderText: "Number of Scenes"
                label: "Number of Scenes"
                validator: IntValidator { bottom: 1; top: 10 }
                color: errorHighlight? "red" : Theme.primaryColor
                inputMethodHints: Qt.ImhNoPredictiveText
                EnterKey.enabled: text.length > 0
                EnterKey.iconSource: "image://theme/icon-m-enter-next"
                EnterKey.onClicked: focus = false
            }
        }
    }
    onDone: if (result === DialogResult.Accepted) {
                dbConnect.setFest(dbConnect.currentFest, name.text, day.date, 1*numberOfDays.text, place.text, 1*numberOfScenes.text)
            }
}
