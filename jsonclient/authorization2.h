#ifndef AUTHORIZATION2_H
#define AUTHORIZATION2_H

#include <QWidget>
#include <QTcpSocket>
#include <QJsonParseError>
#include <QMessageBox>
#include "admin.h"


namespace Ui {
class authorization2;
}

class authorization2 : public QWidget
{
    Q_OBJECT

public:
    explicit authorization2(QWidget *parent = nullptr);
    ~authorization2();
public slots:
    virtual void sockReady();
signals:

private slots:
    void on_pushButton_3_clicked();
    void on_lineEdit_4_editingFinished();
    void on_lineEdit_3_editingFinished();


    void on_pushButton_2_clicked();

private:
    Ui::authorization2 *ui;
    QString username;
    QString password;
    QByteArray Data;
    quint16 nextBlockSize;
    bool fl = false;
};


#endif // AUTHORIZATION2_H
