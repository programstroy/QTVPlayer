import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import QtQuick.XmlListModel 2.12

Rectangle {
    property int icon_size: 64
    property int window_height: 74
    property int window_width: parent.width
    property int curIndex: 0
    property string caption: ""
    property string source: ""

    color: "#0095d0"
    width: window_width
    height: window_height

    // -один элемент--
    Component {
        id: delegate

        Item {
            width: tvColumn.width
            height: tvColumn.height

            Column {
                id: tvColumn

                Rectangle{
                    width: tvIcon.width + 2
                    height: tvIcon.height + 2
                    color: "white"
                    Image {
                        id: tvIcon
                        width: icon_size
                        height: icon_size
                        source: cover
                        smooth: true
                        anchors.centerIn: parent
                    }
                    layer.enabled: true
                    layer.effect: DropShadow{
                        horizontalOffset: 3
                        verticalOffset: 3
                        radius: 8.0
                        samples: 17
                        color: "#80000000"
                    }
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: tvView.currentIndex = index
            }
        }
    }

    // -превьюер--
    Connections {
        target: fso
        onDataUpdated: {
            tvList.reload()
            tvView.update()
            tvView.positionViewAtIndex(curIndex,PathView.Center)
            tvView.positionViewAtIndex(curIndex,PathView.Center)
        }
    }

    Component {
        id: highlightComponent
        Rectangle {
            width: window_height - 2
            height: window_height - 2
            opacity: 1
            color: "red"
            Rectangle{
                anchors.centerIn: parent
                width: window_height - 6
                height: window_height - 6
                opacity: 1
                color: "#0095d0"
            }
        }
    }

    PathView {
        property bool moving: false
        property int spacing: Math.round(window_width / (icon_size + 6))

        id: tvView
        anchors.fill: parent
        model: XmlListModel {
            id: tvList
            source: fso.getPath()
            query:  "/ListModel/ListElement[source != '']"
            XmlRole {name: "channel_id"; query: "channel_id/string()"}
            XmlRole {name: "caption"; query: "caption/string()"}
            XmlRole {name: "source"; query: "source/string()"}
            XmlRole {name: "cover"; query: "cover/string()"}
        }
        delegate: delegate
        highlight: highlightComponent
        preferredHighlightBegin: 0.5
        preferredHighlightEnd: 0.5
        focus: true
        pathItemCount: spacing

        Keys.onLeftPressed: decrementCurrentIndex()
        Keys.onRightPressed: incrementCurrentIndex()

        path: Path{
            startX: 0
            startY: window_height / 2
            PathLine {x: window_width + icon_size / 2; y: window_height / 2}
        }

        onCurrentItemChanged: {
            if (!moving){
                caption = tvList.get(currentIndex).caption
                source =  tvList.get(currentIndex).source
                telegid.setChannel(tvList.get(currentIndex).channel_id)
            }
        }
        onMovementStarted: moving = true
        onMovementEnded: moving = false

        Connections{
            target: tools.deleteChannel
            onClicked: {
                curIndex = tvView.currentIndex - 1
                fso.removeChannel(tvList.get(tvView.currentIndex).channel_id,
                                  tvList.get(tvView.currentIndex).caption)
            }
        }
    }
}

