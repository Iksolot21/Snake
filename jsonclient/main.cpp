#include <menu.h>
#include <QApplication>
#include "authorization2.h"
#include "application.h"
#include <QFile>

int main(int argc, char *argv[])
{
    QString filename = "C:/Qt/project/build-jsonclient-Desktop_Qt_6_6_2_MinGW_64_bit-Debug/score.txt";
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        file.close();
    } else {
        qDebug() << "Ошибка при открытии файла для очистки";
        return 1;
    }
    Application::getSocket();
    QApplication a(argc, argv);
    authorization2 auth;
    auth.show();
    return a.exec();
}
