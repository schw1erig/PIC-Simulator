#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_toolButton_toggled(bool checked);

    void on_pushButton_5_toggled(bool checked);

    void on_test_clicked(bool checked);

    void on_test_stateChanged(int arg1);

    void on_pushButton_5_clicked();

    void on_test_clicked();

    void on_Console_Field_blockCountChanged(int newBlockCount);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
