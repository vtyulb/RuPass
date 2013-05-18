#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QApplication *app, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->password->setEchoMode(QLineEdit::Password);
    ui->password->setFocus();
    ui->siteLine->setReadOnly(true);
    ui->passwordLine->setReadOnly(true);
    ui->loginLine->setReadOnly(true);

    QObject::connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    QObject::connect(ui->actionAbout_Qt, SIGNAL(triggered()), app, SLOT(aboutQt()));
    QObject::connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));
    QObject::connect(ui->password, SIGNAL(textChanged(QString)), this, SLOT(recalculate()));
    QObject::connect(ui->address, SIGNAL(textChanged(QString)), this, SLOT(recalculate()));
    QObject::connect(ui->checkBox, SIGNAL(clicked(bool)), this, SLOT(showPass(bool)));

    recalculate();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::recalculate() {
    QString site = parseAddress(ui->address->text());
    QString password = ui->password->text();
    if (password.length() < 2)
        setError(critical, tr("Password must contains at least 2 symbols"));
    else {
        if (password.length() < 6)
            setError(warning, tr("Password is too small for avoiding collisions"));
        else
            setError(normal);

        long long hash = 0;
        long long p = password[0].unicode() * 256 + password[1].unicode();
        last = password[password.length() - 1].unicode();
        beforeLast = password[password.length() - 2].unicode();
        password.remove(0, 2);
        QString main = password.left(password.length() / 2) + site + password.right((password.length() + 1) / 2);
        for (int i = 0; i < main.length(); i++) {
            hash *= p;
            hash += main[i].unicode() * rand();
        }

        last = hash << 32;
        beforeLast = hash >> 32;

        main = "";
        for (int i = 0; i < 6; i++) main += '0'; // small latin
        for (int i = 0; i < 2; i++) main += '1'; // number
        for (int i = 0; i < 1; i++) main += '2'; // big latin
        for (int i = 0; i < 1; i++) main += '3'; // special

        for (int i = 1; i < 10; i++)
            swap(main[i], main[rand() % i]);

        for (int i = 0; i < 10; i++)
            main = '0' + main;

        for (int i = 0; i < 20; i++)
            if (main[i] == '0')
                main[i] = small[rand() % small.length()];
            else if (main[i] == '1')
                main[i] = number[rand() % number.length()];
            else if (main[i] == '2')
                main[i] = big[rand() % big.length()];
            else if (main[i] == '3')
                main[i] = special[rand() % special.length()];

        ui->siteLine->setText(site);
        ui->passwordLine->setText(main.right(10));
        ui->loginLine->setText(main.left(10));
    }
}

void MainWindow::setError(int code, QString error) {
    if (code == normal) {
        ui->errorLabel->hide();
        ui->outputBox->show();
    } else if (code == critical) {
        ui->errorLabel->setText(error);
        ui->errorLabel->show();
        ui->outputBox->hide();
    } else {
        ui->errorLabel->setText(error);
        ui->errorLabel->show();
        ui->outputBox->show();
    }
}

QString MainWindow::parseAddress(QString address) {
    address = address.toLower();
    for (int i = 0; i < address.length(); i++)
        if ((address[i] == ':') || (address[i] == '/') || (address[i] == '.') || (address[i] == ' '))
            address.remove(i--, 1);

    if (address.left(5) == "https")
        address = address.right(address.length() - 5);

    if (address.left(4) == "http")
        address = address.right(address.length() - 4);

    if (address.left(3) == "www")
        address = address.right(address.length() - 3);

    return address;
}

int MainWindow::rand() {
    long long i = beforeLast * 999999937 + last * 31 + 1;
    beforeLast = last;
    last = i;
    if (int(i) < 0)
        return -int(i);
    else
        return int(i);
}

void MainWindow::swap(QCharRef a, QCharRef b) {
    QChar c = a;
    a = b;
    b = c;
}

void MainWindow::showPass(bool show) {
    if (show)
        ui->password->setEchoMode(QLineEdit::Normal);
    else
        ui->password->setEchoMode(QLineEdit::Password);
}

void MainWindow::showAbout() {
    QMessageBox::about(this, tr("about RuPass"), tr("RuPass - simple program for generation\npasswords and logins.\nWritten by russian author - Vladislav Tyulbashev.\nvladislav.tyulbashev@yandex.ru"));
}
