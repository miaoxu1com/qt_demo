#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "xmindparser.h"
#include "excelwriter.h"
#include <QMessageBox>
#include <QtConcurrent/QtConcurrentRun>
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_watcher = new QFutureWatcher<bool>(this);
    connect(m_watcher, &QFutureWatcher<bool>::finished, this, &MainWindow::onParsingFinished);
}

// 根据命名Qt 的自动连接机制
void MainWindow::on_pushButton_clicked() {
    // 使用QFileDialog打开文件选择对话框，并设置过滤器只显示.xmind文件
    QString filePath = QFileDialog::getOpenFileName(this, "选择文件", "", "XMind Files (*.xmind);;All Files (*)");

    if (!filePath.isEmpty()) {
        // 将选中的文件路径显示在textBrowser_2控件中
        ui->textBrowser->setText(filePath);
    }
}
void MainWindow::on_pushButton_2_clicked() {
    QString path = ui->lineEdit->text();
    if (path.isEmpty()) {
        QMessageBox::warning(this, "告警", "请先选择 XMind 文件！");
        return;
    }

    QFuture<bool> future = QtConcurrent::run([=]() -> bool {
        QList<TestCase> cases = XmindParser::parseXmindFile(path);
        return ExcelWriter::writeTestCasesToExcel(cases, "out.xlsx");
    });

    m_watcher->setFuture(future);
}

void MainWindow::onParsingFinished() {
    bool result = m_watcher->future().result();
    qDebug() << "Parsing finished with result:" << result;
}

MainWindow::~MainWindow()
{
    delete ui;
}
