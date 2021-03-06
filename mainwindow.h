#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QApplication>
#include <QString>

namespace Ui {
    class MainWindow;
}

const int normal = 0;
const int warning = 1;
const int critical = 2;

const QString small = "abcdefghijklmnopqrstuvwxyz";
const QString big = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const QString number = "0123456789";
const QString special = "!@#$%^&*|";


class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QApplication *app, QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    unsigned long long last;
    unsigned long long beforeLast;

    void setError(int code, QString error = "");
    QString parseAddress(QString);
    unsigned int rand();
    void swap(QByteRef a, QByteRef b);
private slots:
    void recalculate();
    void showPass(bool);
    void showAbout();
};

#endif // MAINWINDOW_H
