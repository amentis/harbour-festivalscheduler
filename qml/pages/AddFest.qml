import QtQuick 2.0
import Sailfish.Silica 1.0
import com.ivanbratoev.festivalsheduler 1.0

Dialog {
    function isValid() {
        if (name.text !== "" && numberOfDays.text !== "" && place.text !== "" && numberOfScenes.text !== "" && (1*numberOfDays.text) > 0 && (1*numberOfScenes.text) > 0){
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
    Column {
        id: forms
        TextField {
            id: name
            placeholderText: "Festival name"
            text: isEdit? dbConnect.getFest(dbConnect.currentFest).name : ""
        }
        DatePicker {
            id: day
            date: isEdit? dbConnect.getFest(dbConnect.currentFest).day : ""
        }
        TextField {
            id: numberOfDays
            text: isEdit? dbConnect.getFest(dbConnect.currentFest).numberOfDays : 1
            placeholderText: "Number of Days"
            validator: RegExpValidator { regExp: /^[0-9]$/ }
            color: errorHighlight? "red" : Theme.primaryColor
        }
        TextField {
            id: place
            placeholderText: "Place"
            text: isEdit? dbConnect.getFest(dbConnect.currentFest).place : ""
        }
        TextField {
            id: numberOfScenes
            text: isEdit? dbConnect.getFest(dbConnect.currentFest).numberOfScenes : 1
            placeholderText: "Number of Scenes"
            validator: RegExpValidator { regExp: /^[0-9]$/ }
            color: errorHighlight? "red" : Theme.primaryColor
        }
    }
    onDone: if (result === DialogResult.Accepted) {
                dbConnect.setFest(dbConnect.currentFest, name.text, day.date, 1*numberOfDays.text, place.text, 1*numberOfScenes.text)
            }
}
