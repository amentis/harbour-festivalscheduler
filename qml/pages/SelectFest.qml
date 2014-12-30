import QtQuick 2.0
import Sailfish.Silica 1.0
import com.ivanbratoev.festivalsheduler 1.0

Dialog {
    id: selectFestDialog
    property string currentFest: dbConnect.currentFest

    DialogHeader {
        id: header
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
                onClicked: {
                    var dialog = pageStack.push("AddFest.qml", { "isEdit": false })
                    dialog.accepted.connect(function(){
                        festList.model = dbConnect.listFests()
                    })
                }
            }
        }

        SilicaListView {
            id: festList
            model: dbConnect.listFests()
            anchors.fill: parent
            anchors.topMargin: Theme.itemSizeLarge

            ViewPlaceholder {
                enabled: festList.count == 0
                text: "No festivals added yet"
            }

            delegate: ListItem{
                width: parent.width
                id: festItem
                contentHeight: Theme.itemSizeMedium
                highlightedColor: Theme.highlightColor
                highlighted: currentFest === model.modelData.uid

                Label {
                    x: Theme.paddingLarge
                    height: Theme.itemSizeSmall
                    width: parent.width / 2
                    text: model.modelData.name
                    color: Theme.primaryColor
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: Theme.fontSizeLarge
                }

                Label {
                    x: Theme.paddingLarge + parent.width / 2
                    height: Theme.itemSizeSmall
                    width: parent.width / 2 - 2 * Theme.paddingLarge
                    text: model.modelData.day.toLocaleDateString(Qt.LocalDate, Locale.ShortFormat)
                    color: Theme.secondaryColor
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignRight
                }

                Label {
                    x: Theme.paddingLarge
                    height: Theme.itemSizeMedium
                    text: model.modelData.place
                    color: Theme.secondaryColor
                    font.pixelSize: Theme.fontSizeSmall
                    verticalAlignment: Text.AlignBottom
                    horizontalAlignment: Text.AlignLeft
                    width: parent.width / 2
                }

                Label {
                    x: Theme.paddingLarge + parent.width / 2
                    height: Theme.itemSizeMedium
//                    text: ((model.modelData.numberOfScenes > 1)? model.modelData.numberOfScenes + " scenes   " : "") +
//                          ((model.modelData.numberOfDays > 1)? model.modelData.numberOfDays + " days" : "")
                    text: qsTr(model.modelData.numberOfScenes)
                    color: Theme.secondaryColor
                    font.pixelSize: Theme.fontSizeSmall
                    verticalAlignment: Text.AlignBottom
                    horizontalAlignment: Text.AlignRight
                    width: parent.width / 2 - 2 * Theme.paddingLarge
                }

                onClicked: {
                    currentFest = model.modelData.uid
                }

                menu: contextMenu

                ContextMenu{
                    id:contextMenu
                    MenuItem{
                        text: "Edit Festal Info"
                        onClicked: {
                            dbConnect.setCurrentFest(model.modelData.uid)
                            var dialog = pageStack.push("AddFest.qml", { "isEdit": true })
                            dialog.accepted.connect(function(){
                                festList.model = dbConnect.listFests()
                            })
                        }
                    }
                    MenuItem{
                        text: "Delete Festival"
                        onClicked: {
                            remorseAction("Deleting " + model.modelData.name,
                                            function(){
                                                dbConnect.removeFest(model.modelData.uid)
                                                festList.model = dbConnect.listFests()
                                            })
                        }
                    }
                }

                function remove(){
                    remorse.execute(festItem, "Deleting", function() { dbConnect.removeFest(model.modelData.uid) })
                }
            }
        }
    }
    onDone: {
        if (result === DialogResult.Accepted){
            dbConnect.currentFest = currentFest
        }
    }
}
