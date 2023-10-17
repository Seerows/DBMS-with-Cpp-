#pragma once
#include <iostream>
#include <vector>
#include <cstring>
#include "string.h"
#include <string>

#include "Column.h"

using namespace std;

class Table {

public:
    int counter;
    int num_of_cols, num_of_rows;
    Base_Column* current;

    string label;
    pair<string, vector<pair<string, string>>> metadata;

    Base_Column* col_head;

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


    template <class T>
    bool addRow(T data) {

        string type = typeid(T).name();

        if(type == "i"){
            type = "int";
        }
        else if(type == "NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE"){
            type = "class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >";
        }
        else if(type == "c"){
            type = "char";
        }
        else if(type == "b"){
            type = "bool";
        }
        else if(type == "f"){
            type = "float";
        }

        if (metadata.second.at(counter).first == type) {
            current->insertAtTail(data);
        }
        else {
            cout << "Row cannot be added." << endl;
            return false;
        }

        num_of_rows++;
        current = col_head;
        counter = 0;

        connect();

        return true;
    }

    template <class T, class... Args>
    bool addRow(T data, Args... args) {
        string type = typeid(T).name();

        if(type == "i"){
            type = "int";
        }
        else if(type == "NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE"){
            type = "class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >";
        }
        else if(type == "c"){
            type = "char";
        }
        else if(type == "b"){
            type = "bool";
        }
        else if(type == "f"){
            type = "float";
        }


        if (metadata.second.at(counter).first == type) {
            current->insertAtTail(data);
            current = current->next_col;

            counter++;
            if (addRow(args...)) {
                return true;
            }

            current = current->prev_col;
            counter--;
            current->deleteAtTail();
        }

        cout << "Row cannot be added." << endl;
        return false;

    }

};

