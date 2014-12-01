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

    SilicaFlickable {
        id : flickable
        anchors.top: parent.top
        anchors.fill: parent
        PullDownMenu {
            MenuItem {
                text: "Add Festival"
                onClicked: pageStack.replace("AddFest.qml", { "isEdit": false })
            }
        }

        SilicaListView {
            id: festList
            model: dbConnect.listFests()
            anchors.top: parent.top
            anchors.fill: parent
            ViewPlaceholder {
                enabled: festList.count == 0
                text: "No festivals added yet"
            }

            delegate: ListItem {
                id: festItem
                Label {
                    text: name
                    color: (currentFest === uid)? Theme.highlightColor : Theme.primaryColor
                }
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
