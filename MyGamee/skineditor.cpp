#include "skineditor.h"
#include "ui_skineditor.h"
#include <QPropertyAnimation>
#include <QLabel>
#include <QDebug>

skineditor::skineditor(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::skineditor)
{
    ui->setupUi(this);
    init();
}

skineditor::~skineditor()
{
    delete ui;
    delete mTimer;
}

void skineditor::init()
{
    r1 = QRect(ui->label_1->x(), ui->label_1->y(), ui->label_1->width(), ui->label_1->height());
    r2 = QRect(ui->label_2->x(), ui->label_2->y(), ui->label_2->width(), ui->label_2->height());
    r3 = QRect(ui->label_3->x(), ui->label_3->y(), ui->label_3->width(), ui->label_3->height());
}

void skineditor::startAnimate_Time()
{
    if (!isAnimatingLeft) {
        if (flag == 0) {
            animation(ui->label_1, r1, r2, true);
            animation(ui->label_2, r2, r3, false);
            animation(ui->label_3, r3, r1, false);
            flag++;
        }
        else if (flag == 1) {
            animation(ui->label_1, r2, r3, false);
            animation(ui->label_2, r3, r1, true);
            animation(ui->label_3, r1, r2, false);
            flag++;
        }
        else if (flag == 2) {
            animation(ui->label_1, r3, r1, false);
            animation(ui->label_2, r1, r2, false);
            animation(ui->label_3, r2, r3, true);
            flag = 0;
        }
    } else {
     if (flag == 1) {
            animation(ui->label_1, r1, r3, true);
            animation(ui->label_2, r3, r2, false);
            animation(ui->label_3, r2, r1, false);
            flag++;
        }
        else if (flag == 2) {
            animation(ui->label_1, r3, r2, false);
            animation(ui->label_2, r2, r1, true);
            animation(ui->label_3, r1, r3, false);
            flag++;
        }
        else if (flag == 3) {
            animation(ui->label_1, r2, r1, false);
            animation(ui->label_2, r1, r3, false);
            animation(ui->label_3, r3, r2, true);
            flag = 0;
        }
    }
}

void skineditor::animation(QObject *target, QRect startRect, QRect endRect, bool isRaise)
{
    QPropertyAnimation *a = new QPropertyAnimation(target, "geometry");
    a->setDuration(1000);
    a->setStartValue(startRect);
    a->setEndValue(endRect);
    a->setEasingCurve(QEasingCurve::OutQuad);
    a->start();
    QLabel* lab = dynamic_cast<QLabel*>(target);
    if (isRaise) {
        lab->raise();
    }
}

void skineditor::on_right_arrow_clicked()
{
    isAnimatingLeft = false;
    startAnimate_Time();
}

void skineditor::on_left_arrow_clicked()
{
    isAnimatingLeft = true;
    startAnimate_Time();
}


void skineditor::on_choose_clicked()
{
    QPixmap headTexture;
    QPixmap bodyTexture;

    if (ui->label_1 == sender()) {
        headTexture.load(":/images/resource/red_head.png");
        bodyTexture.load(":/images/resource/red_body.png");
    } else if (ui->label_2 == sender()) {
        headTexture.load(":/images/resource/purple_head.png");
        bodyTexture.load(":/images/resource/purple_body.png");
    } else if (ui->label_3 == sender()) {
        headTexture.load(":/images/resource/blue_head.png");
        bodyTexture.load(":/images/resource/blue_body.png");
    }

    emit headTextureChanged(headTexture);
    emit bodyTextureChanged(bodyTexture);
}
