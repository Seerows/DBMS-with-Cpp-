#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <vector>
#include <cstring>
#include <tuple>

#include "Table.h"
#include "LinkedList.h"
#include "validatequery.h"
#include "Queue.h"
#include "Node.h"

using namespace std;

class Database{

private:
    bool handleCreateQuery(pair<string, vector< pair<string, string>>> createQuery);
    bool handleInsertQuery(pair<string, vector< vector<pair<string, string>>>> insertQuery);
    bool handleSelectQuery(pair<string, vector<string>> selectQuery);
    bool handleUpdateQuery(pair<string, vector< pair<string, string>>> updateQuery, vector<tuple<string, string, string>> whereQuery);

public:
    Database(string name);
    Database(Table& table1, Table& table2);
    string name;
    string username;
    string password;
    int num_of_tables;

    Table* temp;

    LinkedList<Table*> table_list;

    //void pull();
    void join();    //right now, the join is hardcoded. Waiting for SAB's input parser.
    //void commit();
    void addTable(Table* table);
    void printTables();
    
    bool processQuery(vector<std::string> words);
    Table* getTable(string label);

    //put in Dependencies.cpp later
    bool compareStrings(string s1, string s2);
    
    Base_Node* convert(string type, string value);

};


#endif // DATABASE_H
