import QtQuick 2.5

Rectangle
{
    id: sideBar
    anchors.right: parent.right
    anchors.verticalCenter: parent.verticalCenter
    width: 80
    height: parent.height
    color: "#222222"

    property int currentAktive: -1

    signal settingsClicked()

    Column
    {
        id: menu
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter



        function allExclusiveOff()
        {
            groupsButton.isOn = false
            sendsButton.isOn = false
            masterButton.isOn = false
        }

        ButtonBase
        {
            id: settingButton
            index: 0
            width: sideBar.width
            height: sideBar.width
            text: ""
            normalColor: "#222222"
            onColor: "#333333"
            onClicked: sideBar.settingsClicked()
        }

        ButtonBase
        {
            id: sendsButton
            index: 0
            width: sideBar.width
            height: sideBar.width
            text: "S"
            normalColor: "#222222"
            onColor: "#333333"
            onClicked:
            {
                if(isOn)
                {
                    sideBar.currentAktive = -1
                    menu.allExclusiveOff()
                }
                else
                {
                    menu.allExclusiveOff()
                    isOn = true
                    sideBar.currentAktive = index
                }
            }
        }

        ButtonBase
        {
            id: groupsButton
            index: 1
            width: sideBar.width
            height: sideBar.width
            text: "G"
            normalColor: "#222222"
            onColor: "#333333"
            onClicked:
            {
                if(isOn)
                {
                    sideBar.currentAktive = -1
                    menu.allExclusiveOff()
                }
                else
                {
                    menu.allExclusiveOff()
                    isOn = true
                    sideBar.currentAktive = index
                }
            }
        }

        ButtonBase
        {
            id: masterButton
            index: 2
            width: sideBar.width
            height: sideBar.width
            text: "M"
            normalColor: "#222222"
            onColor: "#333333"
            onClicked:
            {
                if(isOn)
                {
                    sideBar.currentAktive = -1
                    menu.allExclusiveOff()
                }
                else
                {
                    menu.allExclusiveOff()
                    isOn = true
                    sideBar.currentAktive = index
                }
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
