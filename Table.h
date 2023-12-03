#pragma once

#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <map>

#include "Column.h"
#include "Primary_Column.h"
#include "Foreign_Column.h"
#include "Queue.h"
#include "QDebug"

using namespace std;

class Table {

public:
    int num_of_cols, num_of_rows, num_of_keys;

    string label;
    pair<string, vector<pair<string, string>>> metadata;
    map<string, string> keys;

    Base_Column* col_head;

    Table();
    Table(string label);
    Table(pair<string, vector<pair<string, string>>> query, map<string, string> keys = { {"?", "?"} }, Queue<Base_Column*>* references = NULL);

    Table(const Table& table);
    ~Table();

    //adds a newly created column and initializes all the unfilled values with NULL .
    void addColumn(pair<string, string> query);

    //adds an existing column by copying all the contents of the parameter.
    void addColumn(Base_Column* col);

    //deletes the row containing the specified Base_Node.
    void deleteRow(Base_Column* col, Base_Node* node);

    //delete all rows
    void deleteAllRows();

    //deletes an exisiting column
    void deleteColumn(string label);

    bool addRow(Base_Node* data, Base_Column* current, int counter);
    bool addRow(Queue<Base_Node*> inputs, Base_Column* current, int counter = 0);

    Base_Column& operator[](string label);
    Base_Column& operator[](int pos);
    void display();
    void connect();
    Table* join(Base_Column* foreign, Base_Column* reference);
    Base_Column* getColumn(string label);
    bool compareStrings(string str1, string str2);

};

