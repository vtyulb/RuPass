#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QApplication *app, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->password->setEchoMode(QLineEdit::Password);

    QObject::connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    QObject::connect(ui->actionAbout_Qt, SIGNAL(triggered()), app, SLOT(aboutQt()));
    QObject::connect(ui->password, SIGNAL(textChanged(QString)), this, SLOT(recalculate()));
    QObject::connect(ui->address, SIGNAL(textChanged(QString)), this, SLOT(recalculate()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::recalculate() {

}
