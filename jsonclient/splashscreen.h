#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H
#include <QVideoWidget>
#include <QObject>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "authorization2.h"

class SplashScreen : public QMainWindow
{
    Q_OBJECT
public:
    explicit SplashScreen(QWidget *parent = nullptr);
    ~SplashScreen();
signals:
    void menuFinished();
private:
    QTimer *timer = nullptr;
    QVideoWidget *videoWidget;
    class QMediaPlayer *videoPlayer;
    QAudioOutput *audioOutput;
    QMediaPlayer *music;
    authorization2 *auth;
private slots:
    void closeSplashScreen();
protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // SPLASHSCREEN_H
