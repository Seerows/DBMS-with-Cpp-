#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <vector>
#include <cstring>
#include <tuple>
#include <QFile>
#include <QDataStream>
#include <QDebug>

#include "Table.h"
#include "LinkedList.h"
#include "validateQuery.h"
#include "Queue.h"
#include "Node.h"
#include "Dependencies.h"

using namespace std;

class Database{

private:
    bool handleCreateQuery(pair<string, vector< pair<string, string>>> createQuery, map<string, string> keys);
    bool handleInsertQuery(pair<string, vector< vector<pair<string, string>>>> insertQuery);
    bool handleSelectQuery(pair<string, vector<string>> selectQuery, pair<vector<tuple<string, string, string>>, string> whereQuery, bool whereCheck, pair<string, string> orderQuery, bool orderCheck, pair<pair<string, string>, pair<string, string>> joinSelect, bool joinCheck);
    bool handleUpdateQuery(pair<string, vector<pair<string, string>>> updateQuery, pair<vector<tuple<string, string, string>>, string> whereQuery, bool whereCheck);
    bool handleAlterQuery(pair<string, vector<pair<string, string>>> alterQuery);
    bool handleDeleteQuery(string deleteQuery, pair<vector<tuple<string, string, string>>, string> whereQuery, bool whereCheck);
    bool handleDropQuery(string dropTableQuery);
    bool handleCommit();

    bool handleJoin(pair<pair<string, string>, pair<string, string>> joinQuery, bool joinCheck);
    bool whereDeleteUtil(Table* table, pair<vector<tuple<string, string, string>>, string> whereQuery);
    bool whereAddUtil(Table*& table, pair<vector<tuple<string, string, string>>, string> whereQuery);

public:
    Database();
    Database(string name);
    Database(string name, string username, string password);
    Database(Table& table1, Table& table2);
    ~Database();

    string name;
    string username;
    string password;
    int num_of_tables;
    Table* temp_select;
    vector<bool> status;

    LinkedList<Table*> table_list;

    void pull();
    void commit();
    void addTable(Table* table);
    void printTables();

    bool processQuery(vector<std::string> words);
    Table* getTable(string label);

    bool compareStrings(string s1, string s2);
    Base_Node* convert(string type, string value);
    tuple<string, string, string> parseFk(string s1);

};


#endif // DATABASE_H
