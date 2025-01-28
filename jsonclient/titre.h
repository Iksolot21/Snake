#ifndef TITRE_H
#define TITRE_H

#include <QVideoWidget>
#include <QObject>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "authorization2.h"

class titre : public QMainWindow
{
    Q_OBJECT
public:
    explicit titre(QWidget *parent = nullptr);
    ~titre();
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

#endif // TITRE_H
