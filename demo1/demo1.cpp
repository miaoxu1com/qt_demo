#include "demo1.h"

demo1::demo1(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    /// <summary>
    /// 链接点击事件和槽
    /// </summary>

    connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked));
}

demo1::~demo1()
{
    
}
/// <summary>
/// 实现声明的点击事件信号槽
/// </summary>
void demo1 :: on_pushButton_clicked()
{
    ui.lineEdit->setText("hello world");

}