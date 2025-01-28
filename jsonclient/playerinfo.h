#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#include <QWidget>
#include "authorization2.h"

namespace Ui {
class PlayerInfo;
}

class PlayerInfo : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerInfo(QWidget *parent = nullptr);

    ~PlayerInfo();

private slots:


    void on_pushButton_clicked();

    void on_lineEdit_editingFinished();

    void on_lineEdit_2_editingFinished();

private:
    authorization2 auth;

    Ui::PlayerInfo *ui;
    QString username;
    QString password;
};

#endif // PLAYERINFO_H
