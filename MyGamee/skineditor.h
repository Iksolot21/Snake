#ifndef SKINEDITOR_H
#define SKINEDITOR_H

#include <QWidget>
#include <QTimer>
#include <QRect>

namespace Ui {
class skineditor;
}

class skineditor : public QWidget
{
    Q_OBJECT

public:
    explicit skineditor(QWidget *parent = nullptr);
    ~skineditor();

signals:
    void headTextureChanged(const QPixmap& texture);
    void bodyTextureChanged(const QPixmap& texture);
private slots:
    void startAnimate_Time();
    void init(); // Добавлен прототип инициализационной функции
    void animation(QObject *target, QRect startRect, QRect endRect, bool isRaise); // Добавлен прототип функции анимации

    void on_right_arrow_clicked();

    void on_left_arrow_clicked();

    void on_choose_clicked();

private:
    Ui::skineditor *ui;
    QTimer *mTimer; // Добавлен указатель на таймер
    QRect r1, r2, r3; // Добавлены переменные для хранения координат объектов
    int flag = 0;
    bool isAnimatingLeft;
};

#endif // SKINEDITOR_H
