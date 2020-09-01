import QtQuick 2.12
import QtQuick.Controls 1.4
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Material 2.12
import QtGraphicalEffects 1.0
import Qt.labs.settings 1.0
import QtQml.Models 2.12
import ru.programmstroy.QTVPlayer 1.0

ApplicationWindow   {
    id: main
    visible: true
    width: 640
    height: 480
    Material.theme: Material.Light
    title: qsTr("QTVPlayer")
    footer: TVSelector { id:selector; visible: box.fullScreen }
    header: TVToolBar { id: tools; channel: selector.caption; visible: box.fullScreen }
    TVBox { id: box; source: selector.source }

    Connections {
        target: telegid
        onDataUpdated: {
            tvShowListView.model = model
        }
    }

    Timer{
        id: fadeTVStatus
        interval: 5000
        repeat: false
        running: true
        onTriggered: { box.status = false }
    }

    Settings{
        id: settings
        property alias brightness: box.brightness
        property alias contrast: box.contrast
        property alias aspectRatio: box.aspectRatio
        property alias mute: box.mute
    }

    Dialog {
        id: aboutDialog
        modal: true
        focus: true
        width: parent.width
        contentHeight: aboutColumn.height
        background: Item { FastBlur { anchors.fill: parent; source: parent } }

        Column {
            id: aboutColumn
            spacing: 10

            Label {
                width: aboutDialog.availableWidth
                text: qsTr("Программа передач")
                wrapMode: Label.Wrap
                font.pixelSize: 16
                font.bold: true
                color: "white"
            }

            ListView {
                id: tvShowListView
                width: aboutDialog.availableWidth
                height: aboutDialog.availableHeight
                spacing: 5
                //model:  - по умолчанию модель отсутствует, присваивание при выборе канала
                delegate: Label {
                    width: aboutDialog.availableWidth
                    text: modelData;
                    wrapMode: Label.Wrap
                    font.pixelSize: 12
                    font.bold: true
                    color: "white"
                }
            }

        }

        MouseArea{
            width: parent.width
            height: parent.height
            enabled: aboutDialog.visible
            parent: aboutDialog.contentItem
            onPressed: aboutDialog.close()
        }
    }

    Dialog {
        id: messageDialog
        parent: ApplicationWindow.overlay
        visible: false
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
        focus: true
        modal: true
        Material.theme: Material.Dark
        Material.accent: Material.Purple
        property alias text: messageText.text
        Label {
            id: messageText
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            anchors.fill: parent
        }
        standardButtons: Dialog.Ok
    }

    Drawer {
        id: fileDialog
        width: parent.width
        height: parent.height
        edge : Qt.RightEdge
        Material.theme: Material.Dark

        ItemSelectionModel {
            id: sel
            model: fso
            objectName: "filesSelected"
        }

        TreeView {
            id: view
            height: fileDialog.height - butbox.height - 2
            width: fileDialog.width
            model: fso
            rootIndex: fso.getRootIndex()
            selection: sel
            selectionMode: SelectionMode.SingleSelection
            alternatingRowColors: true
            style: TreeViewStyle{}

            TableViewColumn {
                title: qsTr("Файл")
                role: "fileName"
                resizable: true
                width: fileDialog.width / 20 * 10
            }

            TableViewColumn {
                title: qsTr("Размер")
                role: "size"
                resizable: false
                horizontalAlignment : Text.AlignRight
                width: fileDialog.width / 20 * 4
            }

            TableViewColumn {
                title: qsTr("Дата")
                role: "lastModified"
                resizable: false
                width: fileDialog.width / 20 * 6
            }

            onClicked : {
                var url = fso.data(index, FileSystemModel.UrlStringRole)
                url = url.substr(url.length - 2)
                if (url === ".."){
                    fso.upToDir()
                    view.rootIndex = fso.getRootIndex()
                }
                else{
                    if(!view.isExpanded(index))
                        view.expand(index)
                    else
                        view.collapse(index)
                }
            }
        }

        Row {
            id: butbox
            anchors.right: view.right
            anchors.top: view.bottom
            anchors.rightMargin: 5
            spacing: 5

            Button {
                text: "добавить\nплейлист"
                Material.theme: Material.Light
                highlighted: true
                Material.accent: Material.Orange
                Material.elevation: 6
                onClicked: {
                    fso.addItems(sel.selectedIndexes)
                    fso.replaceXml()
                    fileDialog.close()
                    if (fso.getXMLName() !== ""){
                        messageDialog.text = qsTr("загружен файл " + fso.getXMLName())
                        messageDialog.visible = true
                    }
                    else{
                        messageDialog.text = qsTr("формат не поддерживается")
                        messageDialog.visible = true
                    }
                }
            }
            Button {
                text: "экспорт\nконфигурации"
                Material.theme: Material.Light
                Material.elevation: 6
                onClicked: {
                    fso.addItems(sel.selectedIndexes)
                    fso.saveXml()
                    fileDialog.close()
                    messageDialog.text = qsTr("выгружен файл " + fso.getXMLName())
                    messageDialog.visible = true
                }
            }
            Button {
                text: "отмена\n"
                Material.theme: Material.Light
                Material.elevation: 6
                onClicked: {
                    fileDialog.close()
                }
            }
        }
    }
}
