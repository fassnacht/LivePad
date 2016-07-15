import QtQuick 2.5
import QtGraphicalEffects 1.0

Item
{
    id: main

    property real leftChannle: 0
    property real rightChannle: 0
    property int peakResetInterval: 2000

    onLeftChannleChanged: leftPeak.update(leftChannle)
    onRightChannleChanged: rightPeak.update(rightChannle)

    Item
    {
        id: leftBar

        anchors.left: parent.left
        anchors.bottom: parent.bottom

        width: main.width*0.4

        height: parent.height*main.leftChannle
        clip: true

        Item
        {
            anchors.bottom: parent.bottom
            width: parent.width
            height: main.height

            LinearGradient
            {
                anchors.fill: parent

                gradient: Gradient {
                    GradientStop { position: 0.0; color: "red" }
                    GradientStop { position: 0.2; color: "yellow" }
                    GradientStop { position: 0.7; color: "#0ff864" }
                }
            }
        }
    }

    Item
    {
        id: rightBar

        anchors.right: parent.right
        anchors.bottom: parent.bottom

        width: main.width*0.4

        height: parent.height*main.rightChannle
        clip: true

        Item
        {
            anchors.bottom: parent.bottom
            width: parent.width
            height: main.height

            LinearGradient
            {
                anchors.fill: parent

                gradient: Gradient {
                    GradientStop { position: 0.0; color: "red" }
                    GradientStop { position: 0.2; color: "yellow" }
                    GradientStop { position: 0.7; color: "#0ff864" }
                }
            }
        }
    }

    Rectangle
    {
        id: leftPeak
        width: leftBar.width
        height: 2
        color: y > parent.height * 0.24 ? "#0ff864" : (y > parent.height*0.08 ? "yellow" : "red")
        property real leftValue: 0

        function update(value)
        {
            if(value > leftValue)
                leftValue = value
        }

        x: leftBar.x
        y: parent.height - parent.height*leftValue
    }

    Rectangle
    {
        id: rightPeak
        width: rightBar.width
        height: 2
        color: y > parent.height * 0.24 ? "#0ff864" : (y > parent.height*0.08 ? "yellow" : "red")
        property real rightValue: 0

        function update(value)
        {
            if(value > rightValue)
                rightValue = value
        }

        x: rightBar.x
        y: parent.height - parent.height*rightValue
    }

    Timer
    {
        running: true
        repeat: true
        interval: main.peakResetInterval
        onTriggered: {rightPeak.rightValue = 0; leftPeak.leftValue = 0}
    }

}
