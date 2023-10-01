#pragma once
#include <iostream>
#include <vector>
#include <string>

#include <Column.h>

using namespace std;

class Table {

public:
	int counter;
	BaseColumn* current;

	string label;
	pair<string, vector<pair<string, string>>> metadata;

	BaseColumn* col_head;

	Table(pair<string, vector<pair<string, string>>> query);

	void display();

	template <class T>
	bool addRow(T data);

	template <class T, class... Args>
	bool addRow(T data, Args... args);

};

