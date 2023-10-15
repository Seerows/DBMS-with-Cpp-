#pragma once
#include <iostream>
#include <vector>
#include <string>

#include <Column.h>

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
	void addColumn(pair<string, string> query);
	void addColumn(Base_Column* col);
	Base_Column& operator[](string label);
	Base_Column& operator[](int pos);
	void display();
	void connect();
	Table* join(Base_Column* foreign, Base_Column* reference);

	//implement backtracking?
	template <class T>
	bool addRow(T data) {
		
		if (!strcmp(metadata.second.at(counter).first.c_str(), typeid(T).name())) {
			current->insertAtTail(data);
		}
		else {
			cout << "nah\n";
		}

		current = col_head;
		counter = 0;
		num_of_rows++;

		connect();

		return true;
	}

	template <class T, class... Args>
	bool addRow(T data, Args... args) {


		if (!strcmp(metadata.second.at(counter).first.c_str(), typeid(T).name())) {

			current->insertAtTail(data);
			current = current->next_col;
		}
		else {
			cout << "nah1\n";
		}

		counter++;
		return addRow(args...);

	}

};

