import QtQuick 2.0
import Sailfish.Silica 1.0
import com.ivanbratoev.festivalsheduler 1.0

Dialog {
    id: selectFestDialog
    property string currentFest: dbConnect.currentFest

    DialogHeader {
        acceptText: "Select"
        cancelText: "Cancel"
    }

    PullDownMenu {
        MenuItem {
            text: "Add Festival"
            onClicked: pageStack.replace("AddFest.qml")
        }
    }

    SilicaFlickable {
        id : flickable
        SilicaListView {
            id: festList
            model: dbConnect.listFests()
            delegate: ListItem {
                id: festItem
                color: (currentFest === uid)? Theme.highlightColor : Theme.primaryColor
                Label { text: name }
                onClicked: {
                    currentFest = uid
                }
                PullDownMenu {
                    MenuItem {
                        text: "Delete Festival"
                        onClicked: remove()
                    }
                }
                function remove(){
                    remorse.execute(festItem, "Deleting", function() { dbConnect.removeFest(uid) })
                }
                RemorseItem { id: remorse }
            }
        }
    }

    onDone: {
        if (result === DialogResult.Accepted){
            dbConnect.currentFest = currentFest
        }
    }
}
