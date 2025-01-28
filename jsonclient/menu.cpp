#include "menu.h"
#include "ui_menu.h"
#include <QProcess>
#include <QFile>
#include "application.h"
#include "mainwindow.h"
#include "titre.h"



Menu::Menu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Menu)
{
    ui->setupUi(this);
    mainWindow = new MainWindow();
    label = new QLabel(this);
    movie = new QMovie (":/image/butterfly-insect.gif");
    label->setMovie(movie);
    this->resize(500,400);
    label->resize(200,100);
    label->show();
    movie->start();
    music = new QMediaPlayer();
    audioOutput = new QAudioOutput(this);
    music->setAudioOutput(audioOutput);
    music->setSource(QUrl("qrc:/image/menu.mp3"));
    audioOutput->setVolume(0.4);
    music->play();
}

void Menu::setUsername(const QString &username)
{
    this->username = username;
}
Menu::~Menu()
{
    delete ui;
}

void Menu::closeEvent(QCloseEvent *event)
{
    music->stop();
    QMainWindow::closeEvent(event);
}

void Menu::readScoreFromFile(int &maxScore)
{
    QString filename = "C:/Qt/project/build-jsonclient-Desktop_Qt_6_6_2_MinGW_64_bit-Debug/score.txt";
    QFile file(filename);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        QString scoreStr = in.readAll();
        maxScore = scoreStr.toInt();
        file.close();
    }
}
void Menu::on_pushButton_clicked()
{
    int maxScore = 0;
    readScoreFromFile(maxScore);
    QString program = "../jsonclient/Basic_Snake/release/MyGame.exe";
    QProcess *myProcess = new QProcess();
    myProcess->start(program);
    close();
    if (myProcess->waitForStarted())
    {
        if (myProcess->waitForFinished())
        {
            readScoreFromFile(maxScore);
            QString request = "UPDATE listworkers SET score = " + QString::number(maxScore) + " WHERE name = '" + username + "'";
            MainWindow mainWindow;
            mainWindow.SendToServer(request);
            show();
            music->play();
        }
    }
}

void Menu::on_pushButton_3_clicked()
{
        QCoreApplication::quit();
}


void Menu::on_pushButton_2_clicked()
{
   mainWindow->show();
}




void Menu::on_pushButton_4_clicked()
{
    // Создаем и показываем заставку
    titre* titre = new class titre();
    titre->show();
}

