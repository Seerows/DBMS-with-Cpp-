#pragma once
#include <iostream>
#include <vector>
#include <cstring>
#include <string>

#include "Column.h"
#include "Queue.h"

using namespace std;

class Table {

public:
    int num_of_cols, num_of_rows;

    string label;
    pair<string, vector<pair<string, string>>> metadata;

    Base_Column* col_head;

    Table();
    Table(string label);
    Table(pair<string, vector<pair<string, string>>> query);
    ~Table();

    void addColumn(pair<string, string> query);
    void addColumn(Base_Column* col);
    Base_Column& operator[](string label);
    Base_Column& operator[](int pos);
    void display();
    void connect();
    Table* join(Base_Column* foreign, Base_Column* reference);
    Base_Column* getColumn(string label);
    bool compareStrings(string str1, string str2);


    bool addRow(Base_Node* data, Base_Column* current, int counter);
    bool addRow(Queue<Base_Node*> inputs, Base_Column* current, int counter = 0);

};

