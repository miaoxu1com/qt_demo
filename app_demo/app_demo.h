#pragma once

#include <QtWidgets/QWidget>
#include "ui_app_demo.h"
#include <QFutureWatcher>
class app_demo : public QWidget
{
    Q_OBJECT

public:
    app_demo(QWidget *parent = nullptr);
    ~app_demo();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked(); // 生成案例
    void onParsingFinished();
private:
    Ui::app_demoClass ui;
    QFutureWatcher<bool>* m_watcher = nullptr;
};

