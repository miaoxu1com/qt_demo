#include "stdafx.h"
#include "app_demo.h"
#include "xmindparser.h"
#include "excelwriter.h"
#include <QMessageBox>
#include <QtConcurrent/QtConcurrentRun>
#include <QDebug>

app_demo::app_demo(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	// qt手动绑定按钮事件到响应函数
	//connect(ui.pushButton, &QPushButton::clicked, this, &app_demo::on_pushButton_clicked);
	m_watcher = new QFutureWatcher<bool>(this);
	connect(m_watcher, &QFutureWatcher<bool>::finished, this, &app_demo::onParsingFinished);
}
// 根据命名Qt 的自动连接机制
void app_demo::on_pushButton_clicked() {
	// 使用QFileDialog打开文件选择对话框，并设置过滤器只显示.xmind文件
	QString filePath = QFileDialog::getOpenFileName(this, "选择文件", "", "XMind Files (*.xmind);;All Files (*)");

	if (!filePath.isEmpty()) {
		// 将选中的文件路径显示在textBrowser_2控件中
		ui.textBrowser->setText(filePath);
	}
}
void app_demo::on_pushButton_2_clicked() {
	QString path = ui.lineEdit->text();
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

void app_demo::onParsingFinished() {
	bool result = m_watcher->future().result();
	qDebug() << "Parsing finished with result:" << result;
}

app_demo::~app_demo()
{
}