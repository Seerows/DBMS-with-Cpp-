#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <QFile>
#include <QDataStream>

#include "Table.h"
#include "Dependencies.h"

using namespace std;

class Database{

public:
    Database();
    Database(Table& table1, Table& table2);
    string name;
    string username;
    string password;

    Table* t1;
    Table* t2;
    Table* temp;


    void join();    //right now, the join is hardcoded. Waiting for SAB's input parser.
    void commit();
};

#endif // DATABASE_H
