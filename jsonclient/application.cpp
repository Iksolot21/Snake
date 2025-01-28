#include "application.h"

Application* Application::instance = nullptr;
QTcpSocket* Application::socket = nullptr;

Application* Application::getInstance()
{
    if (!instance) {
        instance = new Application();
    }
    return instance;
}

QTcpSocket* Application::getSocket()
{
    if (!socket) {
        socket = new QTcpSocket();
    }
    return socket;
}

Application::Application()
{
    initializeSocket();
}

void Application::initializeSocket()
{
    if (!socket) {
        socket = new QTcpSocket();
    }
}
