#ifndef APPLICATION_H
#define APPLICATION_H

#include <QTcpSocket>
#include <QCoreApplication>

class Application
{
public:
    static Application* getInstance();
    static QTcpSocket* getSocket();

private:
    Application();
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    void initializeSocket();

    static Application* instance;
    static QTcpSocket* socket;
};

#endif // APPLICATION_H
