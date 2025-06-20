import QtQuick 2.17
import QtQuick.Window 2.17
import QtQuick.Controls 2.17
import QtQuick.Layouts 1.17
import QtQuick.Shapes 1.17

Window {
    visible: true
    width: 400
    height: 500
    title: "Qt 6.9 登录界面示例"
    color: "#f0f0f0"

    // 背景渐变
    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#e0f2f1" }
            GradientStop { position: 1.0; color: "#ffffff" }
        }
    }

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 20

        Text {
            text: "欢迎登录"
            font.pixelSize: 24
            font.bold: true
            color: "#333"
        }

        TextField {
            id: usernameField
            placeholderText: "用户名"
            Layout.fillWidth: true
            padding: 8

            background: Rectangle {
                radius: 8
                border.color: "#ccc"
                color: "#fff"
            }
        }

        TextField {
            id: passwordField
            placeholderText: "密码"
            echoMode: TextInput.Password
            Layout.fillWidth: true
            padding: 8

            background: Rectangle {
                radius: 8
                border.color: "#ccc"
                color: "#fff"
            }
        }

        Button {
            text: "登录"
               Layout.alignment: Qt.AlignHCenter
               width: 200
               padding: 10

               // 自定义背景
               background: Rectangle {
                   color: parent.parent.pressed ? "#00796b" : "#26a69a"
                   radius: 10
                   border.color: "#004d40"
                   border.width: 2
               }

               // 使用 contentItem 自定义文本样式
               contentItem: Text {
                   text: parent.parent.text
                   font: parent.parent.font
                   color: "white"
                   horizontalAlignment: Text.AlignHCenter
                   verticalAlignment: Text.AlignVCenter
               }

            onClicked: {
                console.log("用户点击了登录");
                loginMessage.text = "登录成功！";
                loginMessage.visible = true;
            }
        }

        Text {
            id: loginMessage
            visible: false
            text: "登录成功！"
            color: "green"
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
        }
    }
}
