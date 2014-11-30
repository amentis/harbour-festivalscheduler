import QtQuick 2.0
import Sailfish.Silica 1.0
import com.ivanbratoev.festivalsheduler 1.0

Page {
    id: editFest
    SilicaFlickable {
        id: flickable
        PullDownMenu {
            MenuItem {
                text: "Edit Festival Info"
                onClicked: pageStack.push("AddFest.qml", { "isEdit": true })
            }
            MenuItem {
                text: "Add Band"
                onClicked: pageStack.push("AddBand.qml")
            }
        }
        SilicaListView {
            id: bandsList
            model: dbConnect.listBands()
            delegate: ListItem {
                id: bandItem
                TextInput {
                    id: name
                    onDataChanged: saveTimer.restart()
                }
                PullDownMenu {
                    MenuItem {
                        text: "Remove Band"
                        onClicked: remove()
                    }
                }
                function remove(){
                    remorse.execute(bandItem, "Deleting", function() { dbConnect.removeBand(uid) })
                }
                RemorseItem { id: remorse }
                Timer {
                    id: saveTimer
                    interval: 2500
                    onTriggered: dbConnect.setBand(uid, fest, name.text, starts, ends, scene)
                    repeat: false
                }
            }
        }
    }
}
