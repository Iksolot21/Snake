#ifndef MODE_H
#define MODE_H

#include <QWidget>

namespace Ui {
class mode;
}

class mode : public QWidget
{
    Q_OBJECT

public:

    explicit mode(QWidget *parent = nullptr);
    ~mode();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::mode *ui;
};

#endif // MODE_H
