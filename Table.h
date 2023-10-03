#pragma once
#include <iostream>
#include <vector>
#include <string>

#include <Column.h>

using namespace std;

class Table {

public:
	int counter;
	Base_Column* current;

	string label;
	pair<string, vector<pair<string, string>>> metadata;

	Base_Column* col_head;

	Table(pair<string, vector<pair<string, string>>> query);

	void display();

	void connect();

	/*template <class T, class... Args>
	bool addRow(T data, Args... args);

	template <class T>
	bool addRow(T data);*/


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

		connect();

		return false;
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

