import QtQuick 2.0

Rectangle
{
    id: pan

    readonly property real panning: bigIndicator.panning

    function setPanning(pan)
    {
        bigIndicator.setPanning(pan)
    }

    color: "#222222"
    width: 100
    height: 40

    Rectangle
    {
        id: background
        color: "black"
        anchors.centerIn: parent
        width: parent.width
        height: 10
    }

    //### bar distance indicators
    Rectangle
    {
        anchors.left: half.right
        anchors.right: smallIndicator.right
        height: 8
        color: "#774444FF"
        anchors.verticalCenter: parent.verticalCenter
    }

    Rectangle
    {
        anchors.right: half.right
        anchors.left: smallIndicator.right
        height: 8
        color: "#774444FF"
        anchors.verticalCenter: parent.verticalCenter
    }
    Item
    {
        id: half
        anchors.left: parent.left
        width: parent.width/2
        height: parent.height
    }
    //###

    Rectangle
    {
        id: smallIndicator
        height: 8
        width: 10
        color: "#4444FF"
        x: (parent.width-width)*bigIndicator.x/(bigView.width-bigIndicator.width)

        //            x: (parent.width-width)*panning
        //            property real panning: 0.5
        //            onPanningChanged: console.log(panning)
        anchors.verticalCenter: parent.verticalCenter
    }

    MouseArea
    {
        id: indicatorArea
        anchors.centerIn: parent
        width: parent.width
        height: parent.height
        drag.target: bigIndicator
        drag.axis: Drag.XAxis
        drag.minimumX: 0
        drag.maximumX: bigView.width - bigIndicator.width
    }

    //### what is seen when it gets pressed
    Rectangle
    {
        id: bigView
        //anchors.centerIn: parent

        width: pan.width*3
        height: pan.height*2

        color: "#774444FF"
        visible: indicatorArea.pressed
        onVisibleChanged:
        {
            if(visible)
                panLayer.bringToFront(bigView)
            else
            {
                bigView.parent = pan
                x = -width/2+pan.width/2
                y = -pan.height/2
            }
        }

        Rectangle
        {
            height: parent.height
            width:20
            anchors.centerIn: parent
            color: "#22FFFFFF"
        }

        Rectangle
        {
            id: bigIndicator
            height: parent.height
            width: 20
            color: "#4444FF"
            x: bigView.width/2-width/2
            property real panning: (x-bigView.width/2+bigIndicator.width/2)/(bigView.width/2-bigIndicator.width/2)

            function setPanning(pan)
            {
                if(pan > 1.0)
                    pan = 1.0
                if(pan < -1.0)
                    pan = -1.0

                pan = pan/2 +0.5
                x = (bigView.width-width)*pan
            }
        }
    }
    //###

}
