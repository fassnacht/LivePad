import QtQuick 2.5

MouseArea
{
    id: main

    property alias model: repeater.model

    Row
    {
        id: row
        spacing: 2

        anchors.bottom: parent.bottom

        Repeater
        {
            id: repeater

            model: 12

            Rectangle
            {
                height:
                {
                    if(modelData == 0)
                        return main.height*0.01
                    else
                        return main.height*modelData
                }
                width: (main.width-11*2)/12

                anchors.bottom: row.bottom
                color: "#888888"
            }
        }
    }
}
