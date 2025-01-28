#ifndef DBINTERFACE_H
#define DBINTERFACE_H

#include <QSqlQuery>
#include <QSqlDatabase>

class DBInterface
{
public:
    DBInterface();
private:
    QSqlDatabase db;
};

#endif // DBINTERFACE_H
