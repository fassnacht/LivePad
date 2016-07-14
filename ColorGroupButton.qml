import QtQuick 2.5

ButtonBase
{
    width: flickable.width
    height: 70
    text: normalColor
    normalColor: modelData
    onColor: normalColor
    font.pixelSize: 20
    textColor: isOn ? "white" : "black"

    Rectangle
    {
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        height: parent.height
        width: 10
        color: "#AAFFFFFF"
        visible: isOn
    }
}
