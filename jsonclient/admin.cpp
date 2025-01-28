#include "admin.h"
#include "qboxlayout.h"
#include "qlineedit.h"
#include "ui_admin.h"
#include "application.h"
#include "mainwindow.h"
#include "authorization2.h"

Admin::Admin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Admin)
{
    ui->setupUi(this);

    idLineEdit = new QLineEdit(this);
    newPasswordLineEdit = new QLineEdit(this);
    idLineEdit->move(20, 10);
    newPasswordLineEdit->move(10, 40);
    idLineEdit->setFixedSize(200, 20);
    newPasswordLineEdit->setFixedSize(200, 20);
}

Admin::~Admin()
{
    delete ui;
}

void Admin::on_pushButton_4_clicked()
{
    // выход
    QCoreApplication::quit();
}


void Admin::on_pushButton_clicked()
{
    QString id = idLineEdit->text();
    QString queryStr = "DELETE FROM listworkers WHERE name = '"+ id +"'";
    MainWindow mainWindow(nullptr);
    mainWindow.SendToServer(queryStr);
}
void Admin::on_pushButton_2_clicked()
{

    QString username = idLineEdit->text();
    QString newPassword = newPasswordLineEdit->text();

    QString queryStr = "UPDATE listworkers SET password = '" + newPassword + "' WHERE name = '" + username + "'";
    MainWindow mainWindow(nullptr);
    mainWindow.SendToServer(queryStr);
}

void Admin::on_pushButton_3_clicked()
{
    QString id = idLineEdit->text();
    QString queryStr = "UPDATE listworkers SET block = 1 WHERE name = '"+id +"'";
    MainWindow mainWindow(nullptr);
    mainWindow.SendToServer(queryStr);
 }

void Admin::refreshUserTable()
{
    userTable->clearContents();

    QSqlQuery query("SELECT name, id FROM listworkers");
    int row = 0;
    while(query.next()) {
        QString username = query.value(0).toString();
        QString userId = query.value(1).toString();
        userTable->setItem(row, 0, new QTableWidgetItem(username));
        userTable->setItem(row, 1, new QTableWidgetItem(userId));
        row++;
    }
}

