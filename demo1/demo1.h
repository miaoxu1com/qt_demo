#pragma once

#ifndef DEMO1_H
#define DEMO1_H

#include <QtWidgets/QWidget>
#include "ui_demo1.h"

class demo1 : public QWidget
{
    Q_OBJECT

public:
    demo1(QWidget *parent = nullptr);
    ~demo1();
public slots:
    /// <summary>
    /// 声明点击事件槽
    /// </summary>
    void on_pushButton_clicked();

private:
    Ui::demo1Class ui;
};

#endif