#ifndef GAMEPANEL_H
#define GAMEPANEL_H
#include "qmediaplayer.h"
#include "qpainter.h"
#include <QTimer>
#include <QWidget>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QGraphicsScene>
#include <QPushButton>
#include <QPixmap>

class GamePanel : public QWidget {
    Q_OBJECT
public:
    bool initializeSecondSnake;
    void saveScoreToFile(int score);
    GamePanel(bool initializeSecondSnake, QWidget* parent = nullptr);
    ~GamePanel();
protected:
    void keyPressEvent(QKeyEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private:
    QPushButton* restartBtn;
    bool isGameOver;
    bool pause;
    QPainter * painter;
    QPixmap background;
    QAudioOutput *audioOutput;
    QMediaPlayer *music;
    QTimer* timer;
    void updateGame();

    int xControl, yControl;
    int xPos, yPos;
    int xFood, yFood;
    int snakeSize;
    int** bitmap;

    // Для второй змейки
    int xControl2, yControl2;
    int xPos2, yPos2;
    int xFood2, yFood2;
    int snakeSize2;
    int** bitmap2;
private slots:
    void restartGame();
};

#endif // GAMEPANEL_H
