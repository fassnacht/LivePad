import QtQuick 2.5

Item
{
    id: main

    height: 400
    width: 100

    readonly property real value: 1-handle.y/(main.height-handle.height)

    function setValue(value)
    {
        if(value > 1)
            value = 1
        if(value < 0)
            value = 0

        handle.y = (main.height-handle.height)*(1-value)
    }

    Rectangle
    {
        anchors.centerIn: parent
        height: parent.height - 20
        width: 4
        color: "black"
    }

    Rectangle
    {
        id: handle
        width: 25
        height: 70
        color: "#999999"

        radius: 5

        anchors.horizontalCenter: parent.horizontalCenter

        y: main.height-height

        Rectangle
        {
            height: 2
            width: parent.width
            color: "#222222"
            anchors.centerIn: parent
        }

        MouseArea
        {
            height: parent.height
            width: main.width
            drag.target: parent
            drag.axis: Drag.YAxis
            drag.minimumY: 0
            drag.maximumY: main.height-handle.height
        }
    }

    //Component.onCompleted: setValue(0)
}
