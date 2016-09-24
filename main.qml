import QtQuick 2.5
import Helpers 1.0
import QtQuick.Controls 1.4

Rectangle
{
    id: main

    anchors.fill: parent
    color: "black"

    property alias panLayer: topLayer

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

        cacheBuffer: main.width

        model: filter.filteredList

        ChannleFilter
        {
            id: filter
            unfilteredChannles: channles
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

            isMidi: _midi
            sendModel: _sendLevel

            property real panning: _pan
            onPanningChanged: setPanning(panning)

            property real level: _level
            onLevelChanged: setVolume(level)

            color: _color

            onMuteClicked: sender.send("/live/mute%ii%"+channle+"%"+(mute ? 0 : 1));
            onSoloClicked: sender.send("/live/solo%ii%"+channle+"%"+(solo ? 1 : 0));
            onRecordClicked: sender.send("/live/arm%ii%"+channle+"%"+(record ? 1 : 0));
            onPanChanged: sender.send("/live/pan%if%"+channle+"%"+pan);
            onVolumeChanged: sender.send("/live/volume%if%"+channle+"%"+volume);

            Component.onCompleted:
            {
                setVolume(_level)
                sender.send("/live/mute%i%"+(channleNumber));
                sender.send("/live/solo%i%"+(channleNumber));
                sender.send("/live/arm%i%"+(channleNumber));
                sender.send("/live/send%i%"+(channleNumber));
                sender.send("/live/pan%i%"+(channleNumber));
                sender.send("/live/volume%i%"+(channleNumber));
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


    StackView
    {
        id: stack
        anchors.fill: parent
        initialItem: ""

        clip: true

        Component
        {
            id: groupComp
        Groups
        {
            id: groups
            height: main.height
            width: 260
            anchors.topMargin: 10
            anchors.rightMargin: 10

            colorModel: channles.colorGroups

            onCurrentFilterColorChanged: filter.filterColor = currentFilterColor

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

        Component
        {
            id: sendsComp
            Rectangle
            {
                height: main.height
                width: 150
                color: "green"
            }
        }

        Component
        {
            id: masterComp
            Rectangle
            {
                height: main.height
                width: 80
                color: "red"
            }
        }
    }
}


SideBar
{
    id: sideBar
    onSettingsClicked: settingsDialog.open()
    onCurrentAktiveChanged:
    {
        if(currentAktive != -1)
            container.open()
        else
            container.close()
            //stack.clear()

        if(currentAktive == 0)
        {
            stack.push(sendsComp)
        }
        else if(currentAktive == 1)
        {
            stack.push(groupComp)
        }
        else if(currentAktive == 2)
        {
            stack.push(masterComp)
        }
    }
}

Item
{
    id: topLayer
    anchors.fill: parent

    function getGlobalPosition(item)
    {
        var globalPos = item.mapToItem(topLayer, 0,0)
        return globalPos
    }

    function bringToFront(item, absX ,absY)
    {
        var globalPos = getGlobalPosition(item)
        item.parent = topLayer

        if(absX != undefined)
            item.x = absX
        else
            item.x = globalPos.x

        if(absY != undefined)
            item.y = absY
        else
            item.y = globalPos.y
    }

}


Settings
{
    id: settingsDialog
    ipAddress: settings.ownIp

    onIpAddressChanged:
    {
        settings.targetIp = ipAddress
        sender.send("/live/name/track")
    }

    myIp: settings.ownIp
}




Component.onCompleted: sender.send("/live/name/track");
}
