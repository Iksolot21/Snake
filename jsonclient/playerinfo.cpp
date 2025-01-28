#include "playerinfo.h"
#include "ui_playerinfo.h"
#include "mainwindow.h"
#include "application.h"
#include "authorization2.h"

PlayerInfo::PlayerInfo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PlayerInfo)
{
    ui->setupUi(this);
}

PlayerInfo::~PlayerInfo()
{
    delete ui;
}

void PlayerInfo::on_pushButton_clicked()
{
    authorization2 auth;
    connect(Application::getSocket(), &QTcpSocket::readyRead, &auth, &authorization2::sockReady);

    Application::getSocket()->connectToHost("127.0.0.1", 23232);
    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Registration Error", "Username and password cannot be empty.");
        return;
    }
    QString queryStr = "INSERT INTO listworkers (name, password) VALUES ('" + username + "', '" + password + "')";

    MainWindow mainWindow(nullptr);
    mainWindow.SendToServer(queryStr);
    disconnect(Application::getSocket(), &QTcpSocket::readyRead, &auth, &authorization2::sockReady);
    close();

    authorization2 *authWindow = new authorization2();
    authWindow->show();
}


void PlayerInfo::on_lineEdit_editingFinished()
{
    password = ui->lineEdit->text();
}


void PlayerInfo::on_lineEdit_2_editingFinished()
{
    password = ui->lineEdit_2->text();
}

