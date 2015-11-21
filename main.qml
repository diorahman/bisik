import QtQuick 2.5
import QtQuick.Window 2.2

Window {
    visible: true

    Rectangle {
        anchors.fill: parent

        Column {
            anchors.fill: parent

            TextInput {
                id: current
                width: parent.width
            }

            Rectangle {
                width: parent.width
                height: 50
                color: "blue"

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        App.initAccount(current.text);
                    }
                }
            }

            TextInput {
                id: to
                width: parent.width
            }

            Rectangle {
                width: parent.width
                height: 50
                color: "pink"

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        App.call(to.text);
                    }
                }
            }

            Rectangle {
                width: parent.width
                height: 50
                color: "yellow"

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        App.answer();
                    }
                }
            }

        }

    }
}

