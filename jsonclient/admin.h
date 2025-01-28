#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>
#include <QTableWidget>

namespace Ui {
class Admin;
}

class Admin : public QWidget
{
    Q_OBJECT

public:
    char id;
    explicit Admin(QWidget *parent = nullptr);
    ~Admin();
    void refreshUserTable();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    QTableWidget *userTable;
    QLineEdit *idLineEdit;
    QLineEdit *newPasswordLineEdit;
    Ui::Admin *ui;
};

#endif // ADMIN_H
