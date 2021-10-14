import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQml 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.15

ApplicationWindow {

    id:root
    width: 800
    height: 600
    visible: true
    title: qsTr("Management FRDMK64F")
    opacity: 1
    flags: Qt.Window | Qt.FramelessWindowHint
    visibility: visibilityFlag === false ? "Windowed" : "FullScreen"

    Material.theme: Material.Dark
    Material.accent: Material.DeepOrange
    Material.background: Material.BlueGrey
    Material.foreground:  Material.DeepPurple

    property string time
    property string date
    property bool visibilityFlag: false
    property bool pendingState: false


    BusyIndicator
    {
        id: busyIndicator
        width: parent.width/8
        height: width
        running: pendingState
        visible: running
        anchors.centerIn: parent
        z: parent.z + 1
    }

    Component.onCompleted:
    {
        pendingState = true
    }

    StackView
    {
        id:stack
        initialItem: startView
    }

    Component
    {
        id:startView
        Column
        {
            Text
            {
                id: _starttext
                text: qsTr("startView")
                font.family: "Mongolian Baiti"
                font.pointSize: 16
                font.bold: true
            }
        }
    }

    Component
    {
        id:communicationView
        Column
        {
            Text
            {
                Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
                id: _commtext
                text: qsTr("communicationView")
                font.family: "Mongolian Baiti"
                font.pointSize: 16
                font.bold: true
            }
        }
    }

    Timer
    {
        interval: 1000; running: true; repeat: true
        onTriggered:
        {
            time =  Qt.formatTime(new Date(), "hh:mm:ss")
            date = Qt.formatDate(new Date(), Qt.ISODate)

            pendingState = false
        }
    }

header: ToolBar
        {
            id:menutoolbar
            MouseArea
            {
                property var clickPos
                clickPos: "1,1"
                anchors.fill: parent

                onPressed:
                {
                    clickPos  = Qt.point(mouse.x,mouse.y)
                }

                onPositionChanged:
                {
                    var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
                    root.x += delta.x;
                    root.y += delta.y;
                }
                onDoubleClicked:
                {
                    visibilityFlag = !visibilityFlag
                }
            }
            contentHeight: toolButton.implicitHeight

            ToolButton
            {
                id: toolButton
                Text
                {
                    id: name
                    text: stack.depth > 1 ? "\u2B98" : "\u2630"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    font.bold: true
                    font.pointSize: 16
                    color: "#2c81e0"
                }
                font.pixelSize: Qt.application.font.pixelSize * 1.6
                onClicked:
                {
                    if (stack.depth < 2) {
                        drawer.open()
                    }
                    else
                    {
                        stack.pop()
                    }
                }
            }
            Drawer {
                  id: drawer
                  width: root.width * 0.3
                  height: root.height

                  Column {
                      anchors.fill: parent
                      anchors.topMargin: 10

                      ItemDelegate {

                          id:delegateCamSettings
                          text: qsTr("Communication FRDMK64F")
                          width: parent.width
                          onClicked: {
                              stack.push(communicationView)
                              drawer.close()
                          }
                      }
                  }
            }

            RowLayout
            {
                anchors.fill: parent
                spacing: 20
                Button
                {
                    id:logoutbtn
                    Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
                    width: 30
                    height: 30
                    Layout.leftMargin: 180
                    Layout.minimumWidth: 30
                    Layout.minimumHeight: 40

                    background: Rectangle
                    {
                        color:"transparent"
                    }
                    Image
                    {
                        width: 30
                        height: 30
                        id: logoutimage
                        anchors.verticalCenter: parent.verticalCenter
                        source: "qrc:/Images/logout.svg"
                        sourceSize.width: 30
                        sourceSize.height: 30
                        fillMode: Image.PreserveAspectFit
                    }
                    onClicked:
                    {
                        Qt.quit()
                    }
                }
            }
        }
}
