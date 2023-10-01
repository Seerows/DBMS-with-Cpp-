#include "Table.h"

Table::Table(pair<string, vector<pair<string, string>>> query) {
	metadata = query;
	counter = 0;

	BaseColumn* curr;

	for (int i = 0; i < query.second.size(); i++) {
		string type = query.second.at(i).first;
		curr = col_head;

		if (i == 0) {

			if (type == "float") {
				col_head = new Column<float>(query.second.at(i).second);
			}
			else if (type == "string") {
				col_head = new Column<string>(query.second.at(i).second);
			}
			else if (type == "char") {
				col_head = new Column<char>(query.second.at(i).second);
			}
			else if (type == "bool") {
				col_head = new Column<bool>(query.second.at(i).second);
			}
			else {			//for int case. Removing this gives an error.
				col_head = new Column<int>(query.second.at(i).second);
			}

		}
		else{
			
			if (i == 1) {
				curr = col_head;
			}
			else if (i > 1) {
				curr = curr->next_col;
			}

			if (type == "float") {
				curr->next_col = new Column<float>(query.second.at(i).second);
			}
			else if (type == "class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >") {
				curr->next_col = new Column<string>(query.second.at(i).second);
			}
			else if (type == "char") {
				curr->next_col = new Column<char>(query.second.at(i).second);
			}
			else if (type == "bool") {
				curr->next_col = new Column<bool>(query.second.at(i).second);
			}
			else {			//for int case. Removing this gives an error.
				curr->next_col = new Column<int>(query.second.at(i).second);
			}

		}

	}

	current = col_head;
}

void Table::display() {

	current = col_head;

	while (current != NULL) {
		current->display();
		cout << endl;
		current = current->next_col;
	}

	current = col_head;
}

template <class T>
bool Table::addRow(T data) {

	if (!strcmp(metadata.second.at(counter).first.c_str(), typeid(T).name())) {
		current->insertAtTail(data);
	}
	else {
		cout << "nah\n";
	}


	current = col_head;
	counter = 0;

	return false;
}

template <class T, class... Args>
bool Table::addRow(T data, Args... args) {


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

template bool Table::addRow<int>(int);
template bool Table::addRow<char>(char);
template bool Table::addRow<string>(string);
template bool Table::addRow<float>(float);
template bool Table::addRow<bool>(bool);

template bool Table::addRow<int, int>(int, int);
template bool Table::addRow<int, string>(int, string);
template bool Table::addRow<string, int>(string, int);
template bool Table::addRow<string, string>(string, string);