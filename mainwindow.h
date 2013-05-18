#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QApplication>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QApplication *app, QWidget *parent = 0);
    ~MainWindow();

    QString small = "abcdefghijklmnopqrstuvwxyz";
    QString big = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    QString number = "0123456789";
    QString special = "!@#$%^&*|";
private:
    Ui::MainWindow *ui;
    long long last;
    long long beforeLast;

    void setError(QString);
    QString parseAddress(QString);
    int rand();
    void swap(QCharRef a, QCharRef b);
private slots:
    void recalculate();
    void showPass(bool);
    void showAbout();
};

#endif // MAINWINDOW_H
