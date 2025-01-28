#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

class DatabaseManager {
public:
    static DatabaseManager& instance() {
        static DatabaseManager instance;
        return instance;
    }

    QSqlDatabase& database() { return db; }

private:
    QSqlDatabase db;

    DatabaseManager() {
        // Инициализация базы данных
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("путь_к_вашей_базе_данных.db");
        if (!db.open()) {
            qDebug() << "Не удалось открыть базу данных";
        }
    }
    ~DatabaseManager() {
        if (db.isOpen()) {
            db.close();
        }
    }
};#include "dbmanager.h"

dbmanager::dbmanager()
{

}
