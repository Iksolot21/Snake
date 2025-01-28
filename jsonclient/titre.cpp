#include "titre.h"
#include <QApplication>
#include <QTimer>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QKeyEvent>

titre::titre(QWidget *parent) : QMainWindow(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    resize(1920, 1080);

    videoWidget = new QVideoWidget(this);
    setCentralWidget(videoWidget);

    videoPlayer = new QMediaPlayer;
    videoPlayer->setVideoOutput(videoWidget);
    videoPlayer->setSource(QUrl::fromLocalFile("C:/Qt/project/jsonclient/Qumi-Qumi The Legend end credits.mp4"));


    music = new QMediaPlayer();
    audioOutput = new QAudioOutput(this);
    music->setAudioOutput(audioOutput);
    music->setSource(QUrl("qrc:/image/videoplayback (2).m4a"));
    audioOutput->setVolume(0.4);
    music->play();

    videoPlayer->play();
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &titre::closeSplashScreen);
    timer->start(30000);
    connect(this, &titre::destroyed, timer, &QTimer::deleteLater);
}
void titre::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space) {
        closeSplashScreen();
    } else {
        QMainWindow::keyPressEvent(event);
    }
    if (timer && timer->isActive()) {
        timer->stop();
        timer->deleteLater();

    }
}
void titre::closeSplashScreen()
{

    QTimer *timer = qobject_cast<QTimer*>(sender());
    if (timer) {
        timer->stop();
        timer->deleteLater();
    }
    music->stop();

    if (isVisible())
        close();

    emit menuFinished();
}
titre::~titre()
{

}
