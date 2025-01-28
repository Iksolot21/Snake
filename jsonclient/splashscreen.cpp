#include "splashscreen.h"

#include <QApplication>
#include <QTimer>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "authorization2.h"
#include <QKeyEvent>

SplashScreen::SplashScreen(QWidget *parent) : QMainWindow(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    resize(1920, 1080);

    videoWidget = new QVideoWidget(this);
    setCentralWidget(videoWidget);

    videoPlayer = new QMediaPlayer;
    videoPlayer->setVideoOutput(videoWidget);
    videoPlayer->setSource(QUrl::fromLocalFile("C:/Qt/project/jsonclient/splashscreennew.mp4"));


    music = new QMediaPlayer();
    audioOutput = new QAudioOutput(this);
    music->setAudioOutput(audioOutput);
    music->setSource(QUrl("qrc:/image/videoplayback (1).m4a"));
    audioOutput->setVolume(0.4);
    music->play();

    videoPlayer->play();
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SplashScreen::closeSplashScreen);
    timer->start(30000);
    connect(this, &SplashScreen::destroyed, timer, &QTimer::deleteLater);
}
void SplashScreen::keyPressEvent(QKeyEvent *event)
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
void SplashScreen::closeSplashScreen()
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
SplashScreen::~SplashScreen()
{

}
