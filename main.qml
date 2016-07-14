import QtQuick 2.5
import Helpers 1.0

Rectangle
{
    id: main

    anchors.fill: parent
    color: "black"

    ListView
    {
        id: listview

        anchors.right: container.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left

        anchors.topMargin: 10
        anchors.leftMargin: 10
        anchors.bottomMargin: 10
        anchors.rightMargin: 10

        orientation: ListView.Horizontal

        clip: true

        model: filter.filteredList

        ChannleFilter
        {
            id: filter
            unfilteredChannles: channles
            filterColor: groups.currentFilterColor
        }

        delegate: Channle
        {
        width: (main.width-80-5)/8
        channleNumber: _channleNumber
        channleName: _name
        mute: _mute
        solo: _solo
        record: _record
        selected: _selected

        sendModel: _sendLevel

        color: _color

        onMuteClicked: sender.send("/live/mute%ii%"+channle+"%"+(mute ? 0 : 1));
        onSoloClicked: sender.send("/live/solo%ii%"+channle+"%"+(solo ? 1 : 0));
        onRecordClicked: sender.send("/live/arm%ii%"+channle+"%"+(record ? 1 : 0));

        Component.onCompleted:
        {
            sender.send("/live/mute%i%"+(channleNumber));
            sender.send("/live/solo%i%"+(channleNumber));
            sender.send("/live/arm%i%"+(channleNumber));
            sender.send("/live/send%i%"+(channleNumber));
        }
    }
}

Rectangle
{
    id: container
    x: main.width - sideBar.width

    Behavior on x {NumberAnimation{duration: 200}}

    anchors.verticalCenter: parent.verticalCenter
    height: parent.height
    width: 260
    color: "#333333"

    property bool opened: false

    function open()
    {
        container.x = main.width - sideBar.width - container.width
        opened = true
    }

    function close()
    {
        container.x = main.width - sideBar.width
        opened = false
    }

    function toggelContainer()
    {
        if(container.x == main.width - sideBar.width - container.width)
            container.close()
        else
            container.open()
    }

    Groups
    {
        id: groups

        anchors.topMargin: 10
        anchors.rightMargin: 10

        colorModel: channles.colorGroups

        onCurrentState:
        {
            if(state == 0)
            {
                filter.audioOnly = false
                filter.midiOnly = false
            }

            if(state == 1)
            {
                filter.audioOnly = true
                filter.midiOnly = false
            }

            if(state == 2)
            {
                filter.audioOnly = false
                filter.midiOnly = true
            }
        }
    }
}


Rectangle
{
    id: sideBar
    anchors.right: parent.right
    anchors.verticalCenter: parent.verticalCenter
    width: 80
    height: parent.height
    color: "#222222"

    Column
    {
        id: menu
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter

        property int currentAktive: -1

        ButtonBase
        {
            index: 0
            width: sideBar.width
            height: sideBar.width
            text: "S"
            normalColor: "#222222"
            onColor: "#333333"
            isOn: menu.currentAktive == index && container.opened
            onClicked:
            {
                menu.currentAktive = index
                container.toggelContainer()
            }
        }

        ButtonBase
        {
            index: 1
            width: sideBar.width
            height: sideBar.width
            text: "G"
            normalColor: "#222222"
            onColor: "#333333"
            isOn: menu.currentAktive == index && container.opened
            onClicked:
            {
                menu.currentAktive = index
                container.toggelContainer()
            }
        }

        ButtonBase
        {
            index: 2
            width: sideBar.width
            height: sideBar.width
            text: "M"
            normalColor: "#222222"
            onColor: "#333333"
            isOn: menu.currentAktive == index && container.opened
            onClicked:
            {
                menu.currentAktive = index
                container.toggelContainer()
            }
        }
    }

    Column
    {
        id: transport
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        ButtonBase
        {
            width: sideBar.width
            height: sideBar.width

            onColor: "#ff3223"
            text: ""

            normalColor: "#222222"

            Item
            {
                width: 20
                height: width
                anchors.centerIn: parent
                clip: true
                Rectangle
                {

                    color: "black"
                    width: 20
                    height: width
                    rotation: 45
                    x: -6
                }
            }
        }

        ButtonBase
        {
            width: sideBar.width
            height: sideBar.width

            onColor: "#ff3223"
            text: ""

            normalColor: "#222222"

            Rectangle
            {
                anchors.centerIn: parent
                color: "black"
                width: 20
                height: width
                radius: 10
            }
        }

        Item
        {
            width: sideBar.width
            height: 10
        }

        ButtonBase
        {
            width: sideBar.width
            height: sideBar.width
            text: "All"
            onColor: "#ff3223"
            isOn: true

            onClicked:
            {
                for(var i = 0; i < channles.count(); i++)
                {
                    console.log("Arm")
                    sender.send("/live/arm%ii%"+i+"%"+1);
                }
            }
        }

        ButtonBase
        {
            width: sideBar.width
            height: sideBar.width
            text: "S"
            isOn: true
            onColor: "#2883c9"

            onClicked:
            {

                for(var i = 0; i < channles.count(); i++)
                {
                    console.log("Solo")
                    sender.send("/live/solo%ii%"+i+"%"+0);
                }
            }
        }
    }
}

Component.onCompleted: sender.send("/live/name/track");
}
