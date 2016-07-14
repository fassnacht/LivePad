import QtQuick 2.5

Item
{
    id: main

    property var colorModel: []

    signal currentState(var state)

    anchors.fill: parent

    onColorModelChanged:
    {
        listModel.clear()
        for(var i = 0; i<colorModel.count; i++)
        {
            listModel.append({color: colorModel.at(i)})
            console.log(i)
        }
    }


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

    ListView
    {
        id: listView

        width: parent.width
        anchors.top: selectButton.bottom
        anchors.topMargin: 10
        anchors.rightMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom

        model: listModel

        ListModel
        {
            id: listModel
        }

        spacing: 10

        //property string selectedGroup: model[0]

        delegate: ButtonBase
        {
            width: parent.width
            height: 70
            text: "color"
            normalColor: "#444444"
            onColor: "black"
            font.pixelSize: 20

            textColor: isOn ? "#888888" : "black"

            isOn: main.selectedGroup == modelData

            onClicked: main.selectedGroup = modelData
        }
    }
}
