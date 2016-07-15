import QtQuick 2.5
import QtQuick.Controls 1.4

Rectangle
{
    id: main

    anchors.fill: parent
    color: "#77000000"

    opacity: 1.0
    onOpacityChanged: opacity == 0.0 ? visible = false : visible = true

    property alias ipAddress: ipTextfield.text
    property alias port: portTextfield.text
    property string myIp: "1.2.3.4"

    function close()
    {
        main.opacity = 0.0;
    }

    function open()
    {
        main.opacity = 1.0
    }

    MouseArea
    {
        anchors.fill: parent
        onClicked: main.close()
    }

    Behavior on opacity
    {
        NumberAnimation {duration: 300}
    }

    Rectangle
    {
        anchors.fill: parent
        anchors.margins: 100

        color: "#222222"

        MouseArea{anchors.fill: parent}

        Text
        {
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.margins: 20
            text: "Settings"
            color: "#999999"
            font.pixelSize: 32
        }

        Flickable
        {
            id: flickable

            anchors.fill: parent
            anchors.topMargin: 72
            anchors.leftMargin: 20
            Column
            {
                width: parent.width

                Item
                {
                    width: flickable.width
                    height: 50
                    anchors.left: parent.left

                    Row
                    {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.left: parent.left

                        Text
                        {
                            text: "IP Address of the device: "
                            color: "#999999"
                            width: contentWidth
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        Text
                        {
                            text: main.myIp
                            color: "#999999"
                            width: contentWidth
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }
                }

                Item
                {
                    width: flickable.width
                    height: 50
                    anchors.left: parent.left

                    Row
                    {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.left: parent.left

                        spacing: 20

                        Text
                        {
                            text: "IP Address of pc running Ableton Live"
                            color: "#999999"
                            width: contentWidth
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        TextField
                        {
                            id: ipTextfield
                            text: "192.68.0.207"
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }
                }

                Item
                {
                    width: flickable.width
                    height: 50
                    anchors.left: parent.left

                    Row
                    {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.left: parent.left

                        spacing: 20

                        Text
                        {
                            text: "Target port"
                            color: "#999999"
                            width: contentWidth
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        TextField
                        {
                            id: portTextfield
                            text: "7788"
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }
                }
            }
        }
    }
}
