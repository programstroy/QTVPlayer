import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import QtMultimedia 5.8
import QtQuick.Dialogs 1.2

ToolBar {
    property alias channel: channelName.text
    property alias deleteChannel: deleteChannel

    RowLayout{
        anchors.fill: parent

        // -кнопка "Программа передач"--
        ToolButton {
            Image {
                source:  "qrc:/icons/launcher.png"
                anchors.centerIn: parent
                smooth: true
            }
            onClicked: aboutDialog.open()
            onPressAndHold: { Qt.quit() }
        }

        // -имя канала--
        Label {
            id: channelName
            font.pixelSize: 20
            elide: Label.ElideRight
            color: "white"
            horizontalAlignment: Qt.AlignLeft
            verticalAlignment: Qt.AlignVCenter
            layer.enabled: true
            layer.effect: DropShadow {
                horizontalOffset: 3
                verticalOffset: 3
                radius: 8.0
                samples: 17
                color: "#80000000"
            }
        }

        // -правый GroupBox "resize" + "список каналов" --
        Row{
            Layout.alignment:Qt.AlignRight

            //-кнопка "удалить канал"--
            ToolButton {
                id:deleteChannel
                Image {
                    source:  "qrc:/icons/close.png"
                    width: 20
                    height: 20
                    anchors.centerIn: parent
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

            //-кнопка "яркость"--
            ToolButton {
                Image {
                    source:  "qrc:/icons/brightness.png"
                    width: 20
                    height: 20
                    anchors.centerIn: parent
                    layer.enabled: true
                    layer.effect: DropShadow {
                        horizontalOffset: 3
                        verticalOffset: 3
                        radius: 8.0
                        samples: 17
                        color: "#80000000"
                    }
                }
                onClicked: {
                    box.brightness = (box.brightness == 0.5 ? box.brightness = -0.5 : box.brightness + 0.1)
                    box.status = true
                    fadeTVStatus.start()
                }
                onPressAndHold: {
                    box.brightness = (box.brightness == -0.5 ? box.brightness = 0.5 : box.brightness - 0.1)
                    box.status = true
                    fadeTVStatus.start()
                }
            }

            //-кнопка "контраст"--
            ToolButton {
                Image {
                    source:  "qrc:/icons/contrast.png"
                    width: 20
                    height: 20
                    anchors.centerIn: parent
                    layer.enabled: true
                    layer.effect: DropShadow {
                        horizontalOffset: 3
                        verticalOffset: 3
                        radius: 8.0
                        samples: 17
                        color: "#80000000"
                    }
                }
                onClicked: {
                    box.contrast = (box.contrast == 0.5 ? box.contrast = -0.5 : box.contrast + 0.1)
                    box.status = true
                    fadeTVStatus.start()
                }
                onPressAndHold: {
                    box.contrast = (box.contrast == -0.5 ? box.contrast = 0.5 : box.contrast - 0.1)
                    box.status = true
                    fadeTVStatus.start()
                }
            }

            // -кнопка "nosound"--
            ToolButton {
                Image {
                    visible: !box.mute
                    source:  "qrc:/icons/sound.png"
                    width: 20
                    height: 20
                    anchors.centerIn: parent
                    layer.enabled: true
                    layer.effect: DropShadow {
                        horizontalOffset: 3
                        verticalOffset: 3
                        radius: 8.0
                        samples: 17
                        color: "#80000000"
                    }
                }
                Image {
                    visible: box.mute
                    source:  "qrc:/icons/nosound.png"
                    width: 20
                    height: 20
                    anchors.centerIn: parent
                    layer.enabled: true
                    layer.effect: DropShadow {
                        horizontalOffset: 3
                        verticalOffset: 3
                        radius: 8.0
                        samples: 17
                        color: "#80000000"
                    }
                }
                onClicked: {
                    box.mute = !box.mute
                    box.status = true
                    fadeTVStatus.start()
                }
            }

            // -кнопка "pause"--
            ToolButton {
                Image {
                    visible: !box.pause
                    source:  "qrc:/icons/play.png"
                    width: 20
                    height: 20
                    anchors.centerIn: parent
                    layer.enabled: true
                    layer.effect: DropShadow {
                        horizontalOffset: 3
                        verticalOffset: 3
                        radius: 8.0
                        samples: 17
                        color: "#80000000"
                    }
                }
                Image {
                    visible: box.pause
                    source:  "qrc:/icons/pause.png"
                    width: 20
                    height: 20
                    anchors.centerIn: parent
                    layer.enabled: true
                    layer.effect: DropShadow {
                        horizontalOffset: 3
                        verticalOffset: 3
                        radius: 8.0
                        samples: 17
                        color: "#80000000"
                    }
                }
                onClicked: {box.pause = !box.pause}
            }

            // -кнопка "resize"--
            ToolButton {
                Image {
                    source:  "qrc:/icons/resize.png"
                    width: 20
                    height: 20
                    anchors.centerIn: parent
                    layer.enabled: true
                    layer.effect: DropShadow {
                        horizontalOffset: 3
                        verticalOffset: 3
                        radius: 8.0
                        samples: 17
                        color: "#80000000"
                    }
                }
                onClicked: {
                    switch (box.aspectRatio){
                    case VideoOutput.PreserveAspectCrop:
                        box.aspectRatio = VideoOutput.Stretch
                        box.status = true
                        fadeTVStatus.start()
                        break
                    case VideoOutput.Stretch:
                        box.aspectRatio = VideoOutput.PreserveAspectFit
                        box.status = true
                        fadeTVStatus.start()
                        break
                    case VideoOutput.PreserveAspectFit:
                        box.aspectRatio = VideoOutput.PreserveAspectCrop
                        box.status = true
                        fadeTVStatus.start()
                        break
                    }
                }
            }


            // -кнопка "загрузка xml" --
            ToolButton {
                visible: true
                Image {
                    source:  "qrc:/icons/settings.png"
                    width: 20
                    height: 20
                    anchors.centerIn: parent
                    layer.enabled: true
                    layer.effect: DropShadow {
                        horizontalOffset: 3
                        verticalOffset: 3
                        radius: 8.0
                        samples: 17
                        color: "#80000000"
                    }
                }
                onClicked: { fileDialog.open() }
            }

            // -кнопка "помощь"--
            ToolButton {
                visible: true
                Image {
                    source:  "qrc:/icons/question.png"
                    width: 20
                    height: 20
                    anchors.centerIn: parent
                    layer.enabled: true
                    layer.effect: DropShadow {
                        horizontalOffset: 3
                        verticalOffset: 3
                        radius: 8.0
                        samples: 17
                        color: "#80000000"
                    }
                }
                onClicked: {
                    messageDialog.text = qsTr("<p><b>Структура плейлиста ChannelsList.xml</b></p><p><i>" + fso.getDir() + "</i></p><p><b>&lt;ListElement&gt;</b></p><p>&nbsp;&nbsp;<b>&lt;channel_id&gt;</b>850<b>&lt;/channel_id&gt;</b></p><p>&nbsp;&nbsp;<b>&lt;caption&gt;</b>Первый<b>&lt;/caption&gt;</b></p><p>&nbsp;&nbsp;<b>&lt;source&gt;</b>http://internet_path/streaming_playlist.m3u8<b>&lt;/source&gt;</b></p><p>&nbsp;&nbsp;<b>&lt;cover&gt;</b>qrc:/covers/850.png<b>&lt;/cover&gt;</b></p><p><b>&lt;/ListElement&gt;</b></p><p>где:</p><p><b>&lt;channel_id&gt;</b> - фиксированный номер канала (не менять!!!)</p><p><b>&lt;caption&gt;</b> - наименование канала</p><p><b>&lt;source&gt;</b> - ссылка m3u8 для просмотра канала (из любого плейлиста IPTV M3U)</p><p><b>&lt;cover&gt;</b> - логотип (предустановлен 521 канал)</p><p>Приложение не содержит ссылок на интелектуальную собственность третьих лиц.</p><p>Ссылки m3u8 необходимо подставить в текущий плейлист вручную</p>")
                    messageDialog.visible = true
                }
            }
        }
    }
}

