#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtWidgets/QWidget>
#include <QMainWindow>
#include <QFutureWatcher>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked(); // 生成案例
    void onParsingFinished();
private:
    Ui::MainWindow *ui;
    QFutureWatcher<bool>* m_watcher = nullptr;
};
#endif // MAINWINDOW_H
