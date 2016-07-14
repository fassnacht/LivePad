import QtQuick 2.5

Item
{
    id: main

    width: 128
    height: parent.height

    property string channleName: "name"
    property int channleNumber: 0

    property bool mute: false
    property bool record: false
    property bool solo: false
    property bool selected: false

    property color color: "#FFFFFF"

    property var sendModel: [0.7, 0.2, 0.3, 0.5, 1.0, 0.2, 0.7, 0.2, 0.3, 0.5, 1.0, 0.2]

    signal muteClicked(var channle, var mute)
    signal soloClicked(var channle, var solo)
    signal recordClicked(var channle, var record)

    Rectangle
    {
        anchors.fill: parent
        anchors.margins: 2
        color: selected? "#333333" : "#222222"

        Text
        {
            id: name
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            text: main.channleName
            font.bold: true
            font.pixelSize: 16
            color: "#888888"
            elide: Text.ElideRight
            width: parent.width-10
            horizontalAlignment: Text.AlignHCenter
        }

        Rectangle
        {
            id: colorRect
            width: parent.width
            height: 10
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: name.bottom
            anchors.topMargin: 10
            color: main.color
        }

        Meter
        {
            id: bars
            width: 80
            height: parent.height -20

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: controls.top
            anchors.bottomMargin: 10
            anchors.top: colorRect.bottom
            anchors.topMargin: 10

            function updateLeft(channle, value)
            {
                if(channle == main.channleNumber)
                    bars.leftChannle = value
            }

            function updateRight(channle, value)
            {
                if(channle == main.channleNumber)
                    bars.rightChannle = value
            }
        }

        Column
        {
            id: controls

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter

            spacing: 10

            Rectangle //sends
            {
                color: "#333333"
                width: main.width-20
                height: 50

                SmallSends
                {
                    anchors.fill: parent
                    model: main.sendModel
                }
            }

            ButtonBase
            {
                width: main.width-20
                height: main.width-20
                text: channleNumber+1
                isOn: !main.mute
                onColor: "#ffc907"
                font.bold: true

                onClicked: main.muteClicked(main.channleNumber, !isOn)
            }

            ButtonBase
            {
                width: main.width-20
                isOn: main.solo
                text: "S"
                onColor: "#2883c9"
                font.pixelSize: 24

                onClicked: main.soloClicked(main.channleNumber, !isOn)
            }

            ButtonBase
            {
                width: main.width-20
                text: ""

                isOn: main.record
                onColor: "#ff3223"

                onClicked: main.recordClicked(main.channleNumber, !isOn)

                Rectangle
                {
                    anchors.centerIn: parent
                    color: "black"
                    width: 20
                    height: width
                    radius: 10
                }
            }
        }
    }


    //### CONNECTIONS ###
    Component.onCompleted:
    {
        meters.sig_leftChannleMeterUpdated.connect(bars.updateLeft)
        meters.sig_rightChannleMeterUpdated.connect(bars.updateRight)
    }
    Component.onDestruction:
    {
        meters.sig_leftChannleMeterUpdated.disconnect(bars.updateLeft)
        meters.sig_rightChannleMeterUpdated.disconnect(bars.updateRight)
    }
}

