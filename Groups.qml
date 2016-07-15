import QtQuick 2.5

Item
{
    id: main

    property var colorModel: []

    signal currentState(var state)

    property string currentFilterColor: "#000000"

    anchors.top: parent.top
    anchors.bottom: parent.bottom
    width: 260

    ButtonBase
    {
        id: selectButton
        property int currentState: 0

        normalColor: "#444444"

        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 10
        width: parent.width -20
        height: 60

        text:
        {
            if (currentState == 0 ) return "All"
            if (currentState == 1 ) return "Audio"
            if (currentState == 2 ) return "Midi"
        }

        onClicked:
        {
            if(currentState >= 2)
                currentState = 0
            else
                currentState = currentState + 1

            main.currentState(currentState)
        }

    }

    Flickable
    {
        id: flickable

        clip: true

        anchors.top: selectButton.bottom
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom

        contentWidth: content.width
        contentHeight: content.height

        Column
        {
            id: content
            spacing: 10

            ColorGroupButton
            {
                normalColor: "#000000"
                isOn: currentFilterColor == normalColor
                onClicked: main.currentFilterColor = normalColor
            }

            Repeater
            {
                model: channles.colorGroups

                ColorGroupButton
                {
                    isOn: currentFilterColor == normalColor
                    onClicked: main.currentFilterColor = normalColor
                }
            }
        }
    }
}
