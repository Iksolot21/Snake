#ifndef MENU_H
#define MENU_H

#include "qlabel.h"
#include <QMainWindow>
#include <QMovie>
#include <QLabel>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <mainwindow.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class Menu;
}
QT_END_NAMESPACE

class Menu : public QMainWindow
{
    Q_OBJECT

public:
    void readScoreFromFile(int &maxScore);
    void setUsername(const QString &username);
    QMovie *movie;
    QLabel *label;
    Menu(QWidget *parent = nullptr);
    ~Menu();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

private:
    QString username;
    MainWindow *mainWindow;
    QAudioOutput *audioOutput;
    QMediaPlayer *music;
    Ui::Menu *ui;
protected:
    void closeEvent(QCloseEvent *event) override;
};
#endif // MENU_H
