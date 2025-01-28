#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

class DatabaseManager
{
private:
    static DatabaseManager *instance;
    QSqlDatabase db;
    DatabaseManager()
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("../jsonserver/users.db");

        if (db.open()) {
            qDebug() << "Слушаем и база данных открыта";
        } else {
            qDebug() << "База данных не открыта";
        }
    }

public:
    static DatabaseManager *getInstance()
    {
        if (!instance)
            instance = new DatabaseManager;
        return instance;
    }

    QSqlDatabase getDatabase() const
    {
        return db;
    }

    ~DatabaseManager()
    {
        db.close();
    }
};

DatabaseManager *DatabaseManager::instance = nullptr;

#endif // DATABASEMANAGER_H
