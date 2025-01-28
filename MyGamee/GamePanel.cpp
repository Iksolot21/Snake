#include "GamePanel.h"
#include "qapplication.h"
#include <QPainter>
#include <QKeyEvent>
#include <QMediaPlayer>
#include <QFont>
#include <QPushButton>
#include <QFile>

#define WIDTH 20
#define HEIGHT 20

GamePanel::GamePanel(bool initializeSecondSnake, QWidget* parent) : QWidget(parent), initializeSecondSnake(initializeSecondSnake) {
    restartBtn = new QPushButton("Restart", this);
    restartBtn->setGeometry(this->width() / 2, this->height() / 2+ this->height() / 4, 50, 50);
    restartBtn->setFocusPolicy(Qt::NoFocus);
    restartBtn->setStyleSheet("background-color: rgb(0, 0, 255);");
    connect(restartBtn, &QPushButton::clicked, this, &GamePanel::restartGame);
    restartBtn->setVisible(false);
    isGameOver=false;
    pause= false;


    // Инициализируем таймер для обновления игры
    setStyleSheet("QWidget {background-image: url(:/images/resource/grass.png) }");
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GamePanel::updateGame);
    timer->start(100);
    //==========GAME INITIALISATION===========
    xPos = yPos = 10;
    xControl = 0;
    yControl = 1;
    xFood = yFood = 12;
    snakeSize = 2;
    bitmap = new int*[HEIGHT];
    for (int i = 0; i < HEIGHT; i++)
        bitmap[i] = new int[WIDTH];
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
            bitmap[i][j] = 0;
    }

    // Инициализация переменных для второй змейки
    if (initializeSecondSnake) {
    xPos2 = yPos2 = 5;
    xControl2 = 0;
    yControl2 = 1;
    xFood2 = yFood2 = 8;
    snakeSize2 = 2;
    bitmap2 = new int*[HEIGHT];
    for (int i = 0; i < HEIGHT; i++)
        bitmap2[i] = new int[WIDTH];
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++)
            bitmap2[i][j] = 0;
    }
    }

    music = new QMediaPlayer();
    audioOutput = new QAudioOutput(this);
    music->setAudioOutput(audioOutput);
    music->setSource(QUrl("qrc:/images/resource/Smeshariki_-_Muzyka_pogoni_66371495.mp3"));
    audioOutput->setVolume(0.4);
    music->play();
    background = QPixmap(":/images/resource/grass.png");

}

    GamePanel::~GamePanel() {
    for (int i = 0; i < HEIGHT; i++) {
        delete[] bitmap[i];

        delete[] bitmap2[i];
    }
    delete[] bitmap;
     if (initializeSecondSnake) {
    delete[] bitmap2;
     }
}

void GamePanel::restartGame() {
    isGameOver=false;
    xPos = yPos = 10;
    xControl = 0;
    yControl = 1;
    snakeSize = 2;
    snakeSize2 = 2;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++)
        {
            bitmap[i][j] = 0;
            if (initializeSecondSnake) {
            bitmap2[i][j] = 0;
            }
        }
    }


    xFood = rand() % WIDTH;
    yFood = rand() % HEIGHT;

    timer->start();

    music->play();

    update();
}

void GamePanel::saveScoreToFile(int score) {
    QString filename = "score.txt";
    QFile file(filename);

    int maxScore = 0;

    qDebug() << "saveScoreToFile called with score:" << score;

    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QTextStream in(&file);
        QString currentScore = in.readAll();
        maxScore = currentScore.toInt();
        qDebug() << "Current max score in file:" << maxScore;

        if (score > maxScore) {
            maxScore = score;
            file.resize(0);
            QTextStream out(&file);
            out << maxScore;
            qDebug() << "New max score written to file:" << maxScore;
        } else {
            qDebug() << "Score is not higher than current max score. File not updated.";
        }
    } else {
        qDebug() << "Error opening file:" << file.errorString();
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << score;
            qDebug() << "New file created with score:" << score;
        }
    }

    file.close();
}
void GamePanel::keyPressEvent(QKeyEvent* event) {
    if (!isGameOver)
    {
    switch (event->key()) {
    case Qt::Key_A:

        if (xControl != 1) {
            xControl = -1;
            yControl = 0;
        }
        break;
    case Qt::Key_D:

        if (xControl != -1) {
            xControl = 1;
            yControl = 0;
        }
        break;
    case Qt::Key_W:

        if (yControl != 1) {
            xControl = 0;
            yControl = -1;
        }
        break;
    case Qt::Key_S:

        if (yControl != -1) {
            xControl = 0;
            yControl = 1;
        }
        break;
    case Qt::Key_Space:
    if (pause)
        timer->start();
    else {
        timer->stop();
        update();
        }
    pause=!pause;
    break;
    case Qt::Key_Escape:
        QApplication::quit();
        break;
         if (initializeSecondSnake) {
        // Управление второй змейкой
        case Qt::Key_Left:
        if (xControl2 != 1) {
            xControl2 = -1;
            yControl2 = 0;
        }
        break;
    case Qt::Key_Right:
        if (xControl2 != -1) {
            xControl2 = 1;
            yControl2 = 0;
        }
        break;
    case Qt::Key_Up:
        if (yControl2 != 1) {
            xControl2 = 0;
            yControl2 = -1;
        }
        break;
    case Qt::Key_Down:
        if (yControl2 != -1) {
            xControl2 = 0;
            yControl2 = 1;
        }
        break;
    }

}
}
}

void GamePanel::updateGame() {

    xPos += xControl;
    yPos += yControl;

    if (xPos >= WIDTH) xPos = 0;
    else if (xPos < 0) xPos = WIDTH - 1;
    if (yPos >= WIDTH) yPos = 0;
    else if (yPos < 0) yPos = HEIGHT - 1;

    if (xPos == xFood && yPos == yFood) {
        snakeSize++;
        xFood = rand() % WIDTH;
        yFood = rand() % HEIGHT;
        saveScoreToFile(snakeSize);
    }

    if (bitmap[xPos][yPos] > 0) {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++)
                bitmap[i][j] = 0;
        }
        snakeSize = 1;
        isGameOver=true;
    }
    else {
        for (int i = 0; i < HEIGHT; i++)
            for (int j = 0; j < WIDTH; j++)
                if (bitmap[i][j] > 0) bitmap[i][j]--;
        }

    bitmap[xPos][yPos] = snakeSize;
    update();
     if (initializeSecondSnake) {

    xPos2 += xControl2;
    yPos2 += yControl2;

    if (xPos2 >= WIDTH) xPos2 = 0;
    else if (xPos2 < 0) xPos2 = WIDTH - 1;
    if (yPos2 >= WIDTH) yPos2 = 0;
    else if (yPos2 < 0) yPos2 = HEIGHT - 1;

    if (xPos2 == xFood && yPos2 == yFood) {
        snakeSize2++;
        xFood = rand() % WIDTH;
        yFood = rand() % HEIGHT;
        saveScoreToFile(snakeSize2);
    }
    if (bitmap[xPos2][yPos2] > 0) {
        isGameOver = true;
    }
    if (bitmap2[xPos][yPos] > 0) {
        isGameOver = true;

    }
    if (bitmap2[xPos2][yPos2] > 0) {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++)
                bitmap2[i][j] = 0;
        }
        snakeSize2 = 2;
        isGameOver=true;
    }
    else {
        for (int i = 0; i < HEIGHT; i++)
            for (int j = 0; j < WIDTH; j++)
                if (bitmap2[i][j] > 0) bitmap2[i][j]--;
    }

    bitmap2[xPos2][yPos2] = snakeSize2;
    update();
     }
}

void GamePanel::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter painter(this);
    int width = size().width();
    int height = size().height();

    QRect screenSize = qApp->primaryScreen()->geometry();

    double cellWidth = screenSize.width() / WIDTH;
    double cellHeight = screenSize.height() / HEIGHT;


    painter.drawPixmap(0, 0, width, height, background);


    QPixmap foodImage(":/images/resource/burger.png");
    painter.drawPixmap(xFood * cellWidth, yFood * cellHeight, cellWidth, cellHeight, foodImage);

    QPixmap snakeHeadTexture(":/images/resource/blue_head.png");
    QPixmap snakeTailTexture(":/images/resource/tail.png");
    QPixmap snakeBodyTexture(":/images/resource/blue_body.png");

    QPixmap snakeHeadTexture2(":/images/resource/yellow_head.png");
    QPixmap snakeBodyTexture2(":/images/resource/yellow.png");


    int headX = xPos;
    int headY = yPos;

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (bitmap[x][y] > 0) {
                if (x == headX && y == headY) {
                    // Отрисовка головы змеи
                    painter.save();
                    painter.translate(x * cellWidth + cellWidth / 2, y * cellHeight + cellHeight / 2);
                    QTransform transform;
                    if (xControl == 1) {
                        transform.rotate(90);
                    } else if (xControl == -1) {
                        transform.rotate(-90);
                    } else if (yControl == 1) {
                        transform.rotate(180);
                    }
                    QPixmap transformedHeadTexture = snakeHeadTexture.transformed(transform, Qt::SmoothTransformation);
                    painter.drawPixmap(-cellWidth / 2, -cellHeight / 2, cellWidth, cellHeight, transformedHeadTexture);
                    painter.restore();
                } else {

                        painter.drawPixmap(x * cellWidth, y * cellHeight, cellWidth, cellHeight, snakeBodyTexture);
                    }
                }
            }
        }
     if (initializeSecondSnake) {

    int headX2 = xPos2;
    int headY2 = yPos2;

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (bitmap2[x][y] > 0) {
                if (x == headX2 && y == headY2) {
                    painter.save();
                    painter.translate(x * cellWidth + cellWidth / 2, y * cellHeight + cellHeight / 2);

                    QTransform transform;
                    if (xControl2 == 1) {
                        transform.rotate(90);
                    } else if (xControl2 == -1) {
                        transform.rotate(-90);
                    } else if (yControl2 == 1) {
                        transform.rotate(180);
                    }

                    QPixmap transformedHeadTexture = snakeHeadTexture2.transformed(transform, Qt::SmoothTransformation);
                    painter.drawPixmap(-cellWidth / 2, -cellHeight / 2, cellWidth, cellHeight, transformedHeadTexture);

                    painter.restore();
                } else {
                    painter.drawPixmap(x * cellWidth, y * cellHeight, cellWidth, cellHeight, snakeBodyTexture2);
                }
            }
        }
    }
     }
    QString score = QString("P1 Score: %1").arg(snakeSize);
      if (initializeSecondSnake) {
     QString score2 = QString("P2 Score: %1").arg(snakeSize2);
          painter.setFont(QFont("times",15));
          painter.setPen(QColor(0, 0, 128));
          painter.drawText(QRectF(width - 100, 5, width*3, height*3), score2);
      }


    QFont font;
    painter.setFont(QFont("times",15));
    painter.setPen(QColor(128, 0, 128));
    painter.drawText(QRectF(5, 5, width*3, height*3), score);


    if (pause)
    {
      painter.setFont(QFont("times",30));
      painter.setPen(QColor(0, 0, 139));
      painter.drawText(QRectF(0, 0, width, height), Qt::AlignCenter, "Paused");
      music->stop();

      update();
      timer->stop();
      music->stop();
    }
    else
    music->play();
    if (isGameOver) {
        timer->stop();
        music->stop();
        painter.setFont(QFont("Arial", 36));
        QRect textRect = rect();
        textRect.adjust(2, 2, -2, -2);
        for (int i = 0; i < 5; ++i) {
            QColor color = QColor::fromHsv((i * 60) % 360, 255, 255);
            painter.setPen(color);
            painter.drawText(textRect, Qt::AlignCenter, "GAME OVER");
            textRect.translate(2, 2);
            painter.setFont(QFont("Arial", 36));
            QRect textRect = rect();
            textRect.adjust(2, 2, -2, -200);
            if (initializeSecondSnake) {
            QString winnerMessage;
            if (snakeSize > snakeSize2) {
                winnerMessage = "Winner: 1";
            } else if (snakeSize < snakeSize2) {
                winnerMessage = "Winner: 2";
            } else {
                winnerMessage = "Draw";
            }
            painter.drawText(textRect, Qt::AlignCenter, winnerMessage);
            }
        }

        restartBtn->setVisible(true);
    }
    else
    {
        restartBtn->setVisible(false);
    }
}

