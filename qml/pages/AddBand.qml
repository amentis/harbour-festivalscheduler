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

    function showScenesOrNot() {
        var fest = dbConnect.getFest(dbConnect.currentFest)
        return (fest.numberOfScenes > 1)
    }

    id: addBand
    canAccept: isValid()
    DialogHeader {
        acceptText: "Save"
        cancelText: "Cancel"
    }
    Column {
        id: forms
        TextField {
            id: name
            placeholderText: "Band name"
        }
        TimePicker {
            id: starts
        }
        TimePicker {
            id: ends
        }

        TextField {
            id: scene
            placeholderText: "Scene"
            validator: RegExpValidator { regExp: /^[0-9]$/ }
            color: errorHighlight? "red" : Theme.primaryColor
            height: showScenesOrNot()? theme.itemSizeMedium : 0
        }
    }
    onDone: if (result === DialogResult.Accepted) {
                dbConnect.setFest(dbConnect.currentFest, name.text, day.date, 1*numberOfDays.text, place.text, 1*numberOfScenes.text)
            }
}
