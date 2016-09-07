import QtQuick 2.5

Item
{
    id: main

    property real currentValue: 0.0

    function setValue(value)
    {
//        if(value > 1.0)

//        if(value < 0.0)
    }

    Rectangle
    {
        id: indicator
        width: parent.width/2
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: main.height * currentValue
        color: "red"
    }

    Rectangle
    {
        id: handle


    }

}
