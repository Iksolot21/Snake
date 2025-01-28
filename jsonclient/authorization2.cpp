#include "authorization2.h"
#include "ui_authorization2.h"
#include "menu.h"
#include "application.h"
#include "mainwindow.h"
#include "playerinfo.h"
#include <QThread>
#include <QPropertyAnimation>

authorization2::authorization2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::authorization2)
{
    ui->setupUi(this);
    connect(Application::getSocket(), &QTcpSocket::readyRead, this, &authorization2::sockReady);

}

authorization2::~authorization2()
{
    disconnect(Application::getSocket(), &QTcpSocket::readyRead, this, &authorization2::sockReady);
    delete ui;
}

void authorization2::on_pushButton_3_clicked()
{
    connect(Application::getSocket(), &QTcpSocket::readyRead, this, &authorization2::sockReady);
    if (Application::getSocket()->state() != QAbstractSocket::ConnectedState &&
        Application::getSocket()->state() != QAbstractSocket::ConnectingState) {
        Application::getSocket()->connectToHost("127.0.0.1", 23232);
    }
        QString username = ui->lineEdit_3->text();
        QString password = ui->lineEdit_4->text();
        QString queryStr = "SELECT name, password, block FROM listworkers WHERE name = '" + username + "' AND password = '" + password + "' AND (block <> 1 or block is NULL)";
        MainWindow mainWindow(nullptr);
        mainWindow.SendToServer(queryStr);

}

void authorization2::on_lineEdit_4_editingFinished()
{
    password = ui->lineEdit_4->text();
}

void authorization2::on_lineEdit_3_editingFinished()
{
    username = ui->lineEdit_3->text();
}

void authorization2::sockReady()
{
    Data = Application::getSocket()->readAll();
    qDebug() << "Data received:" << Data;

    QString username = ui->lineEdit_3->text();
    QString password = ui->lineEdit_4->text();

    if (Data == "Connection Successful")
    {
        if (username == "admin" && password == "admin") {
            QMessageBox::information(this, "Login Successful", "You have been successfully logged by admin.");
            Admin *admin = new Admin();
            close();
            admin->show();
        } else {
            QMessageBox::information(this, "Login Successful", "You have been successfully logged in.");
            Menu *menu = new Menu();
            menu->setUsername(ui->lineEdit_3->text());
            close();
            menu->setWindowOpacity(0.0);
            menu->showFullScreen();

            QPropertyAnimation *animation = new QPropertyAnimation(menu, "windowOpacity");
            animation->setDuration(500);
            animation->setStartValue(0.0);
            animation->setEndValue(1.0);
            animation->start(QAbstractAnimation::DeleteWhenStopped);
        }
    }
    else if (Data == "Incorrect username or password")
    {
        QMessageBox::warning(this, "Login Unsuccessful", "Incorrect username or password.");
    }
    else if (Data == "Registration Successful")
    {
        QMessageBox::information(this, "Registration Successful", "You have been successfully registered.");
    }
    else if (Data == "Error executing query")
    {
        QMessageBox::warning(this, "Error", "Error executing query.");
    }
    else
    {
        qDebug() << "Unknown message received";
    }
    disconnect(Application::getSocket(), &QTcpSocket::readyRead, this, &authorization2::sockReady);
}

void authorization2::on_pushButton_2_clicked()
{
    PlayerInfo *playerInfo = new PlayerInfo();
    playerInfo->show();
    hide();
}
