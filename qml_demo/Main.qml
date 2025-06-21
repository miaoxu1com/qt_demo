import QtQuick 2.17
import QtQuick.Controls 2.17
import QtQuick.Layouts 1.17

ApplicationWindow {
    visible: true
    width: 640
    height: 800
    title: "功能测试表单"

    ListModel {

        id: formModel
        ListElement { label: "类型"; value: "功能测试" }
        ListElement { label: "作者"; value: "苗栩" }
        ListElement { label: "标签"; value: "20250410" }
        ListElement { label: "优先级"; value: "中" }
        ListElement { label: "节点路径"; value: "AAA" }
        ListElement { label: "应用"; value: "Target-LPS" }
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 10
        Rectangle {
               width: 20
               height: 0
               color: "transparent"
        }
        Repeater {
            model: formModel

            delegate: RowLayout {
                Layout.fillWidth: true

                Label {
                    font.pixelSize: 16
                    text: label + ":"
                    Layout.preferredWidth: 60
                }

                TextField {
                    Layout.preferredHeight: 30
                    font.pixelSize: 16
                    text: value
                    Layout.fillWidth: true

                }
            }
        }

        Label {
            font.pixelSize: 16
            text: "已选择文件列表:"
            font.bold: true
        }

        TextArea {
            id: selectedFilesTextArea
            placeholderText: " "
            Layout.fillWidth: true
            Layout.preferredHeight: 100
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 150
            Button {
                font.pixelSize: 16
                text: "选择文件"
                onClicked: console.log("选择思维导图文件按钮被点击")
            }

            Button {
                font.pixelSize: 16
                text: "生成案例"
                onClicked: console.log("生成Excel用例按钮被点击")
            }
        }

        Label {
            font.pixelSize: 16
            text: "已生成的案例列表:"
            font.bold: true
        }

        TextArea {
            id: generatedCasesTextArea
            placeholderText: " "
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredHeight: 150
        }
    }
}
