import QtQuick 2.5
import QtGraphicalEffects 1.0

Item
{
    id: main

    property real leftChannle: 0
    property real rightChannle: 0

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
                    GradientStop { position: 0.3; color: "#0ff864" }
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
                    GradientStop { position: 0.3; color: "#0ff864" }
                }
            }
        }
    }

}
