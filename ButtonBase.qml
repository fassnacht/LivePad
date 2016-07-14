import QtQuick 2.5

MouseArea
{
    id: main

    height: 50

    property string commandString: ""

    property color normalColor: "#333333"
    property color onColor:  "#444444"

    property bool isOn: false

    property string text: "text"
    property alias font: label.font

    property int index: -1

    property alias textColor: label.color

    Rectangle
    {
        anchors.fill: parent

        color: !isOn ? normalColor : onColor
        Behavior on color {ColorAnimation{duration: 200}}


        Rectangle
        {
            id: highlighter
            anchors.fill: parent
            color: main.pressed ? "#AA222222" : "transparent"

            Behavior on color {ColorAnimation{duration: 200}}
        }

        Text
        {
            id: label
            anchors.centerIn: parent
            text: main.text
            visible: main.text != ""
            font.pixelSize: 30
        }
    }
}
