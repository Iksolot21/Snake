#include "mode.h"
#include "ui_mode.h"
#include "GamePanel.h"
#include <QObject>

mode::mode(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mode)
{
    ui->setupUi(this);
}

mode::~mode()
{
    delete ui;
}


void mode::on_pushButton_clicked()
{
    // Режим для одного игрока
    GamePanel* game = new GamePanel(false);
    game->showFullScreen();
}

void mode::on_pushButton_2_clicked()
{
    // Режим для двух игроков
    GamePanel* game = new GamePanel(true);
    game->showFullScreen();
}




