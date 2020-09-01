import QtQuick 2.12
import QtQuick.Controls 2.12
import QtMultimedia 5.8
import QtGraphicalEffects 1.0

Rectangle{
    property  alias source: player.source
    property alias  aspectRatio: player.fillMode
    property alias mute: player.muted
    property bool pause: false
    property bool fullScreen: true
    property alias brightness: tvControl.brightness
    property alias contrast: tvControl.contrast
    property alias status: picStatus.visible
    anchors.fill: parent
    focus: true
    color: "black"

    onPauseChanged: pause? player.pause(): player.play()

    // -канал не работает--
    Label{
        id: tvStatus
        anchors.centerIn: parent
        color: "white"
        font.pixelSize: 20
        elide: Label.ElideRight
        horizontalAlignment: Qt.AlignCenter
        verticalAlignment: Qt.AlignVCenter
        visible: true
    }

    BusyIndicator {
        id: busyIndicator
        anchors.centerIn: parent
        visible: false
    }

    // -канал работает--
    Video{
        id: player
        anchors.fill: parent
        autoPlay: true
        visible: true

        MouseArea {anchors.fill: parent; onClicked: {fullScreen = !fullScreen}}

        onStatusChanged: {
            switch (status){
            case MediaPlayer.NoMedia:
                tvStatus.text = qsTr("Сигнал отсутствует")
                busyIndicator.visible = false
                break
            case MediaPlayer.Loading:
                tvStatus.text = qsTr("Поиск сигнала, подождите...")
                busyIndicator.visible = true
                break
            case MediaPlayer.Loaded:
                tvStatus.text = qsTr("Сигнал найден")
                busyIndicator.visible = false
                break
            case MediaPlayer.Buffering:
                tvStatus.text = qsTr("Буфферизация данных, подождите...")
                busyIndicator.visible = true
                break
            case MediaPlayer.Buffered:
                tvStatus.text = qsTr("")
                busyIndicator.visible = false
                break
            case MediaPlayer.Stalled:
                tvStatus.text = qsTr("Воспроизведение прервано")
                busyIndicator.visible = false
                break
            case MediaPlayer.InvalidMedia:
                tvStatus.text = qsTr("Сигнал отсутствует")
                busyIndicator.visible = false
                break
            default:
                tvStatus.text = errorString
                busyIndicator.visible = false
            }
        }
    }

    BrightnessContrast{
        id: tvControl
        anchors.fill: player
        source: player
        brightness: 0
        contrast: 0
        visible: true
    }

    Label{
        id: picStatus
        anchors.left: parent.left
        anchors.leftMargin: 10
        color: "white"
        font.pixelSize: 12
        font.weight: Font.DemiBold
        elide: Label.ElideRight
        horizontalAlignment: Qt.AlignLeft
        verticalAlignment: Qt.AlignVCenter
        visible: true
        text: "\nяркость: " + Math.round(100 + box.brightness * 100) + " %\n" +
                 "контраст: " + Math.round(100 + box.contrast * 100) + " %\n" +
                 "звук: " + (player.muted? "беззвучный" : "нормальный") + "\n" +
                 "экран: " +
              (box.aspectRatio == VideoOutput.PreserveAspectFit? "пропорционально" :
              (box.aspectRatio == VideoOutput.Stretch? "растянуть" : "обрезать"))
        layer.enabled: true
        layer.effect: DropShadow {
            horizontalOffset: 3
            verticalOffset: 3
            radius: 8.0
            samples: 17
            color: "#80000000"
        }
    }
}
