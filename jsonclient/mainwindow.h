#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "authorization2.h"
#include <QMainWindow>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDebug>
#include <QStandardItemModel>
#include <QTime>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlTableModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase db;
    void SendToServer(QString str);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QByteArray Data;

public slots:
        void slotReadyRead();



private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_lineEdit_returnPressed();

    void on_pushButton_2_clicked();

private:
    QStandardItemModel *model;
    Ui::MainWindow *ui;
    quint16 nextBlockSize;
};
#endif // MAINWINDOW_H
